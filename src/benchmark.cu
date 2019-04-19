#include "benchmark.h"
#include "wrapper.h"
#include <exception>
#include <yao/cuda/cuda_error.h>
#include <yao/io/binary_io.h>
#include <yao/cusp_ext/convert.h>
#include <yao/time/timer.h>
#include <cusp/csr_matrix.h>

#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>

#include <algorithm>
#include <numeric>

#include <cusp/system/tbb/detail/par.h>

#ifdef ENABLE_VTUNE
#include "vtune.h"
#endif

bool is_file_exist(std::string filename)
{
	std::ifstream infile(filename);
	return infile.good();
}

void read_matrix(matrix_info_t &matrix, const std::vector<std::string> path,
	cusp::csr_matrix<int, float, cusp::host_memory> &csr_matrix, float ValueThreshold)
{
	std::string filename;
	bool is_found = false;
	for (auto &dir : path)
	{
		filename = dir + matrix.data_filename;
		if (is_file_exist(filename))
		{
			is_found = true;
			break;
		}
	}

	std::cout << "Read " << filename << std::endl;

	if (!is_found)
		throw std::runtime_error(filename + " NOT found!");

	std::vector<float> raw_data;
	yao::io::ReadBinaryArray(filename, raw_data);
	yao::cusp_ext::convert(&raw_data[0], matrix.num_rows, matrix.num_cols, csr_matrix, ValueThreshold);

    matrix.nnz = csr_matrix.num_entries;

	float nnz_percent = static_cast<float>(csr_matrix.num_entries) / (csr_matrix.num_rows * csr_matrix.num_cols);
	std::cout << "nnz%=" << nnz_percent << std::endl;
	
}


template <typename callable_t>
double time_spmv(callable_t c, int num_iterations)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < num_iterations; i++)
		c();
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time = t2 - t1;

	return static_cast<double>(time.count()) / num_iterations;
}

// TODO Reduce redundant code
benchmark_result_t start_benchmark(benchmark_setting_t &setting)
{
	benchmark_result_t b_result;

	for (auto & matrix : setting.matrices)
	{
		
		// CPU SpMV
		cusp::csr_matrix<int, float, cusp::host_memory> csr_matrix;
		read_matrix(matrix, setting.matrix_path, csr_matrix, setting.value_threshold);

		matrix_result_t m_result(matrix);

		std::vector<float> x(matrix.num_cols, 1);
		std::vector<float> y(matrix.num_rows, 0);
		
		m_result.time.emplace(static_cast<std::string>("mkl"), 
			time_spmv([&csr_matrix, &x, &y] {blas::mkl::spmv(csr_matrix, x, y); }, setting.num_iterations));


		::cusp::array1d_view<typename std::vector<float>::iterator> x_view(x.begin(), x.end());
		::cusp::array1d_view<typename std::vector<float>::iterator> y_view(y.begin(), y.end());
		//CPU cusp



		#ifdef ENABLE_VTUNE
		__itt_resume();
		__itt_task_begin(domain, __itt_null, __itt_null, op_task);
		#endif

		m_result.time.emplace(static_cast<std::string>("cusp_tbb"),
			time_spmv(
				[&csr_matrix, &x_view, &y_view]
		{::cusp::multiply(::cusp::tbb::par, csr_matrix, x_view, y_view);},
			setting.num_iterations));

		#ifdef ENABLE_VTUNE
		__itt_task_end(domain);
		__itt_pause();
		#endif


		 // GPU cusp
		 cusp::csr_matrix<int, float, cusp::device_memory> d_csr_matrix(csr_matrix);
		 thrust::device_vector<float> d_x(csr_matrix.num_cols, 1);
		 thrust::device_vector<float> d_y(csr_matrix.num_rows, 0);

		 m_result.time.emplace(static_cast<std::string>("cusp_cuda"),
		 	time_spmv(
		 		[&d_csr_matrix, &d_x, &d_y] 
		 		{blas::cusp::spmv(d_csr_matrix, d_x, d_y); throw_on_cuda_error(cudaDeviceSynchronize()); },
		 		setting.num_iterations));

		 // GPU cusparse
		 auto cusparse_handle = blas::cusparse::create_handle();
		 auto cusparse_descr = blas::cusparse::create_mat_descr(d_csr_matrix);
		 m_result.time.emplace(static_cast<std::string>("cusparse"),
		 	time_spmv( 
		 		[&cusparse_handle, &cusparse_descr, &d_csr_matrix, &d_x, &d_y] 
		 		{blas::cusparse::spmv(cusparse_handle, cusparse_descr, d_csr_matrix, d_x, d_y); throw_on_cuda_error(cudaDeviceSynchronize()); }, 
		 		setting.num_iterations));

		 // GPU cusparse_mp
		 m_result.time.emplace(static_cast<std::string>("cusparse_mp"),
		 	time_spmv([&cusparse_handle, &cusparse_descr, &d_csr_matrix, &d_x, &d_y] 
		 			  {blas::cusparse::spmv_mp(cusparse_handle, cusparse_descr, d_csr_matrix, d_x, d_y); throw_on_cuda_error(cudaDeviceSynchronize()); }, 
		 		setting.num_iterations));

		b_result.push_back(m_result);
	}

	return b_result;
}

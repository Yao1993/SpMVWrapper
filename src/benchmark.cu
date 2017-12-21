#pragma once
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


bool is_file_exist(std::string filename)
{
	std::ifstream infile(filename);
	return infile.good();
}

void read_matrix(const matrix_info &matrix, const std::vector<std::string> path,
	cusp::csr_matrix<int, float, cusp::host_memory> &csr_matrix)
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

	if (!is_found)
		throw(filename + " NOT found!");

	std::vector<float> raw_data;
	yao::io::ReadBinaryArray(filename, raw_data);
	yao::cusp_ext::convert(&raw_data[0], matrix.num_rows, matrix.num_cols, csr_matrix);
	
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
benchmark_result start_benchmark(benchmark_setting &setting)
{
	benchmark_result b_result;

	for (auto & matrix : setting.matrices)
	{
		
		matrix_result m_result(matrix);




		// CPU SpMV
		cusp::csr_matrix<int, float, cusp::host_memory> csr_matrix;
		read_matrix(matrix, setting.matrix_path, csr_matrix);
		std::vector<float> x(matrix.num_cols, 1);
		std::vector<float> y(matrix.num_rows, 0);
		
		m_result.time.emplace_back(static_cast<std::string>("mkl"), 
			time_spmv([&csr_matrix, &x, &y] {blas::mkl::spmv(csr_matrix, x, y); }, setting.num_iterations));

		// GPU cusp
		cusp::csr_matrix<int, float, cusp::device_memory> d_csr_matrix(csr_matrix);
		thrust::device_vector<float> d_x(matrix.num_cols, 1);
		thrust::device_vector<float> d_y(matrix.num_rows, 0);

		m_result.time.emplace_back(static_cast<std::string>("cusp"),
			time_spmv(
				[&d_csr_matrix, &d_x, &d_y] 
				{blas::cusp::spmv(d_csr_matrix, d_x, d_y); throw_on_cuda_error(cudaDeviceSynchronize()); },
				setting.num_iterations));

		// GPU cusparse
		auto cusparse_handle = blas::cusparse::create_handle();
		auto cusparse_descr = blas::cusparse::create_mat_descr(d_csr_matrix);
		m_result.time.emplace_back(static_cast<std::string>("cusparse"),
			time_spmv(
				[&cusparse_handle, &cusparse_descr, &d_csr_matrix, &d_x, &d_y] 
				{blas::cusparse::spmv(cusparse_handle, cusparse_descr, d_csr_matrix, d_x, d_y); throw_on_cuda_error(cudaDeviceSynchronize()); }, 
				setting.num_iterations));

		// GPU cusparse_mp
		m_result.time.emplace_back(static_cast<std::string>("cusparse_mp"),
			time_spmv([&cusparse_handle, &cusparse_descr, &d_csr_matrix, &d_x, &d_y] 
					  {blas::cusparse::spmv_mp(cusparse_handle, cusparse_descr, d_csr_matrix, d_x, d_y); throw_on_cuda_error(cudaDeviceSynchronize()); }, 
				setting.num_iterations));

		b_result.push_back(m_result);
	}

	return b_result;
}

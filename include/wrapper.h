#pragma once

#include <thrust/device_vector.h>
#include <cusp/csr_matrix.h>
#include <cusp/multiply.h>
#include <cusp/array1d.h>
#include <cusparse_v2.h>
#include <yao/cusparse/cusparse_error.h>
#include <type_traits>

#include "mkl_spmv.h"

namespace blas
{
	namespace mkl
	{
		template <typename host_matrix_t, typename host_vector_t>
		void spmv(host_matrix_t &host_matrix, host_vector_t &x, host_vector_t &y)
		{
			// TODO check index_type and value_type
			//using index_type = host_matrix_t::index_type;
			//using value_type = host_matrix_t::value_type;

			spmv(
				host_matrix.num_rows,
				host_matrix.num_cols,
				thrust::raw_pointer_cast(host_matrix.values.data()),
				thrust::raw_pointer_cast(host_matrix.row_offsets.data()),
				thrust::raw_pointer_cast(host_matrix.column_indices.data()),
				thrust::raw_pointer_cast(x.data()),
				thrust::raw_pointer_cast(y.data())
			);
		}
	}

	namespace cusp
	{
		template <typename device_matrix_t, typename device_vector_t>
		void spmv(device_matrix_t &device_matrix, device_vector_t &x, device_vector_t &y)
		{
			::cusp::array1d_view<typename thrust::device_vector<float>::iterator> x_view(x.begin(), x.end());
			::cusp::array1d_view<typename thrust::device_vector<float>::iterator> y_view(y.begin(), y.end());
			::cusp::multiply(device_matrix, x_view, y_view);
		}
	}

	namespace cusparse
	{
		cusparseHandle_t create_handle()
		{
			cusparseHandle_t handle;

			throw_on_cusparse_error(cusparseCreate(&handle));

			return handle;
		}

		// Only support device matrix
		template <typename index_type, typename value_type>
		cusparseMatDescr_t create_mat_descr(::cusp::csr_matrix<index_type, value_type, ::cusp::device_memory>&)
		{
			cusparseMatDescr_t descr = 0;
			throw_on_cusparse_error(cusparseCreateMatDescr(&descr));

			cusparseSetMatType(descr, CUSPARSE_MATRIX_TYPE_GENERAL);
			cusparseSetMatIndexBase(descr, CUSPARSE_INDEX_BASE_ZERO);

			return descr;
		}

		// Only enabled when value_type is float
		// TODO use tag-dispatching to deal with float, double and complex
		template <typename device_matrix_t, typename device_vector_t>
		void spmv(cusparseHandle_t handle, cusparseMatDescr_t descr, device_matrix_t &device_matrix, device_vector_t &x, device_vector_t &y,
		 typename std::enable_if<
			std::is_same<typename device_matrix_t::value_type, float>::value, 
			void>::type * = nullptr)
		{
			float alpha = 1.0f;
			float beta = 0.0f;
			cusparseScsrmv(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, device_matrix.num_rows, device_matrix.num_cols, device_matrix.num_entries, &alpha,
				descr, thrust::raw_pointer_cast(&device_matrix.values[0]), thrust::raw_pointer_cast(&device_matrix.row_offsets[0]), thrust::raw_pointer_cast(&device_matrix.column_indices[0]),
				thrust::raw_pointer_cast(&x[0]), &beta, thrust::raw_pointer_cast(&y[0]));
		}
		

		template <typename device_matrix_t, typename device_vector_t>
		void spmv_mp(cusparseHandle_t handle, cusparseMatDescr_t descr, device_matrix_t &device_matrix, device_vector_t &x, device_vector_t &y,
			typename std::enable_if<
			std::is_same<typename device_matrix_t::value_type, float>::value,
			void>::type * = nullptr)
		{
			float alpha = 1.0f;
			float beta = 0.0f;
			cusparseScsrmv_mp(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, device_matrix.num_rows, device_matrix.num_cols, device_matrix.num_entries, &alpha,
				descr, thrust::raw_pointer_cast(&device_matrix.values[0]), thrust::raw_pointer_cast(&device_matrix.row_offsets[0]), thrust::raw_pointer_cast(&device_matrix.column_indices[0]),
				thrust::raw_pointer_cast(&x[0]), &beta, thrust::raw_pointer_cast(&y[0]));
		}
	}
}
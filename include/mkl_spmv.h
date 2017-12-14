#pragma once
#include <mkl_types.h>


namespace blas
{
	namespace mkl
	{
		void spmv(MKL_INT m,
			double values[],
			MKL_INT row_offsets[],
			MKL_INT column_indices[],
			double x[],
			double y[]);

		void spmv(MKL_INT m,
			float values[],
			MKL_INT row_offsets[],
			MKL_INT column_indices[],
			float x[],
			float y[]);

		//template <typename host_matrix_t, typename host_vector_t>
		//void spmv(host_matrix_t host_matrix, host_vector_t x, host_vector_t y)
		//{
		//	using index_type = host_matrix_t::index_type;
		//	using value_type = host_matrix_t::value_type;

		//	index_type m = host_matrix.num_rows;
		//}
	}
}
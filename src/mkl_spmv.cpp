#include "mkl_spmv.h"

#include <mkl.h>
#include <mkl_spblas.h>


namespace blas
{
	namespace mkl
	{
		void spmv(MKL_INT m,
			MKL_INT n,
			double values[],
			MKL_INT row_offsets[],
			MKL_INT column_indices[],
			double x[],
			double y[])
		{
			sparse_matrix_t A;
			mkl_sparse_d_create_csr(&A, SPARSE_INDEX_BASE_ZERO, m, n, row_offsets, row_offsets+1, column_indices, values);

			matrix_descr desr;
			desr.type = SPARSE_MATRIX_TYPE_GENERAL;
			mkl_sparse_d_mv(SPARSE_OPERATION_NON_TRANSPOSE, 1.0f, A, desr, x, 0.0f, y);
		}

		void spmv(MKL_INT m,
			MKL_INT n,
			float values[],
			MKL_INT row_offsets[],
			MKL_INT column_indices[],
			float x[],
			float y[])
		{
			sparse_matrix_t A;
			mkl_sparse_s_create_csr(&A, SPARSE_INDEX_BASE_ZERO, m, n, row_offsets, row_offsets+1, column_indices, values);

			matrix_descr desr;
			desr.type = SPARSE_MATRIX_TYPE_GENERAL;
			mkl_sparse_s_mv(SPARSE_OPERATION_NON_TRANSPOSE, 1.0f, A, desr, x, 0.0f, y);
		}
	}
}
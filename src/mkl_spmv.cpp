#include "mkl_spmv.h"

#include <mkl.h>


namespace blas
{
	namespace mkl
	{
		void spmv(MKL_INT m,
			double values[],
			MKL_INT row_offsets[],
			MKL_INT column_indices[],
			double x[],
			double y[])
		{
			char trans = 'n';
			mkl_cspblas_dcsrgemv(&trans, &m, values, row_offsets, column_indices, x, y);
		}

		void spmv(MKL_INT m,
			float values[],
			MKL_INT row_offsets[],
			MKL_INT column_indices[],
			float x[],
			float y[])
		{
			char trans = 'n';
			mkl_cspblas_scsrgemv(&trans, &m, values, row_offsets, column_indices, x, y);
		}
	}
}
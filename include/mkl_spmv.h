#pragma once
#include <mkl_types.h>


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
			double y[]);

		void spmv(MKL_INT m,
			MKL_INT n,
			float values[],
			MKL_INT row_offsets[],
			MKL_INT column_indices[],
			float x[],
			float y[]);
	}
}
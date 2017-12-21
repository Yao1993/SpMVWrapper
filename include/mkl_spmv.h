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
	}
}
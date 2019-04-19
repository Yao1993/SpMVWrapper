#pragma once
#include <string>

struct matrix_info_t
{
	int num_rows;
	int num_cols;
	size_t nnz;
	std::string data_filename;
};
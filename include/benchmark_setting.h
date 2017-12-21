#pragma once 
#include <string>
#include <vector>

#include "matrix_info.h"

struct benchmark_setting
{
	std::vector<matrix_info> matrices;
	std::vector<std::string> matrix_path;
	int num_iterations;
};
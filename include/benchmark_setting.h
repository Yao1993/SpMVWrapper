#pragma once 
#include <string>
#include <vector>

#include "matrix_info.h"

struct benchmark_setting_t
{
	std::vector<matrix_info_t> matrices;
	std::vector<std::string> matrix_path;
	int num_iterations;
	float value_threshold;
};
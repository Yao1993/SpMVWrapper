#pragma once
#include <vector>
#include <string>


struct matrix_info
{
	int num_rows;
	int num_cols;
	std::string data_filename;
};

struct benchmark_setting
{
	std::vector<matrix_info> matrices;
	std::vector<std::string> matrix_path;
	int num_iterations;
};

benchmark_setting parse_json(std::string json_filename);
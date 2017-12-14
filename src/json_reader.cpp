#include "json_reader.h"
#include <fstream>
#include <json.hpp>

using nlohmann::json;

// For matrix_info
void to_json(json& j, const matrix_info& info) 
{
	j = json{ { "num_rows", info.num_rows },{ "num_cols", info.num_rows },{ "data_filename", info.num_rows } };
}

void from_json(const json& j, matrix_info& info) 
{
	info.num_rows = j.at("num_rows").get<int>();
	info.num_cols = j.at("num_cols").get<int>();
	info.data_filename = j.at("data_filename").get<std::string>();
}

// For benchmarksetting
void to_json(json& j, const benchmark_setting& s)
{
	j = json{ { "num_iterations", s.num_iterations },{ "matrix_path", s.matrix_path },{ "matrices", s.matrices } };
}

void from_json(const json& j, benchmark_setting& s) 
{
	s.num_iterations = j.at("num_iterations").get<int>();
	s.matrix_path = j.at("matrix_path").get<std::vector<std::string>>();
	s.matrices = j.at("matrices").get<std::vector<matrix_info>>();
}



benchmark_setting parse_json(std::string json_filename)
{
	std::ifstream input_file(json_filename);
	json input_json;
	input_file >> input_json;

	benchmark_setting setting = input_json;

	return setting;
}

#include "json_io.h"
#include <fstream>
#include <nlohmann/json.hpp>

using nlohmann::json;

// For matrix_info_t
void to_json(json& j, const matrix_info_t& info) 
{
	j = json{ { "num_rows", info.num_rows },{ "num_cols", info.num_cols },{ "nnz", info.nnz },{ "data_filename", info.data_filename } };
}

void from_json(const json& j, matrix_info_t& info) 
{
	info.num_rows = j.at("num_rows").get<int>();
	info.num_cols = j.at("num_cols").get<int>();
	info.data_filename = j.at("data_filename").get<std::string>();
}

// For benchmarksetting
void to_json(json& j, const benchmark_setting_t& s)
{
	j = json{ { "num_iterations", s.num_iterations },{ "matrix_path", s.matrix_path },{ "matrices", s.matrices }, {"value_threshold", s.value_threshold} };
}

void from_json(const json& j, benchmark_setting_t& s) 
{
	s.num_iterations = j.at("num_iterations").get<int>();
	s.matrix_path = j.at("matrix_path").get<std::vector<std::string>>();
	s.matrices = j.at("matrices").get<std::vector<matrix_info_t>>();
    s.value_threshold = j.at("value_threshold").get<float>();
}

//For matrix_result
void to_json(json& j, const matrix_result_t& result)
{
	j = json{ { "matrix", result.matrix },{ "time", result.time }};
}



benchmark_setting_t parse_json(std::string json_filename)
{
	std::ifstream input_file(json_filename);
	json input_json;
	input_file >> input_json;

	benchmark_setting_t setting = input_json;

	return setting;
}

void dump_json(benchmark_result_t result, std::string filename)
{
	std::ofstream output_file(filename);
	json output_json = result;

	output_file << output_json;
}
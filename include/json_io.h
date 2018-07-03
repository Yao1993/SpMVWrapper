#pragma once
#include <vector>
#include <string>

#include "benchmark_setting.h"
#include "benchmark_result.h"

benchmark_setting_t parse_json(std::string json_filename);

void dump_json(benchmark_result_t result, std::string filename="time.json");
#pragma once
#include <vector>
#include <string>

#include "benchmark_setting.h"
#include "benchmark_result.h"

benchmark_setting parse_json(std::string json_filename);

void dump_json(benchmark_result result, std::string filename="time.json");
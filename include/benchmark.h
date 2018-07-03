#pragma once

// CANNOT include json.hpp in cu file
#include "benchmark_setting.h"
#include "benchmark_result.h"
 

// Note when using nvcc, json.hpp not compatible with nvcc, 
// so we must to seprate the json_reader.cpp and benchmark.cpp
benchmark_result_t start_benchmark(benchmark_setting_t &setting);
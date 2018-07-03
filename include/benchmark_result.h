#pragma once
#include <vector>

#include "matrix_info.h"
#include <unordered_map>

struct matrix_result_t
{
    matrix_info_t matrix;
    std::unordered_map<std::string, double> time;
    
    matrix_result_t(matrix_info_t m) : matrix(m) {}
};

using benchmark_result_t = std::vector<matrix_result_t>;

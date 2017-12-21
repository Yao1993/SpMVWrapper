#pragma once
#include <vector>

#include "matrix_info.h"

struct matrix_result
{
    matrix_info matrix;
    std::vector<std::pair<std::string, double>> time;
    
    matrix_result(matrix_info m) : matrix(m) {}
};

using benchmark_result = std::vector<matrix_result>;

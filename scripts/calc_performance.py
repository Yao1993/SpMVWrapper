import json


def calc_performance(m, n, nnz, time, size_of_index_type=4, size_of_value_type=4):
    gb = (m + 1 + nnz) * size_of_index_type + (m + n + nnz) * size_of_index_type
    gflop = 2 * nnz

    return gb / (1e6 * time), gflop / (1e6 * time)

if __name__ == "__main__":
    benchmark_result_file = "time.json"
    with open(benchmark_result_file) as f:
        benchmark_result = json.load(f)
    
    for matrix_result in benchmark_result:
        matrix_info = matrix_result["matrix"]
        print(matrix_info["data_filename"])
        print("------------------------------------------")
        m = matrix_info["num_rows"]
        n = matrix_info["num_cols"]
        nnz = matrix_info["nnz"]
        
        for library, time in matrix_result["time"].items():
            print(library)
            print("{} GB/s, {} GFlops".format(*calc_performance(m, n, nnz, time)))

        print("===========================================")

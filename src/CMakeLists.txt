include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(mkl_spmv mkl_spmv.cpp)
target_link_libraries(mkl_spmv  TBB::tbb  "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2019/windows/mkl/lib/intel64_win/mkl_tbb_thread.lib" 
                                          "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2019/windows/mkl/lib/intel64_win/mkl_core.lib"
                                          "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2019/windows/mkl/lib/intel64_win/mkl_intel_lp64.lib"
                                          "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2019/windows/mkl/lib/intel64_win/mkl_intel_thread.lib"
                                          "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2019/windows/compiler/lib/intel64_win/libiomp5md.lib"
                                          
)

add_library(json_io json_io.cpp)
add_dependencies(json_io json)

add_library(benchmark benchmark.cu)
add_dependencies(benchmark cusplibrary)
target_link_libraries(benchmark mkl_spmv cusparse)

add_executable(spmv_ctl spmv_ctl.cpp)
target_link_libraries(spmv_ctl json_io benchmark)

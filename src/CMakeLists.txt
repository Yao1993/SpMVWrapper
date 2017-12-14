include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(mkl_spmv mkl_spmv.cpp)
target_link_libraries(mkl_spmv ${MKL_LP_INTELTHREAD_LIBRARIES} "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2018.0.124/windows/compiler/lib/intel64_win/libiomp5md.lib")

add_library(json_reader json_reader.cpp)
add_dependencies(json_reader json)

add_executable(spmv_ctl spmv_ctl.cpp)
target_link_libraries(spmv_ctl mkl_spmv json_reader)

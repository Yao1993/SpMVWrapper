include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(json_io json_io.cpp)
add_dependencies(json_io json)

add_library(benchmark benchmark.cu)
add_dependencies(benchmark cusplibrary)
target_link_libraries(benchmark cusparse)

add_executable(spmv_ctl spmv_ctl.cpp)
target_link_libraries(spmv_ctl json_io benchmark)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(mkl_spmv mkl_spmv.cpp)
target_link_libraries(mkl_spmv MKL::MKL)

add_library(json_io json_io.cpp)
add_dependencies(json_io json yao)

add_library(benchmark benchmark.cu)
add_dependencies(benchmark cusplibrary)
target_link_libraries(benchmark cusparse TBB::tbb VTune::VTune mkl_spmv)


add_executable(spmv_ctl spmv_ctl.cpp)
target_link_libraries(spmv_ctl json_io benchmark VTune::VTune)



if(MSVC)
    set_property(TARGET spmv_ctl APPEND PROPERTY LINK_FLAGS /DEBUG)
endif()
cmake_minimum_required(VERSION 3.10)

project(SpMVWrapper LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler ${OpenMP_CXX_FLAGS}")
    message("${CMAKE_CUDA_FLAGS}")
endif()


# Compiler Options
set(CMAKE_CUDA_FLAGS "-gencode arch=compute_61,code=sm_61 -gencode arch=compute_52,code=sm_52 
                      -Xcompiler -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_CUDA 
                      -Xcompiler -DCUSP_DEVICE_BLAS_SYSTEM=CUSP_DEVICE_BLAS_CUBLAS 
                      -Xcompiler -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_OMP                       
                      ${CMAKE_CUDA_FLAGS}")


if (WIN32)
    set(CMAKE_CUDA_FLAGS "-Xcompiler \"/wd 4819\" ${CMAKE_CUDA_FLAGS}")
endif (WIN32)

# Output Directory
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Dependencies
include(./dependencies/CMakeLists.txt)

# MKL package
list(APPEND CMAKE_MODULE_PATH C:/MyLib/CMake)
find_package(MKL REQUIRED)
include_directories(${MKL_INCLUDE_DIR})

add_subdirectory(src)

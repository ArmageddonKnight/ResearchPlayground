cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(cuda_stream LANGUAGES CXX CUDA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -O2 -std=c++11 -Wall")

add_subdirectory(src)

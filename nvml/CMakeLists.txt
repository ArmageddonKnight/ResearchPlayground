cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(CMAKE_C_STANDARD 11)
project(nvrtc_dp LANGUAGES CXX CUDA)

add_executable(used_gpu_memory used_gpu_memory.cu)

target_include_directories(used_gpu_memory PUBLIC
    /usr/local/cuda/samples/common/inc)
target_link_libraries(used_gpu_memory PUBLIC -lnvidia-ml)

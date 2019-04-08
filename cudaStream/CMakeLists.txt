cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(cuda_stream LANGUAGES CXX CUDA)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

add_subdirectory(src)

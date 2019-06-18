add_executable(dynamic_parallelism dynamic_parallelism.cpp)

target_compile_features   (dynamic_parallelism PUBLIC cxx_std_11)
target_include_directories(dynamic_parallelism PUBLIC
        /usr/local/cuda/include
        /usr/local/cuda/samples/common/inc)
target_link_libraries     (dynamic_parallelism PUBLIC -lnvrtc -lcuda)

set_target_properties(dynamic_parallelism PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/../bin)

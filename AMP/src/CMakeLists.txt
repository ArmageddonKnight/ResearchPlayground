add_executable(vecadd vecadd.cu)

target_compile_features   (vecadd PUBLIC cxx_std_11)
target_include_directories(vecadd PUBLIC
        /usr/local/cuda/include
        /usr/local/cuda/samples/common/inc)

set_target_properties(vecadd PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY 
        ${CMAKE_CURRENT_BINARY_DIR}/../bin)

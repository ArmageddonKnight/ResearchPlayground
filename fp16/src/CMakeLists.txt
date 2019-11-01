add_executable(vecadd vecadd.cu)

target_include_directories(vecadd PUBLIC
    /usr/local/cuda/samples/common/inc)

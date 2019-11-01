add_executable(nvrtc_dp nvrtc_dp.cu)

target_include_directories(nvrtc_dp PUBLIC
    /usr/local/cuda/samples/common/inc)
target_link_libraries(nvrtc_dp PUBLIC -lnvrtc)

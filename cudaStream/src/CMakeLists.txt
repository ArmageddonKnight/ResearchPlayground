file(GLOB MAIN_CXX_SOURCES *.cpp)

add_executable(cudaStream_main ${MAIN_CXX_SOURCES})

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS program_options REQUIRED)
target_link_libraries(cudaStream_main PUBLIC ${Boost_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
	-I${CMAKE_SOURCE_DIR}/../cuda-samples/Common \
	-I/usr/local/cuda/include \
	-I/usr/local/cuda/extras/CUPTI/include")

set_target_properties(cudaStream_main PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
set_target_properties(cudaStream_main PROPERTIES 
	RUNTIME_OUTPUT_NAME cudaStreamMB
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

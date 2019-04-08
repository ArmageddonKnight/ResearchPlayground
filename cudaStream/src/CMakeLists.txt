file(GLOB MAIN_CXX_SOURCES *cu *.cpp)

add_executable(cudaStream_main ${MAIN_CXX_SOURCES})

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS program_options REQUIRED)

target_compile_features   (cudaStream_main PUBLIC cxx_std_11)
target_include_directories(cudaStream_main PUBLIC
	${CMAKE_SOURCE_DIR}/../cuda-samples/Common 
	/usr/local/cuda/include 
	/usr/local/cuda/extras/CUPTI/include)
target_link_libraries     (cudaStream_main PUBLIC 
	-lcublas ${Boost_LIBRARIES})

set_target_properties(cudaStream_main PROPERTIES 
	RUNTIME_OUTPUT_NAME cudaStreamMB
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#include <cublas.h>
#include <cupti.h>

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <iostream>
#include <boost/program_options.hpp>

#include "helper_cuda.h"

int main(int argc, char * argv[])
{
	using namespace boost::program_options;

	options_description desc ("cudaStream Microbenchmark Program Options");

	desc.add_options()
		("help,h", "Helping Message")
		("batch-size", value < std::size_t > (), "Batch Size")
		("input-size", value < std::size_t > (), "Input Size")
		("state-size", value < std::size_t > (), "State Size");
	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);

	if (!vm.count("batch-size") || 
	    !vm.count("input-size") || 
	    !vm.count("state-size"))
	{
		std::cerr << "Tensor shapes must be provided." << std::endl;
		exit(EXIT_FAILURE);
	} 

	std::size_t batch_size = vm["batch-size"].as < std::size_t > (), 
	            input_size = vm["input-size"].as < std::size_t > (), 
		    state_size = vm["state-size"].as < std::size_t > ();

	thrust::host_vector < float > I     (batch_size * input_size, 1.0f);
	thrust::host_vector < float > H     (batch_size * input_size, 1.0f);
	thrust::host_vector < float > W_I2H (state_size * input_size, 1.0f);
	thrust::host_vector < float > W_H2H (state_size * input_size, 1.0f);
	thrust::host_vector < float > Y_I   (batch_size * state_size, 0.0f);
	thrust::host_vector < float > Y_H   (batch_size * state_size, 0.0f);



}
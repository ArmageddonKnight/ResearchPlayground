#include <iostream>
// Program Options
#include <boost/program_options.hpp>
// CUDA Headers
#include <cublas_v2.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
// Helper Functions
#include "helper_cuda.h"

int main(int argc, char * argv[])
{
        using namespace boost::program_options;

        options_description desc ("cudaStream Microbenchmark Program Options");

        desc.add_options()
                ("help,h", "Helping Message")
                ("batch-size,b", value < std::size_t > (), "Batch Size")
                ("input-size,i", value < std::size_t > (), "Input Size");
        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);

        if (!vm.count("batch-size") || !vm.count("input-size"))
        {
                std::cerr << "[ERROR] Tensor shapes must be provided." << std::endl;
                exit(EXIT_FAILURE);
        } 

        std::size_t batch_size = vm["batch-size"].as < std::size_t > (), 
                    input_size = vm["input-size"].as < std::size_t > ();
        std::size_t state_size = 4 * input_size;

        std::cout << "[INFO] B = " << batch_size << ", "
                            "I = " << input_size << ", "
                            "H = " << state_size << std::endl;

        thrust::device_vector < float > I     (batch_size * input_size, 1.0f);
        thrust::device_vector < float > H     (batch_size * input_size, 1.0f);
        thrust::device_vector < float > W_I2H (state_size * input_size, 1.0f);
        thrust::device_vector < float > W_H2H (state_size * input_size, 1.0f);
        thrust::device_vector < float > Y_I   (batch_size * state_size, 0.0f);
        thrust::device_vector < float > Y_H   (batch_size * state_size, 0.0f);

        // =====================================================================
        // Baseline (Default Stream)
        // =====================================================================

        struct cublasHandleWrapper
        {
        private:
                cublasHandle_t handle;
        public:
                cublasHandleWrapper() { checkCudaErrors(cublasCreate(&handle)); }
               ~cublasHandleWrapper() { checkCudaErrors(cublasDestroy(handle)); }
                operator cublasHandle_t() { return handle; }
        };

        cublasHandleWrapper cublas_handle; const float alpha = 1.0f, beta = 0.0f;
        
        // =====================================================================

        checkCudaErrors(cublasSetStream(cublas_handle, nullptr));
        checkCudaErrors(cublasSgemm(cublas_handle,
                        CUBLAS_OP_T, 
                        CUBLAS_OP_N,
                        state_size, 
                        batch_size,
                        input_size,
                        &alpha, 
                        W_I2H.data().get(), input_size, 
                        I    .data().get(), input_size,
                        &beta, 
                        Y_I  .data().get(), state_size));
        checkCudaErrors(cublasSetStream(cublas_handle, nullptr));
        checkCudaErrors(cublasSgemm(cublas_handle,
                        CUBLAS_OP_T, 
                        CUBLAS_OP_N,
                        state_size, 
                        batch_size,
                        input_size,
                        &alpha, 
                        W_H2H.data().get(), input_size, 
                        H    .data().get(), input_size,
                        &beta, 
                        Y_H  .data().get(), state_size));
        checkCudaErrors(cudaStreamSynchronize(nullptr));

        // =====================================================================
        // Multi-Stream Version
        // =====================================================================

        struct cudaStreamWrapper
        {
                cudaStream_t stream;
                
                cudaStreamWrapper(int priority = 0)
                {
                        checkCudaErrors(cudaStreamCreateWithPriority(&stream, cudaStreamNonBlocking, priority));
                }
               ~cudaStreamWrapper() { checkCudaErrors(cudaStreamDestroy(stream)); }
                operator cudaStream_t() { return stream; }
        };

        cudaStreamWrapper i2h_stream, h2h_stream;

        // =====================================================================

        checkCudaErrors(cublasSetStream(cublas_handle, i2h_stream));
        checkCudaErrors(cublasSgemm(cublas_handle,
                        CUBLAS_OP_T, 
                        CUBLAS_OP_N,
                        state_size, 
                        batch_size,
                        input_size,
                        &alpha, 
                        W_I2H.data().get(), input_size, 
                        I    .data().get(), input_size,
                        &beta, 
                        Y_I  .data().get(), state_size));
        checkCudaErrors(cublasSetStream(cublas_handle, h2h_stream));
        checkCudaErrors(cublasSgemm(cublas_handle,
                        CUBLAS_OP_T, 
                        CUBLAS_OP_N,
                        state_size, 
                        batch_size,
                        input_size,
                        &alpha, 
                        W_H2H.data().get(), input_size, 
                        H    .data().get(), input_size,
                        &beta, 
                        Y_H  .data().get(), state_size));

        checkCudaErrors(cudaStreamSynchronize(i2h_stream));
        checkCudaErrors(cudaStreamSynchronize(h2h_stream));

        return 0;
}

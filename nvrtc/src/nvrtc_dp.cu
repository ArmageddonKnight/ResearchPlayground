#include <cstddef>
#include <iostream>

#include <cuda.h>
#include <nvrtc_helper.h>  // nvrtc.h

const char * const nvrtc_dp = "                                                 \n\
__global__ void child(float * out, std::size_t n)                               \n\
{                                                                               \n\
        std::size_t g_threadIdx = blockIdx.x +                                  \n\
                                  blockDim.x * threadIdx.x;                     \n\
        if (g_threadIdx < n)                                                    \n\
        {                                                                       \n\
                out[g_threadIdx] = g_threadIdx;                                 \n\
        }                                                                       \n\
}                                                                               \n\
__global__ void parent(float * out,                                             \n\
        std::size_t n,                                                          \n\
        std::size_t num_blocks,                                                 \n\
        std::size_t num_threads)                                                \n\
{                                                                               \n\
        child <<< num_blocks, num_threads >>> (out, n);                         \n\
        cudaDeviceSynchronize();                                                \n\
}                                                                               \n";

int main(int argc, char * argv[])
{
        std::size_t num_blocks = 32, num_threads = 128;

        nvrtcProgram prog;
}

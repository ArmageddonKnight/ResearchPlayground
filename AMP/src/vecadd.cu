#include <cstddef>
#include <iostream>

#include <cuda_fp16.h>
#include <thrust/device_vector.h>

#include <helper_cuda.h>

template < typename DTypeT, std::size_t N >
__global__ void cudaVecAdd(
        const DTypeT * const A,
        const DTypeT * const B,
              DTypeT * const C)
{
        const unsigned g_threadIdx = threadIdx.x + blockIdx.x * blockDim.x;

        if (g_threadIdx < N)
        {
                C[g_threadIdx] = A[g_threadIdx] + B[g_threadIdx];
        }
}

template < typename DTypeT >
std::ostream & operator<<(std::ostream & cout_,
        const thrust::device_vector < 
                DTypeT > & dev_vec)
{
        cout_ << "[" << std::endl;
        for (std::size_t i = 0; i < (dev_vec.size() + 10 - 1) / 10; ++i)
        {
                if (i * 10 >= dev_vec.size())
                {
                        break;
                }
                cout_ << "\t";
                for (std::size_t j = 0; j < 10; ++j)
                {
                        if (i * 10 + j >= dev_vec.size())
                        {
                                break;
                        }
                        cout_ << (dev_vec[i * 10 + j]) << ", ";
                }
                cout_ << std::endl;
        }
        cout_ << "]";
        return cout_;
}

/// \brief Top-Level Vector-Add Benchmark
template < typename DTypeT, std::size_t SizeT >
void vecadd()
{
        thrust::device_vector < DTypeT > A (SizeT, 1);
        thrust::device_vector < DTypeT > B (SizeT, 1);
        thrust::device_vector < DTypeT > C (SizeT, 0);

        const std::size_t threads_per_block = 32;
        const std::size_t blocks_per_grid = (SizeT + threads_per_block - 1) / threads_per_block;
        cudaVecAdd < DTypeT, SizeT > 
                <<< blocks_per_grid, 
                    threads_per_block >>> 
                (A.data().get(), 
                 B.data().get(), 
                 C.data().get());
        checkCudaErrors(cudaDeviceSynchronize());
        std::cout << C << std::endl;
}

int main()
{
        vecadd < float, 100 > ();
        vecadd < half,  100 > ();

        return 0;
}

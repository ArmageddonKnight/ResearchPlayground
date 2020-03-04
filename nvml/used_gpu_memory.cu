#include <vector>
#include <iostream>
#include <cuda_runtime.h>
#include <nvml.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
        size_t alloc_size = 30000000; 
        void * alloc_dptr = nullptr;

        nvmlDevice_t nvml_device;
        nvmlReturn_t nvml_retval;
        unsigned info_count = 0;
        std::vector < nvmlProcessInfo_t > infos;
        
        cudaMalloc(&alloc_dptr, alloc_size);

        nvmlInit();
        nvmlDeviceGetHandleByIndex(0, &nvml_device);
        do {
                std::cout << "Info count: " << info_count << std::endl;
                infos = std::vector < nvmlProcessInfo_t > (info_count);
                nvml_retval = nvmlDeviceGetComputeRunningProcesses(nvml_device, &info_count, infos.data());
                std::cout << "NVML Return Val: "
                          << nvml_retval << std::endl;
                // ++info_count;
        } while (nvml_retval != NVML_SUCCESS);
        for (unsigned i = 0; i < info_count; ++i) 
        {
                std::cout << "PID " << infos[i].pid << " uses GPU memory "
                          << (infos[i].usedGpuMemory) / 1e6 << " MiB" << std::endl;
        }

        size_t free, total;
        cudaMemGetInfo(&free, &total);
        std::cout << "Current PID " << getpid() << " uses GPU memory "
                  << (total - free) / 1e6 << " MiB" << std::endl;

        do {

        } while (true);

        cudaFree(alloc_dptr);
        return 0;
}

#include <sys/ipc.h>
#include <sys/shm.h>

// standard C/C++ headers
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <time.h>
#include <sys/time.h>

// opencl harness headers
#include <cmath>
#include "xcl2.hpp"
#include <algorithm>
#include <vector>
#include <chrono>

#include "ap_int.h"
#define DATA_SIZE 1024 * 1024

class Timer {
  std::chrono::high_resolution_clock::time_point mTimeStart;

public:
  Timer() { reset(); }
  long long stop() {
    std::chrono::high_resolution_clock::time_point timeEnd =
        std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(timeEnd -
                                                                 mTimeStart)
        .count();
  }
  void reset() { mTimeStart = std::chrono::high_resolution_clock::now(); }
};

int main(int argc, char ** argv) {
                
  std::vector<int, aligned_allocator<int>> input(DATA_SIZE);
  std::vector<int, aligned_allocator<int>> output(10);
  std::generate(input.begin(), input.end(), std::rand);
  for (int k = 0; k < DATA_SIZE; k++) {
      input[k] = input[k] % 10;
  }

  std::string binaryFile = "kernel.xclbin";
  size_t vector_size_bytes = sizeof(int) * DATA_SIZE;
  cl_int err;
  cl::Context context;
  cl::Kernel krnl;
  cl::CommandQueue q;

  auto devices = xcl::get_xil_devices();
  // read_binary_file() is a utility API which will load the binaryFile
  // and will return the pointer to file buffer.
  auto fileBuf = xcl::read_binary_file(binaryFile);
  cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};
  int valid_device = 0;
  for (unsigned int i = 0; i < devices.size(); i++) {
    auto device = devices[i];
    // Creating Context and Command Queue for selected Device
    OCL_CHECK(err, context = cl::Context(device, NULL, NULL, NULL, &err));
    OCL_CHECK(err, q = cl::CommandQueue(context, device,
                                        CL_QUEUE_PROFILING_ENABLE, &err));
    std::cout << "Trying to program device[" << i
              << "]: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    cl::Program program(context, {device}, bins, NULL, &err);
    if (err != CL_SUCCESS) {
      std::cout << "Failed to program device[" << i << "] with xclbin file!\n";
    } else {
      std::cout << "Device[" << i << "]: program successful!\n";
      OCL_CHECK(err, krnl = cl::Kernel(program, "test", &err));
      valid_device++;
      break; // we break because we found a valid device
    }
  }
  if (valid_device == 0) {
    std::cout << "Failed to program any device found, exit!\n";
    exit(EXIT_FAILURE);
  }

  // Allocate Buffer in Global Memory
  // Buffers are allocated using CL_MEM_USE_HOST_PTR for efficient memory and
  // Device-to-host communication
  OCL_CHECK(err, cl::Buffer buffer_input(
                     context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
                     vector_size_bytes, input.data(), &err));

  OCL_CHECK(err, cl::Buffer buffer_output(
                     context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY,
                     sizeof(int) * 10, output.data(), &err));

  OCL_CHECK(err, err = krnl.setArg(0, buffer_input));
  OCL_CHECK(err, err = krnl.setArg(1, buffer_output));

  // Copy input data to device global memory
  Timer fpga_timer;
  OCL_CHECK(err, err = q.enqueueMigrateMemObjects(
	{buffer_input},
        0 /* 0 means from host*/));

  // Launch the Kernel
  // For HLS kernels global and local size is always (1,1,1). So, it is
  // recommended
  // to always use enqueueTask() for invoking HLS kernel

  OCL_CHECK(err, err = q.enqueueTask(krnl));
  q.finish();


  // Copy Result from Device Global Memory to Host Local Memory
  OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_output},
                                                  CL_MIGRATE_MEM_OBJECT_HOST));
  q.finish();
  // OPENCL HOST CODE AREA END

  long long fpga_timer_stop = fpga_timer.stop();
  std::cout << "Total time " << fpga_timer_stop * 0.001 << " ms\n";


  }

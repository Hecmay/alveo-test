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
#include <random>

#include "ap_int.h"

typedef ap_uint<1> bit1;
typedef ap_uint<2> bit2;
typedef ap_uint<8> bit8;
typedef ap_uint<16> bit16;
typedef ap_uint<32> bit32;

#define K    16
#define N    320
#define D    32

#define SIZE N * D
#define OUTPUT 16 * 32

#define MAX_HBM_BANKCOUNT 32
#define BANK_NAME(n) n | XCL_MEM_TOPOLOGY
const int bank[MAX_HBM_BANKCOUNT] = {
    BANK_NAME(0),  BANK_NAME(1),  BANK_NAME(2),  BANK_NAME(3),  BANK_NAME(4),
    BANK_NAME(5),  BANK_NAME(6),  BANK_NAME(7),  BANK_NAME(8),  BANK_NAME(9),
    BANK_NAME(10), BANK_NAME(11), BANK_NAME(12), BANK_NAME(13), BANK_NAME(14),
    BANK_NAME(15), BANK_NAME(16), BANK_NAME(17), BANK_NAME(18), BANK_NAME(19),
    BANK_NAME(20), BANK_NAME(21), BANK_NAME(22), BANK_NAME(23), BANK_NAME(24),
    BANK_NAME(25), BANK_NAME(26), BANK_NAME(27), BANK_NAME(28), BANK_NAME(29),
    BANK_NAME(30), BANK_NAME(31)};

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
                
  // Prepare input data
  srand (time(NULL));
  std::vector<bit32, aligned_allocator<bit32>> input(SIZE);
  std::vector<bit32, aligned_allocator<bit32>> means(OUTPUT);
  std::vector<bit32, aligned_allocator<bit32>> labels(320);
  for (int i = 0; i < N * D; ++i)
    input[i] = rand() % 100;

  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < D; ++j)
      means[i * D + j] = input[i * D + j];
  }


  std::string binaryFile = "kernel.xclbin";
  size_t input_size_bytes = sizeof(bit32) * SIZE;
  size_t output_size_bytes = sizeof(bit32) * OUTPUT;
  size_t LB_size_bytes = sizeof(bit32) * 320;
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
      OCL_CHECK(err, krnl = cl::Kernel(program, "top", &err));
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
  cl_mem_ext_ptr_t inBufExt, outBufExt, outBufExtLB;

  inBufExt.obj = input.data();
  inBufExt.param = 0;
  inBufExt.flags = bank[0];

  outBufExt.obj = means.data();
  outBufExt.param = 0;
  outBufExt.flags = bank[1];

  outBufExtLB.obj = labels.data();
  outBufExtLB.param = 0;
  outBufExtLB.flags = bank[2];

  OCL_CHECK(err, cl::Buffer input_buffer(
                     context, CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX | CL_MEM_READ_ONLY,
                     input_size_bytes, &inBufExt, &err));

  OCL_CHECK(err, cl::Buffer buffer_output(
                     context, CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX | CL_MEM_READ_WRITE,
                     output_size_bytes, &outBufExt, &err));

  OCL_CHECK(err, cl::Buffer buffer_label(
                     context, CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX | CL_MEM_READ_WRITE,
                     LB_size_bytes, &outBufExtLB, &err));

  OCL_CHECK(err, err = krnl.setArg(0, input_buffer));
  OCL_CHECK(err, err = krnl.setArg(1, buffer_output));
  OCL_CHECK(err, err = krnl.setArg(2, buffer_label));

  // Copy input data to device global memory
  OCL_CHECK(err, err = q.enqueueMigrateMemObjects(
	{input_buffer, buffer_output},
        0 /* 0 means from host*/));

  // Launch the Kernel
  // For HLS kernels global and local size is always (1,1,1). So, it is
  // recommended
  // to always use enqueueTask() for invoking HLS kernel

  Timer fpga_timer;
  OCL_CHECK(err, err = q.enqueueTask(krnl));
  q.finish();

  long long fpga_timer_stop = fpga_timer.stop();
  std::cout << "Total time " << fpga_timer_stop * 0.001 << " ms\n";

  // Copy Result from Device Global Memory to Host Local Memory
  OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_output},
                                                  CL_MIGRATE_MEM_OBJECT_HOST));
  q.finish();
  // OPENCL HOST CODE AREA END



  }

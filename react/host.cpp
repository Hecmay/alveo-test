
#include <sys/ipc.h>
#include <sys/shm.h>

// standard C/C++ headers
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <cassert>

// opencl harness headers
#include "xcl2.hpp"
#include "ap_fixed.h"
#include "ap_int.h"
#include <cmath>
#include <vector>


int main(int argc, char ** argv) {

  std::vector<ap_fixed<32,20>, aligned_allocator<ap_fixed<32,20>>> input_image(3*1024);
  std::vector<ap_fixed<32,20>, aligned_allocator<ap_fixed<32,20>>> fc2(10);

  std::cout << " Initialize RTE...";

  if (argc != 2) {
      std::cout << "Usage: " << argv[0] << " <XCLBIN File>" << std::endl;
      return EXIT_FAILURE;
  }

  auto binaryFile = argv[1];
  cl_int err = CL_SUCCESS;

  // create binary file and program
  auto fileBuf = xcl::read_binary_file(binaryFile);
  cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};

  cl::Context context;
  cl::CommandQueue q;
  cl::Program program;
  auto devices = xcl::get_xil_devices();
  int valid_device = 0;

  for (unsigned int i = 0; i < devices.size(); i++) {
      auto device = devices[i];
      // Creating Context and Command Queue for selected Device
      context = cl::Context(device, NULL, NULL, NULL, &err);
      q = cl::CommandQueue(
          context, device, CL_QUEUE_PROFILING_ENABLE, &err);

      std::cout << "Trying to program device[" << i
                << "]: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
      program = cl::Program(context, {device}, bins, NULL, &err);
      if (err != CL_SUCCESS) {
          std::cout << "Failed to program device[" << i
                    << "] with xclbin file!\n";
      } else {
          std::cout << "Device[" << i << "]: program successful!\n";
          valid_device++;
          break; // we break because we found a valid device
      }
  }
  if (valid_device == 0) {
      std::cout << "Failed to program any device found, exit!\n";
      exit(EXIT_FAILURE);
  }


  // compute and kernel call from host
  ap_int<32> _top;

  cl::Kernel kernel(program, "test", &err);
  cl::Buffer buffer_in(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(ap_fixed<32,20>)*3*1024, input_image.data(), &err);
  cl::Buffer buffer_fc2(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(ap_fixed<32,20>)*1*10, fc2.data(), &err);

  // set device kernel buffer
  err = kernel.setArg(0, buffer_in);
  err = kernel.setArg(1, buffer_fc2);

  OCL_CHECK(err, err = q.enqueueMigrateMemObjects(
    {buffer_in},
        0 /* 0 means from host*/));
  // enqueue kernel function
  std::chrono::duration<double> kernel_time(0);
  auto kernel_start = std::chrono::high_resolution_clock::now();
  cl::Event event;
  err = q.enqueueTask(kernel, NULL, &event);

  err = q.finish();
  auto kernel_end = std::chrono::high_resolution_clock::now();
  kernel_time = std::chrono::duration<double>(kernel_end - kernel_start);
  auto kernel_time_in_sec = kernel_time.count();
  std::cout << "Execution Time:" <<  kernel_time_in_sec;
  err = q.enqueueMigrateMemObjects({buffer_fc2}, CL_MIGRATE_MEM_OBJECT_HOST);

  // execution on host 

  }

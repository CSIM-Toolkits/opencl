#define __CL_ENABLE_EXCEPTIONS

#define PROGRAM_FILE "hello_kernel.cl"
#define KERNEL_FUNC "hello_kernel"

#include <fstream>
#include <iostream>
#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <string.h>


using namespace std;


int main(void) {

   std::vector<cl::Platform> platforms;
   std::vector<cl::Device> devices;
   std::vector<cl::Kernel> allKernels;
   std::string kernelName;
   char msg[16], msg_buffer[16],result[17];


   try {

      // Access all devices in first platform
      cl::Platform::get(&platforms);

      platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
      
      // Create context and access device names
      cl::Context context(devices);

      // Create kernel
      std::ifstream programFile(PROGRAM_FILE);
      std::string programString(std::istreambuf_iterator<char>(programFile),(std::istreambuf_iterator<char>()));
      cl::Program::Sources source(1, std::make_pair(programString.c_str(),programString.length()+1));
      cl::Program program(context, source);
      program.build(devices);
      cl::Kernel kernel(program, KERNEL_FUNC);

     /* Create a buffer to hold the output data */
      cl::Buffer buffer_arg1(context, CL_MEM_READ_WRITE, sizeof(msg_buffer));
      kernel.setArg(0, buffer_arg1);

      cl::CommandQueue queue(context, devices[0]);
      queue.enqueueTask(kernel);

      queue.enqueueReadBuffer(buffer_arg1, CL_TRUE, 0, sizeof(msg), msg);


      printf("Kernel output: %s\n", msg);   


   }
   catch(cl::Error e) {
      cout << e.what() << ": Error code " << e.err() << endl;
   }



   return 0;
}

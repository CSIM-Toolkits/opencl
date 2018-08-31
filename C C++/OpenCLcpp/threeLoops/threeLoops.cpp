#define __CL_ENABLE_EXCEPTIONS

#include <fstream>
#include <iostream>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif


void CL_CALLBACK checkData(cl_event event, cl_int status, void* data) {

   int i;
   float *buffer_data;

   buffer_data = (float*)data;

   for(i=0; i<300; i++) {
         std::cout << "Resultado: " << buffer_data[i] << std::endl;
   }




}

int main() {

   std::vector<cl::Platform> platforms;
   std::vector<cl::Device> devices;
   std::vector<cl::Kernel> allKernels;
   cl_int i;
   cl::Event callbackEvent;

   float result[300];


   try {


      // Place the GPU devices of the first platform into a context
      cl::Platform::get(&platforms);
      platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
      cl::Context context(devices);
      
      // Create and build program
      std::ifstream programFile("threeLoops.cl");
      std::string programString(std::istreambuf_iterator<char>(programFile),(std::istreambuf_iterator<char>()));
      cl::Program::Sources source(1, std::make_pair(programString.c_str(),programString.length()+1));
      cl::Program program(context, source);
      program.build(devices);


      cl::Buffer bufferResult(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(result), result);


      // Create all kernels in program
      program.createKernels(&allKernels);

      allKernels[0].setArg(0,bufferResult);


      // Create queue and enqueue kernel-execution command
      cl::CommandQueue queue(context, devices[0]);

      cl::NDRange offset(0);
      cl::NDRange global_size(300);
      cl::NDRange local_size(50);

      queue.enqueueNDRangeKernel(allKernels[0],offset, global_size,local_size);

      // Read output buffer from kernel
      queue.enqueueReadBuffer(bufferResult, CL_FALSE, 0, sizeof(result), result, NULL, &callbackEvent);

      // Set callback function
      callbackEvent.setCallback(CL_COMPLETE, &checkData, (void*)result);


   }
   catch(cl::Error e) {
      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
   }

   return 0;
}


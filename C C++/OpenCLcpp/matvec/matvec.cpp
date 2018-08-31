#define __CL_ENABLE_EXCEPTIONS

#include <fstream>
#include <iostream>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif


void checkData(cl_event event, cl_int status, void* data) {

   int i;
   float *buffer_data;
   float correct[4] = {84.0, 228.0, 372.0, 516.0}; 

   buffer_data = (float*)data;

   /* Test the result */
   if((buffer_data[0] == correct[0]) && (buffer_data[1] == correct[1])
      && (buffer_data[2] == correct[2]) && (buffer_data[3] == correct[3])) {
      printf("Matrix-vector multiplication successful.\n");
   }
   else {
      printf("Matrix-vector multiplication unsuccessful.\n");
   }

}

int main() {

   std::vector<cl::Platform> platforms;
   std::vector<cl::Device> devices;
   std::vector<cl::Kernel> allKernels;
   cl_int i;
   cl::Event callbackEvent;

   float mat[16], vec[4], result[4];


   try {

   /* Initialize data to be processed by the kernel */
   for(i=0; i<16; i++) {
      mat[i] = i * 2.0f;
   } 
   for(i=0; i<4; i++) {
      vec[i] = i * 3.0f;     
   }


      // Place the GPU devices of the first platform into a context
      cl::Platform::get(&platforms);
      platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
      cl::Context context(devices);
      
      // Create and build program
      std::ifstream programFile("matvec.cl");
      std::string programString(std::istreambuf_iterator<char>(programFile),(std::istreambuf_iterator<char>()));

      cl::Program::Sources source(1, std::make_pair(programString.c_str(),programString.length()+1));
      cl::Program program(context, source);
      program.build(devices);

      cl::Buffer bufferMatrix(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(mat), mat);

      cl::Buffer bufferVector(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(vec), vec);

      cl::Buffer bufferResult(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(result), result);


      // Create all kernels in program
      program.createKernels(&allKernels);

      allKernels[0].setArg(0,bufferMatrix);
      allKernels[0].setArg(1,bufferVector);
      allKernels[0].setArg(2,bufferResult);

      // Create queue and enqueue kernel-execution command
      cl::CommandQueue queue(context, devices[0]);

      cl::NDRange offset(0);
      cl::NDRange global_size(4);
      cl::NDRange local_size(4);

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


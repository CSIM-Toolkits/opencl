#define __CL_ENABLE_EXCEPTIONS

#include <fstream>
#include <iostream>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

void CL_CALLBACK checkData(cl_event event, cl_int status, void* data) {

   float *buffer_data;

   buffer_data = (float*)data;

   std::cout << "Resultado: " <<*buffer_data<<std::endl;


}


int main(void) {
   
   std::vector<cl::Platform> platforms;
   std::vector<cl::Device> devices;
   std::vector<cl::Kernel> allKernels;
   std::string kernelName;
   cl::Event callbackEvent;

   try {
      // Place the GPU devices of the first platform into a context
      cl::Platform::get(&platforms);
      platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);
      cl::Context context(devices);
      
      // Create and build program
      std::ifstream programFile("kernels.cl");
      std::string programString(std::istreambuf_iterator<char>(programFile),(std::istreambuf_iterator<char>()));
      cl::Program::Sources source(1, std::make_pair(programString.c_str(),programString.length()+1));
      cl::Program program(context, source);
      program.build(devices);

      // Create individual kernels
//      cl::Kernel addKernel(program, "add");
//      cl::Kernel subKernel(program, "subtract");
//      cl::Kernel multKernel(program, "multiply");

        float *a,*b,*c;
	float n1=5,n2=4,resultado;
	a=&n1;
	b=&n2;

	//*c = *a + *b;
	//*c = *a - *b;
	//*c = *a / *b;
	//*c = *a * *b;
        // std::cout << "Resultado: " << *c;

     // Create buffer and make it a kernel argument
      cl::Buffer bufferNumA(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(a), a);

      cl::Buffer bufferNumB(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(b), b);

      cl::Buffer bufferNumC(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(c), c);


      // Create all kernels in program
      program.createKernels(&allKernels);
	allKernels[3].setArg(0,bufferNumA);
	allKernels[3].setArg(1,bufferNumB);
	allKernels[3].setArg(2,bufferNumC);

      // Create queue and enqueue kernel-execution command
      cl::CommandQueue queue(context, devices[0]);
      queue.enqueueTask(allKernels[3]);

      // Read output buffer from kernel
      queue.enqueueReadBuffer(bufferNumC, CL_FALSE, 0, sizeof(c), c, NULL, &callbackEvent);

      // Set callback function
      callbackEvent.setCallback(CL_COMPLETE, &checkData, (void*)c);
	

      //print names in alphabetical order
      for(int i=0; i<allKernels.size(); i++) {
         kernelName = allKernels[i].getInfo<CL_KERNEL_FUNCTION_NAME>();
         std::cout << "Kernel: " << kernelName << std::endl;
      }
   }
   catch(cl::Error e) {
      std::cout << e.what() << ": Error code " << e.err() << std::endl;   
   }

   return 0;
}

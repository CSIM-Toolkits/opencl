#define __CL_ENABLE_EXCEPTIONS

#include <iostream>
#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <string.h>




int main(void) {

   std::vector<cl::Platform> platforms;
   std::vector<cl::Device> platformDevices, ctxDevices;

   std::string device_name,vendor_name,version_device;
   cl_uint i,u;

   try {

      // Access all devices in first platform
      cl::Platform::get(&platforms);
         std::cout << "Quantidade de plataformas: " << platforms.size()<<    std::endl;

      platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &platformDevices);
      
      // Create context and access device names
      cl::Context context(platformDevices);

      ctxDevices = context.getInfo<CL_CONTEXT_DEVICES>();
         std::cout << "Quantidade de dispositivos: " << ctxDevices.size()<<    std::endl;

      for(i=0; i<ctxDevices.size(); i++) {
         device_name = ctxDevices[i].getInfo<CL_DEVICE_NAME>();
         vendor_name = ctxDevices[i].getInfo<CL_DEVICE_VENDOR>();
         version_device = ctxDevices[i].getInfo<CL_DEVICE_VERSION >();


            std::cout << "Nome fabricante: " << vendor_name.c_str() <<    std::endl;
            std::cout << "Nome dispositivo: " << device_name.c_str() <<    std::endl;
            std::cout << "Versão: " << version_device.c_str() <<    std::endl;
            std::cout << "--------------------------" <<   std::endl;
      }


   }
   catch(cl::Error e) {
         std::cout << e.what() << ": Error code " << e.err() <<    std::endl;
   }



   return 0;
}

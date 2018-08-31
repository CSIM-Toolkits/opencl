#define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#define PROGRAM_FILE "simple_image.cl"
#define KERNEL_FUNC "simple_image"
#define INPUT_FILE "blank.png"
#define OUTPUT_FILE "output.png"


#include <GL/glu.h>
#define PNG_DEBUG 3
#include <png.h>

#include <fstream>
#include <iostream>
#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <string.h>

#include "CLUtil.hpp"

#define SAMPLE_VERSION "AMD-APP-SDK-v2.9-1.599.1"

using namespace std;
using namespace appsdk;



void read_image_data(const char* filename, png_bytep* data, size_t* w, size_t* h) {

   int i;

   /* Open input file */
   FILE *png_input;
   if((png_input = fopen(filename, "rb")) == NULL) {
      perror("Can't read input image file");
      exit(1);
   }

   png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   png_infop info_ptr = png_create_info_struct(png_ptr);
   png_init_io(png_ptr, png_input);
   png_read_info(png_ptr, info_ptr);
   *w = png_get_image_width(png_ptr, info_ptr);
   *h = png_get_image_height(png_ptr, info_ptr);

    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

   *data = new png_byte[rowbytes * *h];

   for(i=0; i<*h; i++) {
      png_read_row(png_ptr, *data + i * png_get_rowbytes(png_ptr, info_ptr), NULL);
   }

   /* Close input file */
   png_read_end(png_ptr, info_ptr);
   png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
   fclose(png_input);



}

void write_image_data(const char* filename, png_bytep data, size_t w, size_t h) {

   int i;

   /* Open output file */
   FILE *png_output;
   if((png_output = fopen(filename, "wb")) == NULL) {
      perror("Create output image file");
      exit(1);
   }

   /* Write image data */
   png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   png_infop info_ptr = png_create_info_struct(png_ptr);
   png_init_io(png_ptr, png_output);
   png_set_IHDR(png_ptr, info_ptr, w, h, 16,
         PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
         PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
   png_write_info(png_ptr, info_ptr);
   for(i=0; i<h; i++) {
      png_write_row(png_ptr, data + i*png_get_rowbytes(png_ptr, info_ptr));
   }

   /* Close file */
   png_write_end(png_ptr, NULL);
   png_destroy_write_struct(&png_ptr, &info_ptr);
   fclose(png_output);
}

int main(void) {

   vector<cl::Platform> platforms;
   vector<cl::Device> devices;
   vector<cl::Kernel> allKernels;
   string kernelName;
   char msg[16], msg_buffer[16],result[17];
   cl_int err=0,imageSupport,status,eventStatus;

   /* Image data */
   png_bytep pixels;
   cl_image_format png_format;


   cl::size_t<3> origin;
   cl::size_t<3> region;

   size_t width, height;


   try {

	/* Open input file and read image data */
	read_image_data(INPUT_FILE, &pixels, &width, &height);

	// Access all devices in first platform
	err = cl::Platform::get(&platforms);

	CHECK_OPENCL_ERROR(err, "Platform::get() failed.");

	err = platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);

        CHECK_OPENCL_ERROR(err, "Platform::getDevices() failed.");

	// Create context and access device names
	cl::Context context(devices, NULL,NULL,NULL,&err);

        CHECK_OPENCL_ERROR(err, "Context::Context() failed.");

	// Check for image support
	imageSupport = devices[0].getInfo<CL_DEVICE_IMAGE_SUPPORT>(&err);

	CHECK_OPENCL_ERROR(err, "Device::getInfo() failed.");

	if(!imageSupport)
	{

        	OPENCL_EXPECTED_ERROR("Images are not supported on this device!");

	}   

	// Create kernel
	ifstream programFile(PROGRAM_FILE);
	string programString(std::istreambuf_iterator<char>(programFile),(istreambuf_iterator<char>()));
	cl::Program::Sources source(1, make_pair(programString.c_str(),programString.length()+1));
	cl::Program program(context, source);
	program.build(devices);

	err= program.createKernels(&allKernels);
	//cl::Kernel kernel(program, KERNEL_FUNC);

	if(err != CL_SUCCESS)
	{
		if(err == CL_BUILD_PROGRAM_FAILURE)
		{
		    std::string str = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]);

		    std::cout << " \n\t\t\tBUILD LOG\n";
		    std::cout << " ************************************************\n";
		    std::cout << str << std::endl;
		    std::cout << " ************************************************\n";
		}
	}
	CHECK_OPENCL_ERROR(err, "Program::build() failed.");


	/* Create image object */
	cl::Image2D inputImage2D(context,CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,cl::ImageFormat(CL_LUMINANCE, CL_UNORM_INT16),width,height,0,(void*)pixels,&err);
	CHECK_OPENCL_ERROR(err, "Image2D::Image2D() failed. (inputImage2D)");

	cl::Image2D outputImage2D(context,CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,cl::ImageFormat(CL_LUMINANCE, CL_UNORM_INT16),width,height,0,(void*)pixels,&err);
	CHECK_OPENCL_ERROR(err, "Image2D::Image2D() failed. (inputImage2D)");

	/* Create kernel arguments */
	err = allKernels[0].setArg(0, inputImage2D);
	CHECK_OPENCL_ERROR(err, "Kernel::setArg() failed. (inputImageBuffer)");
	err = allKernels[0].setArg(1, outputImage2D);
	CHECK_OPENCL_ERROR(err, "Kernel::setArg() failed. (inputImageBuffer)");

	// Create queue and enqueue kernel-execution command
	cl::CommandQueue queue(context, devices[0],0,&err);

	CHECK_OPENCL_ERROR(err, "CommandQueue::CommandQueue() failed.");

	cl::NDRange offset(0,0);
	cl::NDRange global_size(width,height);
	cl::NDRange local_size(256,1);

        cl::Event ndrEvt;
	queue.enqueueNDRangeKernel(allKernels[0],cl::NullRange,global_size,local_size,0,&ndrEvt);

	CHECK_OPENCL_ERROR(err, "CommandQueue::enqueueNDRangeKernel() failed.");

	err = queue.flush();
	CHECK_OPENCL_ERROR(err, "cl::CommandQueue.flush failed.");

	eventStatus = CL_QUEUED;
	while(eventStatus != CL_COMPLETE)
	{
		status = ndrEvt.getInfo<cl_int>(
			     CL_EVENT_COMMAND_EXECUTION_STATUS,
			     &eventStatus);
		CHECK_OPENCL_ERROR(status,
				   "cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
	}

	origin[0] = 0;
	origin[1] = 0;
	origin[2] = 0;

	region[0] = width;
	region[1] = height;
	region[2] = 1;


	// Enqueue readBuffer
	cl::Event readEvt;
	err = queue.enqueueReadImage(outputImage2D,CL_FALSE,origin,region,0,0,(void*)pixels,NULL,&readEvt);
	CHECK_OPENCL_ERROR(err, "CommandQueue::enqueueReadImage failed.");

	err = queue.flush();
	CHECK_OPENCL_ERROR(err, "cl::CommandQueue.flush failed.");

	eventStatus = CL_QUEUED;
	while(eventStatus != CL_COMPLETE)
	{

        status = readEvt.getInfo<cl_int>(
                     CL_EVENT_COMMAND_EXECUTION_STATUS,
                     &eventStatus);
        CHECK_OPENCL_ERROR(status,
                           "cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");

	}

	/* Create output PNG file and write data */
	write_image_data(OUTPUT_FILE, pixels, width, height);
   }
   catch(cl::Error e) {
      cout << e.what() << ": Error code " << e.err() << endl;
   }

   free(pixels);
   //clReleaseMemObject(inputImage2D);
   //clReleaseMemObject(outputImage2D);


   return 0;
}



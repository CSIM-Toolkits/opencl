
#include <SDKBitMap.hpp>

using namespace appsdk;

class Image2DCL:BaseCL
{
  


    public :

	std::string inputImage;
	//std::string outputImage;
	std::string typeImage;


	//int: –2147483648 to 2147483647 
	//uint: 0 to 4294967295 
        cl_uint width;                      /**< Width of image */
        cl_uint height;                     /**< Height of image */

	cl_uchar4* inputImageData;          /**< Input bitmap data to device */
        cl_uchar4* outputImageData;         /**< Output from device */

        cl::Image2D inputImage2D;                       /**< CL Input image2d */
        cl::Image2D outputImage2D;                      /**< CL Output image2d */

        uchar4* pixelData;       /**< Pointer to image data */

        cl_uint pixelSize;                  /**< Size of a pixel in BMP format> */

        cl_uchar* verificationOutput;       /**< Output array for reference implementation */

        cl_int err;

	SDKBitMap inputBitmap;   /**< Bitmap class object */


       
        Image2DCL(std::string inputImage):BaseCL((char*)"Image2DCL")
        {
		this->inputImage=inputImage;
		//this->outputImage=outputImage;

		 pixelSize = sizeof(uchar4);
        }

        /**
         * Destructor
         */
        ~Image2DCL()
        {

        }

	std::string getPathInputImage();
	int readInputImage();
	void setTypeImage(std::string inputImage);
	int createBuffers(cl::Context context);
	int copyHostToBuffer(CommandQueueCL* commandQueue);
	int readyBufferToHost(CommandQueueCL* commandQueue);
	int writeOutputImage(std::string outputImageName);


};


std::string Image2DCL::getPathInputImage(){

	setTypeImage(inputImage);
	std::string filePath = getPath() + inputImage;
	//cout<<filePath<<endl;
	return filePath;
};


int Image2DCL::readInputImage()
{

	std::string filePath = getPathInputImage();

	//BITMAP TYPE
	if(this->typeImage.compare("bmp")==0){

		
		// load input bitmap image
		inputBitmap.load(filePath.c_str());

		// error if image did not load
		if(!inputBitmap.isLoaded())
		{
			std::cout << "Failed to load input image!" << std::endl;
			return SDK_FAILURE;
		}

		// get width and height of input image
		height = inputBitmap.getHeight();
		width = inputBitmap.getWidth();

		// allocate memory for input & output image data  */
		inputImageData  = (cl_uchar4*)malloc(width * height * sizeof(cl_uchar4));

		// error check
		CHECK_ALLOCATION(inputImageData, "Failed to allocate memory! (inputImageData)");


		// allocate memory for output image data
		outputImageData = (cl_uchar4*)malloc(width * height * sizeof(cl_uchar4));

		// error check
		CHECK_ALLOCATION(outputImageData,"Failed to allocate memory! (outputImageData)");


		// initialize the Image data to NULL
		memset(outputImageData, 0, width * height * pixelSize);

		// get the pointer to pixel data
		pixelData = inputBitmap.getPixels();

		// error check
		CHECK_ALLOCATION(pixelData, "Failed to read pixel Data!");

		// Copy pixel data into inputImageData
		memcpy(inputImageData, pixelData, width * height * pixelSize);

		// allocate memory for verification output
		verificationOutput = (cl_uchar*)malloc(width * height * pixelSize);

		// error check
		CHECK_ALLOCATION(verificationOutput,
			     "verificationOutput heap allocation failed!");

		// initialize the data to NULL
		memset(verificationOutput, 0, width * height * pixelSize);


	//JPEG TYPE			
	}else if(this->typeImage.compare("jpg")==0 || this->typeImage.compare("jpeg")==0){

	}
	


    

    return SDK_SUCCESS;

}

int Image2DCL::writeOutputImage(std::string outputImageName)
{

	inputBitmap;   /**< Bitmap class object */

	// copy output image data back to original pixel data
	memcpy(pixelData, outputImageData, width * height * pixelSize);

	// write the output bmp file
	if(!inputBitmap.write(outputImageName.c_str()))
	{
		std::cout << "Failed to write output image!" << std::endl;
		return SDK_FAILURE;
	}

	return SDK_SUCCESS;
}



void Image2DCL::setTypeImage(std::string inputImage){
	char delimiter = '.';
	vector<string> parts = split(inputImage,delimiter);
	//cout<<"Size: "<<parts.size()<<endl;
	//cout<<"Format: "<<parts[1]<<endl;
	this->typeImage = parts[1];
};


int Image2DCL::createBuffers(cl::Context context){

	/*
	* Create and initialize memory objects
	*/
	inputImage2D = cl::Image2D(context,
		               CL_MEM_READ_ONLY,
		               cl::ImageFormat(CL_RGBA, CL_UNSIGNED_INT8),
		               width,
		               height,
		               0,
		               NULL,
		               &err);

	if(CheckError(err,"Image2D::Image2D() failed. (inputImage2D).",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}


	// Create memory objects for output Image
	outputImage2D = cl::Image2D(context,
		                CL_MEM_WRITE_ONLY,
		                cl::ImageFormat(CL_RGBA, CL_UNSIGNED_INT8),
		                width,
		                height,
		                0,
		                0,
		                &err);

	if(CheckError(err,"Image2D::Image2D() failed. (outputImage2D).",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	return SDK_SUCCESS;

};


int Image2DCL::copyHostToBuffer(CommandQueueCL* commandQueue){


	cl_int status;

	cl::size_t<3> origin;
	origin[0] = 0;
	origin[1] = 0;
	origin[2] = 0;

	cl::size_t<3> region;
	region[0] = width;
	region[1] = height;
	region[2] = 1;

	cl::Event writeEvt;
	status = commandQueue->commandQueue.enqueueWriteImage(inputImage2D,CL_TRUE,origin,region,0,0,inputImageData,NULL,&writeEvt);
	//CHECK_OPENCL_ERROR(status,"CommandQueue::enqueueWriteImage failed. (inputImage2D)");
	if(CheckError(status,"CommandQueue::enqueueWriteImage failed. (inputImage2D)",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}



	status = commandQueue->commandQueue.flush();
	//CHECK_OPENCL_ERROR(status, "cl::CommandQueue.flush failed.");
	if(CheckError(status,"cl::CommandQueue.flush failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}


	cl_int eventStatus = CL_QUEUED;
	while(eventStatus != CL_COMPLETE)
	{
		status = writeEvt.getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS,&eventStatus);
		//CHECK_OPENCL_ERROR(status,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
		if(CheckError(status,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
			return SDK_FAILURE;
		}

	}




	return SDK_SUCCESS;
}



int Image2DCL::readyBufferToHost(CommandQueueCL* commandQueue){

	cl_int status;

	cl::size_t<3> origin;
	origin[0] = 0;
	origin[1] = 0;
	origin[2] = 0;

	cl::size_t<3> region;
	region[0] = width;
	region[1] = height;
	region[2] = 1;

	// Enqueue readBuffer
	cl::Event readEvt;
	status = commandQueue->commandQueue.enqueueReadImage(outputImage2D,CL_FALSE,origin,region,0,0,outputImageData,NULL,&readEvt);
	//CHECK_OPENCL_ERROR(status, "CommandQueue::enqueueReadImage failed.");
	if(CheckError(status,"CommandQueue::enqueueReadImage failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	status = commandQueue->commandQueue.flush();
	//CHECK_OPENCL_ERROR(status, "cl::CommandQueue.flush failed.");
	if(CheckError(status,"cl::CommandQueue.flush failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	cl_int eventStatus = CL_QUEUED;
	while(eventStatus != CL_COMPLETE)
	{
		status = readEvt.getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS,&eventStatus);
		//CHECK_OPENCL_ERROR(status,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
		if(CheckError(status,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
			return SDK_FAILURE;
		}

	}

    return SDK_SUCCESS;
}



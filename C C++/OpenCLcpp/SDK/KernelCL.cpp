


class KernelCL:BaseCL
{
  
	public:


	std::vector<string> allKernels;  // kernels availables in folder kernels

        cl::Program currentProgram;                            /**< CL program  */
        cl::Kernel currentKernel;                       /**< CL kernel */

        cl_int err;

        size_t kernelWorkGroupSize;         /**< Group Size returned by kernel */
        size_t blockSizeX;                  /**< Work-group size in x-direction */
	size_t blockSizeY;                  /**< Work-group size in y-direction */


	KernelCL():BaseCL((char*)"KernelCL"){
		err= CL_SUCCESS;
		blockSizeX = GROUP_SIZE;
		blockSizeY = 1;

	
	}


	~KernelCL(){
	}


	std::string getPathKernels();
	void printAllKernelsAvailables();
	int CreateAndBuildProgram(cl::Context context,CommandArgsCL *sampleArgs,DeviceCL *device);
	int run(CommandArgsCL *sampleArgs,CommandQueueCL* commandQueue,Image2DCL *image2d);
	int runCLKernels(CommandQueueCL* commandQueue,Image2DCL *image2d);
	int setArgs(Image2DCL *image2d);
	int enqueueKernel(CommandQueueCL* commandQueue,Image2DCL *image2d);
	


};


std::string KernelCL::getPathKernels(){

	std::string filePath = getPath() + "kernels";
	//cout<<filePath<<endl;
	return filePath;
};

void KernelCL::printAllKernelsAvailables(){


	std::vector<string> kernels; 

	//cout<<"Kernels: "<<getPathKernels().c_str()<<endl;
	kernels = listdir(getPathKernels().c_str());
	printArrayString("Kernels Availables: ", kernels, kernels.size());

}

int KernelCL::CreateAndBuildProgram(cl::Context context,CommandArgsCL *sampleArgs,DeviceCL *device){


	allKernels = listdir(getPathKernels().c_str());
	// create a CL program using the kernel source
	SDKFile kernelFile;
	std::string kernelPath = getPathKernels();


	kernelPath.append("/"+allKernels[sampleArgs->kernelId]);
	//kernelPath.append("/"+allKernels[0]);
	cout<<kernelPath<<endl;


        if(!kernelFile.open(kernelPath.c_str()))
        {
            std::cout << "Failed to load kernel file : " << kernelPath << std::endl;
            return SDK_FAILURE;
        }

        // create program source
        cl::Program::Sources programSource(1,std::make_pair(kernelFile.source().data(),kernelFile.source().size()));

        // Create program object
        currentProgram = cl::Program(context, programSource, &err);
	if(CheckError(err,"Program::Program() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	std::string flagsStr = std::string("");

	// Get additional options
	if(sampleArgs->isComplierFlagsSpecified())
	{
		SDKFile flagsFile;
		std::string flagsPath = getPath();
		flagsPath.append(sampleArgs->flags.c_str());
		if(!flagsFile.open(flagsPath.c_str()))
		{
			std::cout << "Failed to load flags file: " << flagsPath << std::endl;
			return SDK_FAILURE;
		}
		flagsFile.replaceNewlineWithSpaces();
		const char * flags = flagsFile.source().c_str();
		flagsStr.append(flags);
	}

	if(flagsStr.size() != 0)
	{
		std::cout << "Build Options are : " << flagsStr.c_str() << std::endl;
	}

	

	err = currentProgram.build(device->devices, flagsStr.c_str());

	if(err != CL_SUCCESS)
	{
		if(err == CL_BUILD_PROGRAM_FAILURE)
		{
		    std::string str = currentProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device->devices[device->currentDeviceId]);

		    std::cout << " \n\t\t\tBUILD LOG\n";
		    std::cout << " ************************************************\n";
		    std::cout << str << std::endl;
		    std::cout << " ************************************************\n";
		}
	}

	if(CheckError(err,"Program::Program() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	// Create kernel	
	currentKernel = cl::Kernel(currentProgram, removeExt(allKernels[sampleArgs->kernelId]).c_str(),  &err);

	if(CheckError(err,"Kernel::Kernel() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}


	// Check group size against group size returned by kernel
	kernelWorkGroupSize = currentKernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>
		          (device->devices[sampleArgs->deviceId], &err);
	

	if(CheckError(err,"Kernel::getWorkGroupInfo()  failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	if((blockSizeX * blockSizeY) > kernelWorkGroupSize)
	{
		if(!sampleArgs->quiet)
		{
		    std::cout << "Out of Resources!" << std::endl;
		    std::cout << "Group Size specified : "
			      << blockSizeX * blockSizeY << std::endl;
		    std::cout << "Max Group Size supported on the kernel : "
			      << kernelWorkGroupSize << std::endl;
		    std::cout << "Falling back to " << kernelWorkGroupSize << std::endl;
		}

		if(blockSizeX > kernelWorkGroupSize)
		{
		    blockSizeX = kernelWorkGroupSize;
		    blockSizeY = 1;
		}
	}


	return SDK_SUCCESS;
}

int KernelCL::run(CommandArgsCL *sampleArgs,CommandQueueCL* commandQueue,Image2DCL *image2d)
{
	std::cout << "Executing kernel for " << sampleArgs->iterations_value <<" iterations" <<std::endl;
	std::cout << "-------------------------------------------" << std::endl;


	try
	{
		for(int i = 0; i < sampleArgs->iterations_value; i++)
		{
		    // Set kernel arguments and run kernel
		    if(runCLKernels(commandQueue,image2d) != SDK_SUCCESS)
		    {
			return SDK_FAILURE;
		    }
		}
	}
	catch (cl::Error e)
	{
		//std::cout << e.what() << std::endl;
		//std::cout << "Error code: " << e.err() << std::endl;
		CheckError(err,"Program::Program() failed.",GetFileAndLine(__FILE__,__LINE__));
		return SDK_FAILURE;
	}

	commandQueue->commandQueue.finish();

	return SDK_SUCCESS;

}

int KernelCL::runCLKernels(CommandQueueCL* commandQueue,Image2DCL *image2d){

	if(image2d->copyHostToBuffer(commandQueue)!=CL_SUCCESS){
		return SDK_FAILURE;	
	}
	

	if(setArgs(image2d)!=CL_SUCCESS){
		return SDK_FAILURE;	
	}
	
	if(enqueueKernel(commandQueue,image2d)!=CL_SUCCESS){
		return SDK_FAILURE;	
	}

	if(image2d->readyBufferToHost(commandQueue)!=CL_SUCCESS){
		return SDK_FAILURE;	
	}



	return SDK_SUCCESS;
}

int KernelCL::setArgs(Image2DCL *image2d){


	cl_int status;
	// Set appropriate arguments to the kernel
	// input buffer image
	status = currentKernel.setArg(0, image2d->inputImage2D);
	//CHECK_OPENCL_ERROR(status, "Kernel::setArg() failed. (inputImageBuffer)");

	if(CheckError(status,"Kernel::setArg() failed. (inputImageBuffer)",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	// outBuffer imager
	status = currentKernel.setArg(1, image2d->outputImage2D);
	//CHECK_OPENCL_ERROR(status, "Kernel::setArg() failed. (outputImageBuffer)");

	if(CheckError(status,"Kernel::setArg() failed. (outputImageBuffer)",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	return SDK_SUCCESS;

};

int KernelCL::enqueueKernel(CommandQueueCL* commandQueue,Image2DCL *image2d){

	/*
	* Enqueue a kernel run call.
	*/

	cl_int status;

	cl::NDRange offset(0,0);
	cl::NDRange globalThreads(image2d->width, image2d->height);
	cl::NDRange localThreads(blockSizeX, blockSizeY);

	cl::Event ndrEvt;
	status = commandQueue->commandQueue.enqueueNDRangeKernel(currentKernel,offset,globalThreads,localThreads,0,&ndrEvt);
	//CHECK_OPENCL_ERROR(status, "CommandQueue::enqueueNDRangeKernel() failed.");
	if(CheckError(status,"CommandQueue::enqueueNDRangeKernel() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
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
		status = ndrEvt.getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS,&eventStatus);
		//CHECK_OPENCL_ERROR(status,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
		if(CheckError(status,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
			return SDK_FAILURE;
		}
	
	}

};



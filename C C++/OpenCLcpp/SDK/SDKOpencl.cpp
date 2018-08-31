

#include <Configure.h>



//using namespace appsdk;


class SDKOpencl:BaseCL
{
  

	public:

        PlatformCL *platforms;        /**< PlatformCL class to manage platforms*/

        ContextCL *context;        /**< ContextCL class to manage contexts*/

        CommandArgsCL *sampleArgs;    /**< CommandArgsCL  to manage commands arguments  */

        TimerCL *sampleTimer;      /**< TimerCL object */

	DeviceCL *device;

	Image2DCL *image2d;

	KernelCL *kernel;

        CommandQueueCL* commandQueue; 



        cl_double setupTime;                /**< time taken to setup OpenCL resources and building kernel */
        cl_double kernelTime;               /**< time taken to run kernel and read result back */
	



	SDKOpencl():BaseCL((char*)"SDKOpencl"){


		sampleArgs = new CommandArgsCL();
		sampleTimer = new TimerCL();
		platforms = new PlatformCL();
		context = new ContextCL();
		device = new DeviceCL(sampleArgs->deviceId);
		commandQueue = new CommandQueueCL();
		kernel = new KernelCL();
		sampleArgs->sampleVerStr = SAMPLE_VERSION;

	}


	~SDKOpencl(){
	}

	int addOption(string sVersion, string lVersion, string description, CmdArgsEnum enumType, void* value);
	int initialize();

	int setupCL(std::string inputImageName);

	void printStats();

	int finalize();






};

int SDKOpencl::initialize(){

	
	if(CheckError(sampleArgs->initialize(),"OpenCL resource initialization failed",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	
	return SDK_SUCCESS;
};

int SDKOpencl::setupCL(std::string inputImageName){


	// create and initialize timers
	int timer = sampleTimer->createTimer();
	sampleTimer->resetTimer(timer);
	sampleTimer->startTimer(timer);


	if(platforms->GetPlatform(sampleArgs)!=SDK_SUCCESS){

		return SDK_FAILURE;
	}

	if(context->createContext(platforms->currentPlatform,platforms->dType,device)!=SDK_SUCCESS){

		return SDK_FAILURE;
	}

	#ifdef IMAGE_FORMAT_2D
		image2d = new Image2DCL(inputImageName);

		if(image2d->readInputImage() != SDK_SUCCESS)
		{
			return SDK_FAILURE;
		}


	#endif


	if(commandQueue->CreateCommandQueue(context->currentContext,device->devices,sampleArgs->deviceId)!= SDK_SUCCESS){
		return SDK_FAILURE;
	}


	if(image2d->createBuffers(context->currentContext)!= SDK_SUCCESS){
		return SDK_FAILURE;
	}


	if(kernel->CreateAndBuildProgram(context->currentContext,sampleArgs,device)!= SDK_SUCCESS){
		return SDK_FAILURE;
	}

	sampleTimer->stopTimer(timer);
	// Compute setup time
	setupTime = (double)(sampleTimer->readTimer(timer));



	//RUN
	// create and initialize timers
	timer = sampleTimer->createTimer();
	sampleTimer->resetTimer(timer);
	sampleTimer->startTimer(timer);


	if(kernel->run(sampleArgs,commandQueue,image2d)!= SDK_SUCCESS){
		return SDK_FAILURE;
	}



	std::string OutputImageName = removeExt(kernel->allKernels[sampleArgs->kernelId])+"FilterImage_Output.bmp";
	// write the output image to bitmap file
	if(image2d->writeOutputImage(OutputImageName) != SDK_SUCCESS)
	{
		return SDK_FAILURE;
	}



	sampleTimer->stopTimer(timer);
	// Compute kernel time
	kernelTime = (double)(sampleTimer->readTimer(timer))/ sampleArgs->iterations_value;

	printStats();

	return SDK_SUCCESS;
};

int SDKOpencl::addOption(string sVersion, string lVersion, string description,  CmdArgsEnum enumType, void* value){


	Option* iteration_option = new Option;
	if(!iteration_option)
	{
		error("Memory Allocation error.\n");
		return SDK_FAILURE;
	}
	iteration_option->_sVersion = sVersion;
	iteration_option->_lVersion = lVersion;
	iteration_option->_description = description;
	//iteration_option->_type = CA_ARG_INT;

	switch(enumType){
		case CA_ARG_INT: iteration_option->_type=CA_ARG_INT; break;
		case CA_ARG_FLOAT: iteration_option->_type=CA_ARG_FLOAT; break;
		case CA_ARG_DOUBLE: iteration_option->_type=CA_ARG_DOUBLE; break;
		case CA_ARG_STRING: iteration_option->_type=CA_ARG_STRING; break;
		case CA_NO_ARGUMENT: iteration_option->_type=CA_NO_ARGUMENT; break;
	}

	//iteration_option->_type = enumType;
	iteration_option->_value = value;

        //printPointerVoid(value,"int");

	sampleArgs->AddOption(iteration_option);
	delete iteration_option;
	return SDK_SUCCESS;
};



void SDKOpencl::printStats()
{

	if(sampleArgs->timing)
	{
		std::string strArray[4] =
		{
		    "Width",
		    "Height",
		    "Time(sec)",
		    "[Transfer+Kernel]Time(sec)"
		};
		std::string stats[4];

		sampleTimer->totalTime = setupTime + kernelTime;

		stats[0] = toString(image2d->width, std::dec);
		stats[1] = toString(image2d->height, std::dec);
		stats[2] = toString(sampleTimer->totalTime, std::dec);
		stats[3] = toString(kernelTime, std::dec);

		printStatistics(strArray, stats, 4);
	}
}


int SDKOpencl::finalize(){



	FREE(platforms);
	FREE(context);
	FREE(sampleArgs);
	FREE(sampleTimer);
	FREE(device);
	FREE(image2d);
	FREE(kernel);
	FREE(commandQueue);
	LogCL::getInstance()->WriteLogFile((char*)"Fim");

};





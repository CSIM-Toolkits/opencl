
class ErrorCL
{
  
	private:

	static ErrorCL* instance;

	static bool FirstInstanceFlag;  

	ErrorCL(){


	};



	public:




	~ErrorCL(){

		FirstInstanceFlag = false;
		delete instance;
	};

	static ErrorCL* getInstance();

	static int CHECK_OPENCL_ERROR(int actual, std::string message,std::string location,int success = CL_SUCCESS);

	static int CHECK_OPENCL_ERROR(int actual, std::string message,int success = CL_SUCCESS);

	template<typename T>
	static const char* getOpenCLErrorCodeStr(T input);

	template<typename T>
	static int checkVal(T input,T reference,std::string message, bool isAPIerror = true);




};


	bool ErrorCL::FirstInstanceFlag = false;
	ErrorCL* ErrorCL::instance = NULL;


	 ErrorCL* ErrorCL::getInstance(){

		if(!FirstInstanceFlag){
			instance= new ErrorCL();
			FirstInstanceFlag=true;
		}
		return instance;

	};


	int ErrorCL::CHECK_OPENCL_ERROR(int actual, std::string message,std::string location,int success){

		if(checkVal(actual, success, message)) 
		{ 
			std::cout << location<<endl;
			//std::cout << "Location : " << __FILE__ << ":" << __LINE__<< std::endl; 
			return SDK_FAILURE; 
		}
		return SDK_SUCCESS;

	};

	int ErrorCL::CHECK_OPENCL_ERROR(int actual, std::string message,int success){

		if(checkVal(actual, success, message)) 
		{ 

			//std::cout << "Location : " << __FILE__ << ":" << __LINE__<< std::endl; 
			return SDK_FAILURE; 
		}
		
		return SDK_SUCCESS;

	};



	template<typename T>
	const char* ErrorCL::getOpenCLErrorCodeStr(T input)
	{
		int errorCode = (int)input;
		switch(errorCode)
		{
		case CL_DEVICE_NOT_FOUND:
		return "CL_DEVICE_NOT_FOUND";
		case CL_DEVICE_NOT_AVAILABLE:
		return "CL_DEVICE_NOT_AVAILABLE";
		case CL_COMPILER_NOT_AVAILABLE:
		return "CL_COMPILER_NOT_AVAILABLE";
		case CL_MEM_OBJECT_ALLOCATION_FAILURE:
		return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		case CL_OUT_OF_RESOURCES:
		return "CL_OUT_OF_RESOURCES";
		case CL_OUT_OF_HOST_MEMORY:
		return "CL_OUT_OF_HOST_MEMORY";
		case CL_PROFILING_INFO_NOT_AVAILABLE:
		return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case CL_MEM_COPY_OVERLAP:
		return "CL_MEM_COPY_OVERLAP";
		case CL_IMAGE_FORMAT_MISMATCH:
		return "CL_IMAGE_FORMAT_MISMATCH";
		case CL_IMAGE_FORMAT_NOT_SUPPORTED:
		return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		case CL_BUILD_PROGRAM_FAILURE:
		return "CL_BUILD_PROGRAM_FAILURE";
		case CL_MAP_FAILURE:
		return "CL_MAP_FAILURE";
		case CL_MISALIGNED_SUB_BUFFER_OFFSET:
		return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
		case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
		return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
		case CL_INVALID_VALUE:
		return "CL_INVALID_VALUE";
		case CL_INVALID_DEVICE_TYPE:
		return "CL_INVALID_DEVICE_TYPE";
		case CL_INVALID_PLATFORM:
		return "CL_INVALID_PLATFORM";
		case CL_INVALID_DEVICE:
		return "CL_INVALID_DEVICE";
		case CL_INVALID_CONTEXT:
		return "CL_INVALID_CONTEXT";
		case CL_INVALID_QUEUE_PROPERTIES:
		return "CL_INVALID_QUEUE_PROPERTIES";
		case CL_INVALID_COMMAND_QUEUE:
		return "CL_INVALID_COMMAND_QUEUE";
		case CL_INVALID_HOST_PTR:
		return "CL_INVALID_HOST_PTR";
		case CL_INVALID_MEM_OBJECT:
		return "CL_INVALID_MEM_OBJECT";
		case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
		return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		case CL_INVALID_IMAGE_SIZE:
		return "CL_INVALID_IMAGE_SIZE";
		case CL_INVALID_SAMPLER:
		return "CL_INVALID_SAMPLER";
		case CL_INVALID_BINARY:
		return "CL_INVALID_BINARY";
		case CL_INVALID_BUILD_OPTIONS:
		return "CL_INVALID_BUILD_OPTIONS";
		case CL_INVALID_PROGRAM:
		return "CL_INVALID_PROGRAM";
		case CL_INVALID_PROGRAM_EXECUTABLE:
		return "CL_INVALID_PROGRAM_EXECUTABLE";
		case CL_INVALID_KERNEL_NAME:
		return "CL_INVALID_KERNEL_NAME";
		case CL_INVALID_KERNEL_DEFINITION:
		return "CL_INVALID_KERNEL_DEFINITION";
		case CL_INVALID_KERNEL:
		return "CL_INVALID_KERNEL";
		case CL_INVALID_ARG_INDEX:
		return "CL_INVALID_ARG_INDEX";
		case CL_INVALID_ARG_VALUE:
		return "CL_INVALID_ARG_VALUE";
		case CL_INVALID_ARG_SIZE:
		return "CL_INVALID_ARG_SIZE";
		case CL_INVALID_KERNEL_ARGS:
		return "CL_INVALID_KERNEL_ARGS";
		case CL_INVALID_WORK_DIMENSION:
		return "CL_INVALID_WORK_DIMENSION";
		case CL_INVALID_WORK_GROUP_SIZE:
		return "CL_INVALID_WORK_GROUP_SIZE";
		case CL_INVALID_WORK_ITEM_SIZE:
		return "CL_INVALID_WORK_ITEM_SIZE";
		case CL_INVALID_GLOBAL_OFFSET:
		return "CL_INVALID_GLOBAL_OFFSET";
		case CL_INVALID_EVENT_WAIT_LIST:
		return "CL_INVALID_EVENT_WAIT_LIST";
		case CL_INVALID_EVENT:
		return "CL_INVALID_EVENT";
		case CL_INVALID_OPERATION:
		return "CL_INVALID_OPERATION";
		case CL_INVALID_GL_OBJECT:
		return "CL_INVALID_GL_OBJECT";
		case CL_INVALID_BUFFER_SIZE:
		return "CL_INVALID_BUFFER_SIZE";
		case CL_INVALID_MIP_LEVEL:
		return "CL_INVALID_MIP_LEVEL";
		case CL_INVALID_GLOBAL_WORK_SIZE:
		return "CL_INVALID_GLOBAL_WORK_SIZE";
		case CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR:
		return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
		case CL_PLATFORM_NOT_FOUND_KHR:
		return "CL_PLATFORM_NOT_FOUND_KHR";
		//case CL_INVALID_PROPERTY_EXT:
		//    return "CL_INVALID_PROPERTY_EXT";
		case CL_DEVICE_PARTITION_FAILED_EXT:
		return "CL_DEVICE_PARTITION_FAILED_EXT";
		case CL_INVALID_PARTITION_COUNT_EXT:
		return "CL_INVALID_PARTITION_COUNT_EXT";
		default:
		return "unknown opencl error code";
		}
	};




/**
* checkVal
* Set default(isAPIerror) parameter to false
* if checkVaul is used to check otherthan OpenCL API error code
*/
	template<typename T>
	int ErrorCL::checkVal(T input,T reference,std::string message, bool isAPIerror)
	{

	    if(input==reference)
	    {
		return SDK_SUCCESS;
	    }
	    else
	    {
		if(isAPIerror)
		{
		    std::cout<<"Error: "<< message << " Error code : ";
		    std::cout << getOpenCLErrorCodeStr(input) << std::endl;
		}
		else
		{
		    error(message);
		}
		return SDK_FAILURE;
	    }


	};

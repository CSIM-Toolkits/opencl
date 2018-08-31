
class ContextCL:BaseCL
{
  

	cl_context_properties cps[3];
        cl_int err;

	//DeviceCL *device;

	public:

        cl::Context currentContext;                            /**< current context */

	ContextCL():BaseCL((char*)"ContextCL"){
		err= CL_SUCCESS;		

	}


	~ContextCL(){
	}


	int createContext(std::vector<cl::Platform>::iterator i,cl_device_type dType,DeviceCL *device);



};


int ContextCL::createContext(std::vector<cl::Platform>::iterator i, cl_device_type dType,DeviceCL *device){



	cps[0] = CL_CONTEXT_PLATFORM;
        cps[1] = (cl_context_properties)(*i)();
        cps[2] = 0;

	currentContext = cl::Context(dType, cps, NULL, NULL, &err);

	if(CheckError(err,"Context::Context() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}


	device->devices = currentContext.getInfo<CL_CONTEXT_DEVICES>(&err);
	
	if(CheckError(err,"Context::getInfo() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}


	std::vector<cl::Device>::iterator d;


	int deviceCount = (int)device->devices.size();
	int j = 0;
	for (d = device->devices.begin(); d != device->devices.end();
	    ++d, ++j)
	{
		std::cout << "Device " << j << " : ";
		std::string deviceName = (*d).getInfo<CL_DEVICE_NAME>();
		std::cout << deviceName.c_str() << "\n";
	}
	std::cout << "\n";


	if(device->validateDeviceId(device->currentDeviceId,deviceCount)!=CL_SUCCESS){
		return SDK_FAILURE;
	}
    
	return SDK_SUCCESS;
};




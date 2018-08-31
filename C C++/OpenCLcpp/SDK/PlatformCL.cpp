
class PlatformCL:BaseCL
{
  

        std::vector<cl::Platform> platforms;            /**< list of platforms availables*/





	public:

	std::vector<cl::Platform>::iterator currentPlatform; /**< chosen platform */

        cl_device_type dType; /**< type of chosen platform */

	PlatformCL():BaseCL((char*)"PlatformCL"){



	}


	~PlatformCL(){
	}

	int GetPlatform(CommandArgsCL *sampleArgs);
	void PrintCurrentPlatformInfo();
	void PrintPlatformInfo(std::vector<cl::Platform>::iterator i);
	int displayDevices(cl_platform_id platform, cl_device_type deviceType);

};

int PlatformCL::GetPlatform(CommandArgsCL *sampleArgs){

	cl_int err = CL_SUCCESS;

	if(sampleArgs->deviceType.compare("cpu") == 0)
	{
		dType = CL_DEVICE_TYPE_CPU;
	}
	else //deviceType = "gpu"
	{
		dType = CL_DEVICE_TYPE_GPU;
		if(sampleArgs->isThereGPU() == false)
		{
	    		//std::cout << "GPU not found. Falling back to CPU device" << std::endl;
			notice("GPU not found. Falling back to CPU device");
	    		dType = CL_DEVICE_TYPE_CPU;
		}
	}

	/*
	* Have a look at the available platforms and pick either
	* the AMD one if available or a reasonable default.
	*/
	err = cl::Platform::get(&platforms);

	if(CheckError(err,"Platform::get() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	

	std::vector<cl::Platform>::iterator i;

	//If has more than 1 platform,
	if(platforms.size() > 0)
	{
		//Choice the platform, if the user has passed the platformid
		if(sampleArgs->isPlatformEnabled())
		{
		    i = platforms.begin() + sampleArgs->platformId;
		}
		else
		{
		    //choice de AMD
		    for(i = platforms.begin(); i != platforms.end(); ++i)
		    {
			if(!strcmp((*i).getInfo<CL_PLATFORM_VENDOR>().c_str(),
				   "Advanced Micro Devices, Inc."))
			{
			    break;
			}
		    }
		}
	}

	currentPlatform = i;
	PrintCurrentPlatformInfo();


	return SDK_SUCCESS;
}


void PlatformCL::PrintCurrentPlatformInfo(){

	std::cout << "Vendor :" << (*currentPlatform).getInfo<CL_PLATFORM_VENDOR>().c_str() << "\n";
	std::cout << "Version :" << (*currentPlatform).getInfo<CL_PLATFORM_VERSION >().c_str() << "\n";
	std::cout << "Name :" << (*currentPlatform).getInfo<CL_PLATFORM_NAME >().c_str() << "\n";
	std::cout << "Extensions :" << (*currentPlatform).getInfo<CL_PLATFORM_EXTENSIONS>().c_str() << "\n";

};

void PlatformCL::PrintPlatformInfo(std::vector<cl::Platform>::iterator i){

	std::cout << "Vendor :" << (*i).getInfo<CL_PLATFORM_VENDOR>().c_str() << "\n";
	std::cout << "Version :" << (*i).getInfo<CL_PLATFORM_VERSION >().c_str() << "\n";
	std::cout << "Name :" << (*i).getInfo<CL_PLATFORM_NAME >().c_str() << "\n";
	std::cout << "Extensions :" << (*i).getInfo<CL_PLATFORM_EXTENSIONS>().c_str() << "\n";

};

/**
 * display devices
 * displays the devices in a platform
 * @param platform cl_platform_id
 * @param deviceType deviceType
 * @return 0 if success else nonzero
 */
int PlatformCL::displayDevices(cl_platform_id platform, cl_device_type deviceType)
{
    cl_int status;
    // Get platform name
    char platformVendor[1024];
    status = clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, sizeof(platformVendor),
                               platformVendor, NULL);

    if(CheckError(status, "clGetPlatformInfo failed.")!=SDK_SUCCESS){
	return SDK_FAILURE;
    }
    //CHECK_OPENCL_ERROR(status, "clGetPlatformInfo failed");
    std::cout << "\nSelected Platform Vendor : " << platformVendor << std::endl;
    
    // Get number of devices available
    cl_uint deviceCount = 0;
    status = clGetDeviceIDs(platform, deviceType, 0, NULL, &deviceCount);
    if(CheckError(status, "clGetDeviceIDs failed.")!=SDK_SUCCESS){
	return SDK_FAILURE;
    }
    //CHECK_OPENCL_ERROR(status, "clGetDeviceIDs failed");
    cl_device_id* deviceIds = (cl_device_id*)malloc(sizeof(cl_device_id) *
                              deviceCount);
    CHECK_ALLOCATION(deviceIds, "Failed to allocate memory(deviceIds)");
    // Get device ids
    status = clGetDeviceIDs(platform, deviceType, deviceCount, deviceIds, NULL);
    if(CheckError(status, "clGetDeviceIDs failed.")!=SDK_SUCCESS){
	return SDK_FAILURE;
    }
    //CHECK_OPENCL_ERROR(status, "clGetDeviceIDs failed");
    // Print device index and device names
    for(cl_uint i = 0; i < deviceCount; ++i)
    {
        char deviceName[1024];
        status = clGetDeviceInfo(deviceIds[i], CL_DEVICE_NAME, sizeof(deviceName),
                                 deviceName, NULL);
	if(CheckError(status, "clGetDeviceIDs failed.")!=SDK_SUCCESS){
	return SDK_FAILURE;
	}

        //CHECK_OPENCL_ERROR(status, "clGetDeviceInfo failed");
        std::cout << "Device " << i << " : " << deviceName
                  <<" Device ID is "<<deviceIds[i]<< std::endl;
    }
    free(deviceIds);
    return SDK_SUCCESS;
}


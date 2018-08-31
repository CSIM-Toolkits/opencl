class DeviceCL:BaseCL
{
  
	public:

        std::vector<cl::Device> devices;                /**< CL device list availables */

	//std::vector<cl::Device>::iterator currentDevice; /**< chosen device */

	int currentDeviceId; /**< chosen device */

        cl_int err;


	DeviceCL(int deviceId):BaseCL((char*)"DeviceCL"){
		err= CL_SUCCESS;
		currentDeviceId = deviceId;

	}


	~DeviceCL(){
	}


	int validateDeviceId(int deviceId, int deviceCount);
	int imageSupport();
	int validateDeviceId();
	cl::Device getCurrentDevice();


};


int DeviceCL::validateDeviceId(int deviceId, int deviceCount)
{


	if (deviceCount == 0)
	{
		notice("No device available\n");
		//std::cout << "No device available\n";
		return SDK_FAILURE;
	}

	// Validate deviceIndex
	if(deviceId >= (int)deviceCount)
	{
		std::cout << "DeviceId should be < " << deviceCount << std::endl;
		return SDK_FAILURE;
	}


	if(imageSupport()!=CL_SUCCESS){
		return SDK_FAILURE;
	}

	return SDK_SUCCESS;
};

int DeviceCL::imageSupport()
{

	// Check for image support
	int imageSupport = devices[currentDeviceId].getInfo<CL_DEVICE_IMAGE_SUPPORT>(&err);
	CheckError(err,"Device::getInfo() failed.",GetFileAndLine(__FILE__,__LINE__));

	//CHECK_OPENCL_ERROR(err, "Device::getInfo() failed.");

	// If images are not supported then return
	if(!imageSupport)
	{

		error("Images are not supported on this device!");
		return SDK_FAILURE;
	}

	return SDK_SUCCESS;

};

cl::Device DeviceCL::getCurrentDevice(){

	return devices[currentDeviceId];

}

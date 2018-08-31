class CommandQueueCL:BaseCL
{
  
	public:

        cl::CommandQueue commandQueue;                  /**< CL command queue */


        cl_int err;


	CommandQueueCL():BaseCL((char*)"CommandQueueCL"){
		err= CL_SUCCESS;


	}


	~CommandQueueCL(){
	}


	int CreateCommandQueue(cl::Context context,std::vector<cl::Device> devices,int deviceId);




};


	int CommandQueueCL::CreateCommandQueue(cl::Context context, std::vector<cl::Device> devices,int deviceId){


		commandQueue = cl::CommandQueue(context, devices[deviceId], 0,&err);

		if(CheckError(err,"CommandQueue::CommandQueue() failed.",GetFileAndLine(__FILE__,__LINE__))!=CL_SUCCESS){
			return SDK_FAILURE;
		}

		return SDK_SUCCESS;

};



 class BaseCL
{
  
	private:

	#ifdef DEBUG
		//LogCL log;
		char msg[100];
	#endif




	public:

	 void MessageLog(char* className);
	 int CheckError(int actual, std::string message);
	 int CheckError(int actual, std::string message, std::string location);
	 std::string GetFileAndLine(const char* file, int line);

	 BaseCL(char* className){

	#ifdef DEBUG
		MessageLog(className);
	#endif
	}


	~BaseCL(){
	}

};

	 void BaseCL::MessageLog(char* className)
	{

		strcpy(msg,className); // copy string one into the result.
		strcat(msg,(char*)" Construído"); // append string two to the result.
		LogCL::getInstance()->WriteLogFile(msg);
	 
	};


	 int BaseCL::CheckError(int actual, std::string message)
	{
		return ErrorCL::getInstance()->CHECK_OPENCL_ERROR(actual,message);

	};

	 int BaseCL::CheckError(int actual, std::string message,std::string location)
	{
		return ErrorCL::getInstance()->CHECK_OPENCL_ERROR(actual,message,location);

	};

	 std::string BaseCL::GetFileAndLine(const char* file,int line)
	{

		strcpy(msg,(char*)"Location:"); 
		strcat(msg,file); 
		strcat(msg,":"); 
		char integer_string[32];

 		sprintf(integer_string, "%d", line);
		strcat(msg,integer_string); 

		//cout<<msg<<endl;
		std::string str(msg);
	
		return str ;
	};






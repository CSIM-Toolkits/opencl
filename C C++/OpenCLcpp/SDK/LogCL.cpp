//#include <ErrorCL.cpp>

class LogCL
{
  
	private:

	char* nameTxtFile;

	static LogCL* instance;

	static bool FirstInstanceFlag;  

//	ErrorCL error; 

	LogCL(){

		nameTxtFile = (char*)"log.txt";

	};


	public:

	~LogCL(){
		FirstInstanceFlag = false;
		delete instance;
	};

	void WriteLogFile(char* szString);

	void InitializeLogFile();

	const std::string currentDateTime();

	static LogCL* getInstance();


};

	 bool LogCL::FirstInstanceFlag = false;
         LogCL* LogCL::instance = NULL;

	 LogCL* LogCL::getInstance(){

		if(!FirstInstanceFlag){
			instance= new LogCL();
                        instance->InitializeLogFile();
			FirstInstanceFlag=true;
		}
		return instance;

	};



	void LogCL::WriteLogFile(char* szString)
	{


		FILE* pFile = fopen(nameTxtFile, "a");
		fprintf(pFile, "%s\n",szString);
		fclose(pFile);

	 
	};

	void LogCL::InitializeLogFile()
	{


		FILE* pFile = fopen(nameTxtFile, "a");
		
		string msg="--------------------Start - "+ currentDateTime() +" -------------------";

		fprintf(pFile, "%s\n",msg.c_str());
		fclose(pFile);

	 
	};


	const std::string LogCL::currentDateTime() {

		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%d-%m-%Y - %X", &tstruct);

		return buf;
	};


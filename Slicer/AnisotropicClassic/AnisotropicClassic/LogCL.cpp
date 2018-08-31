//#include <ErrorCL.cpp>

class LogCL
{

private:

    char* nameTxtFile;


public:

    LogCL(){

        nameTxtFile = (char*)"log.txt";
        InitializeLogFile();
    };

    LogCL(char* nameTxt){

        nameTxtFile = nameTxt;

        InitializeLogFile();

    };

    ~LogCL(){};

    void WriteLogFile(char* szString);
    void WriteLogFile(int szString);
    void WriteLogFile(float szString);

    void InitializeLogFile();

    const std::string currentDateTime();


};




void LogCL::WriteLogFile(char* szString)
{


    FILE* pFile = fopen(nameTxtFile, "a");
    fprintf(pFile, "%s\n",szString);
    fclose(pFile);


};

void LogCL::WriteLogFile(int szString)
{


    FILE* pFile = fopen(nameTxtFile, "a");
    fprintf(pFile, "%d\n",szString);
    fclose(pFile);


};

void LogCL::WriteLogFile(float szString)
{


    FILE* pFile = fopen(nameTxtFile, "a");
    fprintf(pFile, "%f\n",szString);
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




#pragma once




/**
 * sdkVersionStr
 * struct to form AMD APP SDK version
 */
static struct sdkVersionStr
{
    int major;      /**< SDK major release number */
    int minor;      /**< SDK minor release number */
    int subminor;   /**< SDK sub-minor release number */
    int build;      /**< SDK build number */
    int revision;   /**< SDK revision number */

    /**
     * Constructor
     */
     inline sdkVersionStr()
    {
        major = SDK_VERSION_MAJOR;
        minor = SDK_VERSION_MINOR;
        subminor = SDK_VERSION_SUB_MINOR;
        build = SDK_VERSION_BUILD;
        revision = SDK_VERSION_REVISION;
    }
} sdkVerStr;


/**************************************************************************
* CmdArgsEnum                                                             *
* Enum for datatype of CmdArgs                                            *
**************************************************************************/
enum ArgsEnum
{
    TYPE_INT,TYPE_FLOAT,TYPE_DOUBLE,TYPE_STRING,TYPE_INBUFFER,TYPE_OUTBUFFER
};


struct BuildOption{
    std::string name;
    void* value;
    ArgsEnum type;
};

struct BufferObj{
    cl::Buffer buffer;
    float * data;
    float dataFLOAT;
    int dataINT;
    size_t size;
    ArgsEnum type;
};




static void error(std::string errorMsg)
{
    std::cerr<<"Error: "<<errorMsg<<std::endl;
}

static void message(std::string Msg)
{
    std::cout<<Msg<<std::endl;
}



void printer(std::string name, int value) {
    std::cout<<name<<": "<< value <<std::endl;
    //printf("name: %s\tvalue: %d\n", name.c_str(), value);
}

void printer(std::string name, float value) {
    std::cout<<name<<": "<< value <<std::endl;
    //printf("name: %s\tvalue: %f\n", name.c_str(), value);
}

void printer(std::string name, double value) {
    std::cout<<name<<": "<< value <<std::endl;
    //printf("name: %s\tvalue: %f\n", name.c_str(), value);
}


void printer(std::string name, string value) {
    std::cout<<name<<": "<< value <<std::endl;
    //printf("name: %s\tvalue: %s\n", name.c_str(), value.c_str());
}

void printer(std::string name, cl_uint value) {
    std::cout<<name<<": "<< (int)value <<std::endl;
    //printf("name: %s\tvalue: %s\n", name.c_str(), value.c_str());
}






/**
* compare template version
* compare data to check error
* @param refData templated input
* @param data templated input
* @param length number of values to compare
* @param epsilon errorWindow
*/
static bool compare(const float *refData, const float *data,
             const int length, const float epsilon = 1e-6f)
{
    float error = 0.0f;
    float ref = 0.0f;
    for(int i = 1; i < length; ++i)
    {
        float diff = refData[i] - data[i];
        error += diff * diff;
        ref += refData[i] * refData[i];
    }
    float normRef =::sqrtf((float) ref);
    if (::fabs((float) ref) < 1e-7f)
    {
        return false;
    }
    float normError = ::sqrtf((float) error);
    error = normError / normRef;
    return error < epsilon;
}
static bool compare(const double *refData, const double *data,
             const int length, const double epsilon = 1e-6)
{
    double error = 0.0;
    double ref = 0.0;
    for(int i = 1; i < length; ++i)
    {
        double diff = refData[i] - data[i];
        error += diff * diff;
        ref += refData[i] * refData[i];
    }
    double normRef =::sqrt((double) ref);
    if (::fabs((double) ref) < 1e-7)
    {
        return false;
    }
    double normError = ::sqrt((double) error);
    error = normError / normRef;
    return error < epsilon;
}

/**
 * strComparei
 * Case insensitive compare of 2 strings
 * returns true when strings match(case insensitive), false otherwise
 */
static bool strComparei(std::string a, std::string b)
{
    int sizeA = (int)a.size();
    if (b.size() != sizeA)
    {
        return false;
    }
    for (int i = 0; i < sizeA; i++)
    {
        if (tolower(a[i]) != tolower(b[i]))
        {
            return false;
        }
    }
    return true;
}

/**
 * toString
 * convert a T type to string
 */
template<typename T>
std::string toString(T t, std::ios_base & (*r)(std::ios_base&) = std::dec)
{
    std::ostringstream output;
    output << r << t;
    return output.str();
}


/**
 * filetoString
 * converts any file into a string
 * @param file string message
 * @param str string message
 * @return 0 on success Positive if expected and Non-zero on failure
 */
static int fileToString(std::string &fileName, std::string &str)
{
    size_t      size;
    char*       buf;
    // Open file stream
    std::fstream f(fileName.c_str(), (std::fstream::in | std::fstream::binary));
    // Check if we have opened file stream
    if (f.is_open())
    {
        size_t  sizeFile;
        // Find the stream size
        f.seekg(0, std::fstream::end);
        size = sizeFile = (size_t)f.tellg();
        f.seekg(0, std::fstream::beg);
        buf = new char[size + 1];
        if (!buf)
        {
            f.close();
            return  SDK_FAILURE;
        }
        // Read file
        f.read(buf, sizeFile);
        f.close();
        str[size] = '\0';
        str = buf;
        return SDK_SUCCESS;
    }
    else
    {
        error("Converting file to string. Cannot open file.");
        str = "";
        return SDK_FAILURE;
    }
}

/**
*******************************************************************
* @fn printArray
* @brief displays a array on std::out
******************************************************************/
template<typename T>
void printArray(
    const std::string header,
    const T * data,
    const int width,
    const int height)
{
    std::cout<<"\n"<<header<<"\n";
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            std::cout<<data[i*width+j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

/**
*******************************************************************
* @fn printArray
* @brief displays a array of opencl vector types on std::out
******************************************************************/
template<typename T>
void printArray(
    const std::string header,
    const T * data,
    const int width,
    const int height,
	int veclen)
{
    std::cout<<"\n"<<header<<"\n";
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            std::cout << "(";
			for(int k=0; k<veclen; k++)
			{
				std::cout<<data[i*width+j].s[k]<<", ";
			}
			std::cout << ") ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}


/**
*******************************************************************
* @fn printArray overload function
* @brief displays a array on std::out
******************************************************************/
template<typename T>
void printArray(
    const std::string header,
    const std::vector<T>& data,
    const int width,
    const int height)
{
    std::cout<<"\n"<<header<<"\n";
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            std::cout<<data[i*width+j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}


void printArrayString(
    const std::string header,
    const std::vector<string>& data,
    const int width)
{
    std::cout<<"\n"<<header<<"\n";

	for(int j = 0; j < width; j++)
	{
	    std::cout<<"["<<j<<"] = ";
	    std::cout<<data[j]<<endl;
	}
	std::cout<<"\n";
   
}


/**
 * printstats
 * Print the results from the test
 * @param stdStr Parameter
 * @param stats Statistic value of parameter
 * @param n number
 */
static void printStatistics(std::string *statsStr, std::string * stats, int n)
{
    int *columnWidth = new int[n];
    if(columnWidth == NULL)
    {
        return;
    }
    std::cout << std::endl << "|";
    for(int i=0; i<n; i++)
    {
        columnWidth[i] = (int) ((statsStr[i].length() > stats[i].length())?
                                statsStr[i].length() : stats[i].length());
        std::cout << " " << std::setw(columnWidth[i]+1) << std::left << statsStr[i] <<
                  "|";
    }
    std::cout << std::endl << "|";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<(columnWidth[i]+2); j++)
        {
            std::cout << "-";
        }
        std::cout << "|";
    }
    std::cout << std::endl << "|";
    for(int i=0; i<n; i++)
    {
        std::cout << " " << std::setw(columnWidth[i]+1) << std::left << stats[i] << "|";
    }
    std::cout << std::endl;
    if(columnWidth)
    {
        delete[] columnWidth;
    }
}

/**
 * fillRandom
 * fill array with random values
 */
template<typename T>
int fillRandom(
    T * arrayPtr,
    const int width,
    const int height,
    const T rangeMin,
    const T rangeMax,
    unsigned int seed=123)
{
    if(!arrayPtr)
    {
        error("Cannot fill array. NULL pointer.");
        return SDK_FAILURE;
    }
    if(!seed)
    {
        seed = (unsigned int)time(NULL);
    }
    srand(seed);
    double range = double(rangeMax - rangeMin) + 1.0;
    /* random initialisation of input */
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            int index = i*width + j;
            arrayPtr[index] = rangeMin + T(range*rand()/(RAND_MAX + 1.0));
        }
    return SDK_SUCCESS;
}

/**
 * fillPos
 * fill the specified positions
 */
template<typename T>
int fillPos(
    T * arrayPtr,
    const int width,
    const int height)
{
    if(!arrayPtr)
    {
        error("Cannot fill array. NULL pointer.");
        return SDK_FAILURE;
    }
    /* initialisation of input with positions*/
    for(T i = 0; i < height; i++)
        for(T j = 0; j < width; j++)
        {
            T index = i*width + j;
            arrayPtr[index] = index;
        }
    return SDK_SUCCESS;
}

/**
 * fillConstant
 * fill the array with constant value
 */
template<typename T>
int fillConstant(
    T * arrayPtr,
    const int width,
    const int height,
    const T val)
{
    if(!arrayPtr)
    {
        error("Cannot fill array. NULL pointer.");
        return SDK_FAILURE;
    }
    /* initialisation of input with constant value*/
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            int index = i*width + j;
            arrayPtr[index] = val;
        }
    return SDK_SUCCESS;
}


/**
 * roundToPowerOf2
 * rounds to a power of 2
 */
template<typename T>
T roundToPowerOf2(T val)
{
    int bytes = sizeof(T);
    val--;
    for(int i = 0; i < bytes; i++)
    {
        val |= val >> (1<<i);
    }
    val++;
    return val;
}

/**
 * isPowerOf2
 * checks if input is a power of 2
 */
template<typename T>
int isPowerOf2(T val)
{
    long long _val = val;
    if((_val & (-_val))-_val == 0 && _val != 0)
    {
        return SDK_SUCCESS;
    }
    else
    {
        return SDK_FAILURE;
    }
}

/**
        * getPath
        * @return path of the current directory
        */
static std::string getPath()
{
#ifdef _WIN32
    char buffer[MAX_PATH];
#ifdef UNICODE
    if(!GetModuleFileName(NULL, (LPWCH)buffer, sizeof(buffer)))
    {
        throw std::string("GetModuleFileName() failed!");
    }
#else
    if(!GetModuleFileName(NULL, buffer, sizeof(buffer)))
    {
        throw std::string("GetModuleFileName() failed!");
    }
#endif
    std::string str(buffer);
    /* '\' == 92 */
    int last = (int)str.find_last_of((char)92);
#else
    char buffer[PATH_MAX + 1];
    ssize_t len;
    if((len = readlink("/proc/self/exe",buffer, sizeof(buffer) - 1)) == -1)
    {
        throw std::string("readlink() failed!");
    }
    buffer[len] = '\0';
    std::string str(buffer);
    /* '/' == 47 */
    int last = (int)str.find_last_of((char)47);
#endif
    return str.substr(0, last + 1);
}


/**
***********************************************************************
* @brief Returns SDK Version string
* @return std::string
**********************************************************************/
static std::string getSdkVerStr()
{
    char str[1024];
    std::string dbgStr("");
    std::string internal("");
#ifdef _WIN32
#ifdef _DEBUG
    dbgStr.append("-dbg");
#endif
#else
#ifdef NDEBUG
    dbgStr.append("-dbg");
#endif
#endif
#if defined (_WIN32) && !defined(__MINGW32__)
    sprintf_s(str, 256, "AMD-APP-SDK-v%d.%d.%d%s%s (%d.%d)",
              sdkVerStr.major,
              sdkVerStr.minor,
              sdkVerStr.subminor,
              internal.c_str(),
              dbgStr.c_str(),
              sdkVerStr.build,
              sdkVerStr.revision);
#else
    sprintf(str, "AMD-APP-SDK-v%d.%d.%d%s%s (%d.%d)",
            sdkVerStr.major,
            sdkVerStr.minor,
            sdkVerStr.subminor,
            internal.c_str(),
            dbgStr.c_str(),
            sdkVerStr.build,
            sdkVerStr.revision);
#endif
    return std::string(str);
}


void printPointerVoid( void* pointer, string type ) {

	if(type.compare("int")==0){
		int *value = (int *)pointer;
		cout << *value << endl;
	}else if(type.compare("double")==0){
		double *value = (double *)pointer;
		cout << *value << endl;
	}else if(type.compare("float")==0){
		float *value = (float *)pointer;
		cout << *value << endl;
	}else if(type.compare("string")==0){
		string *value = (string *)pointer;
		cout << *value << endl;
	}


}


vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}


std::vector<string> listdir(const char *dirname) {
  DIR *dp;
  dirent *d;
  vector<string> vec;

  dp = opendir(dirname);
  while((d = readdir(dp)) != NULL){
	
	if(strcmp(d->d_name,".") != 0 && strcmp(d->d_name,"..") != 0 && strcmp(d->d_name,"...") != 0){    
		//cout<<"Nome: "<<d->d_name<<endl;		
		vec.push_back(d->d_name);
	}
}

  sort(vec.begin(), vec.end());
  return vec;
}

std::string removeExt(std::string kernelName){
	const std::string ext(".cl");
	if ( kernelName != ext &&
	     kernelName.size() > ext.size() &&
	     kernelName.substr(kernelName.size() - ext.size()) == ".cl" )
	{
	   // if so then strip them off
	   kernelName = kernelName.substr(0, kernelName.size() - ext.size());
	}
	return kernelName;
}



template<typename T>
static const char* getOpenCLErrorCodeStr(T input)
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
        return "unknown error code";
    }
}

/**
        * checkVal
        * Set default(isAPIerror) parameter to false
        * if checkVaul is used to check otherthan OpenCL API error code
        */
template<typename T>
static int checkVal(
    T input,
    T reference,
    std::string message, bool isAPIerror = true)
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
}

std::string CreateStringBuildOptions(std::vector<BuildOption> vect){

    std::string buildOption= "";
    std::vector<BuildOption>::iterator i;
    int j = 0;
#ifdef VERBOSE
    std::cout << "BuildOptions Size: " << vect.size()<<std::endl;
#endif

    for (i = vect.begin(); i < vect.end(); ++i, ++j)
    {
        void* VoidValue = (*i).value;
        if((*i).type==TYPE_INT){
            int Value = *(int *)VoidValue;
            //std::cout<<toString(Value)<<std::endl;
            buildOption = buildOption + "-D "+ (*i).name+"="+toString(Value)+" ";
        }else if((*i).type==TYPE_FLOAT){
            float Value = *(float *)VoidValue;
            buildOption = buildOption + "-D "+ (*i).name+"="+toString(Value)+" ";
        }else if((*i).type==TYPE_STRING){
            std::string Value = *(std::string *)VoidValue;
            buildOption = buildOption + "-D "+ (*i).name+"="+toString(Value)+" ";
        }else if((*i).type==TYPE_DOUBLE){
            double Value = *(double *)VoidValue;
            buildOption = buildOption + "-D "+ (*i).name+"="+toString(Value)+" ";
        }


    }


#ifdef VERBOSE
    DEBUG(buildOption);
#endif

    return buildOption;
}


bool isOdd( int integer )
{

  if ( integer % 2== 0 )
     return true;
  else
     return false;
}


class SDKFile
{
    public:
        /**
         *Default constructor
         */
        SDKFile(): source_("") {}

        /**
         * Destructor
         */
        ~SDKFile() {};

        /**
         * Opens the CL program file
         * @return true if success else false
         */
        bool open(const char* fileName)
        {
            size_t      size;
            char*       str;
            // Open file stream
            std::fstream f(fileName, (std::fstream::in | std::fstream::binary));
            // Check if we have opened file stream
            if (f.is_open())
            {
                size_t  sizeFile;
                // Find the stream size
                f.seekg(0, std::fstream::end);
                size = sizeFile = (size_t)f.tellg();
                f.seekg(0, std::fstream::beg);
                str = new char[size + 1];
                if (!str)
                {
                    f.close();
                    return  false;
                }
                // Read file
                f.read(str, sizeFile);
                f.close();
                str[size] = '\0';
                source_  = str;
                delete[] str;
                return true;
            }
            return false;
        }

        /**
         * writeBinaryToFile
         * @param fileName Name of the file
         * @param binary char binary array
         * @param numBytes number of bytes
         * @return true if success else false
         */
        int writeBinaryToFile(const char* fileName, const char* binary, size_t numBytes)
        {
            FILE *output = NULL;
            output = fopen(fileName, "wb");
            if(output == NULL)
            {
                return SDK_FAILURE;
            }
            fwrite(binary, sizeof(char), numBytes, output);
            fclose(output);
            return SDK_SUCCESS;
        }


        /**
         * readBinaryToFile
         * @param fileName name of file
         * @return true if success else false
         */
        int readBinaryFromFile(const char* fileName)
        {
            FILE * input = NULL;
            size_t size = 0,val;
            char* binary = NULL;
            input = fopen(fileName, "rb");
            if(input == NULL)
            {
                return SDK_FAILURE;
            }
            fseek(input, 0L, SEEK_END);
            size = ftell(input);
            rewind(input);
            binary = (char*)malloc(size);
            if(binary == NULL)
            {
                return SDK_FAILURE;
            }
            val=fread(binary, sizeof(char), size, input);
            fclose(input);
            source_.assign(binary, size);
            free(binary);
            return SDK_SUCCESS;
        }


        /**
         * Replaces Newline with spaces
         */
        void replaceNewlineWithSpaces()
        {
            size_t pos = source_.find_first_of('\n', 0);
            while(pos != -1)
            {
                source_.replace(pos, 1, " ");
                pos = source_.find_first_of('\n', pos + 1);
            }
            pos = source_.find_first_of('\r', 0);
            while(pos != -1)
            {
                source_.replace(pos, 1, " ");
                pos = source_.find_first_of('\r', pos + 1);
            }
        }

        /**
         * source
         * Returns a pointer to the string object with the source code
         */
        const std::string&  source() const
        {
            return source_;
        }

    private:
        /**
         * Disable copy constructor
         */
        SDKFile(const SDKFile&);

        /**
         * Disable operator=
         */
        SDKFile& operator=(const SDKFile&);

        std::string     source_;    //!< source code of the CL program
};

/**
 * textFile
 * struct to manpulate file
 */
struct textFile
{
    std::string fileName;             /**< fileName name of the file */
    std::string filePath;             /**< filePath name of the file */

    /**
     * Constructor
     */
    textFile()
    {
        fileName = std::string("");
        filePath = std::string("");
    }
};


void writeImageTextFile(const textFile textfile, float *pixelDataOut,int width, int height, int deep){

    std::cout << "file Path:  "<< textfile.filePath<< std::endl;
    std::string fullPath = textfile.filePath;

    fullPath.append(textfile.fileName);

    ofstream myfile;
    myfile.open (fullPath.c_str());


    for(int giz=0; giz<deep; giz++){
        myfile << "\n";
        myfile << "\n";
        for(int giy=0; giy<height; giy++){
            myfile << "\n";
            for(int gix=0; gix<width; gix++){

                unsigned int gidx = width*(giz*height + giy) + gix;
                myfile<<pixelDataOut[gidx]<<" ";

            }
        }
    }

    /*
    for(int giz=0; giz<deep;giz++){
        myfile << "------------- Deep="<< giz <<"0 \n";

        for(int gix=0; gix<width; gix++){
            myfile << "\n";
            for(int giy=0; giy<heigth; giy++){
                unsigned int gidx = width*(giz*heigth + giy) + gix;
                    myfile<<pixelDataOut[gidx]<<" ";

            }
        }
        myfile << "\n";
    }*/

    myfile.close();

}




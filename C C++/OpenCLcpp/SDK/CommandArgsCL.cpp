

#include <clInfoTest.h>
/**
* CLCommandArgs class contains all the
* command arguments related info passed by the user inlcuding
* the decvice and platform infos.
*/
class CommandArgsCL : public CmdArgsParserCL
{

    protected:
        
        //
        bool enableDeviceId;           /**< If deviceId used */
        bool enablePlatform;           /**< If platformId Used */
        bool gpu;                      /**< If GPU used */
        bool amdPlatform;              /**< If AMD Platform Used */
    public:
        bool multiDevice;              /**< Cmd Line Option- if MultiGPU */
        unsigned int deviceId;         /**< Cmd Line Option- device number */
        unsigned int platformId;       /**< Cmd Line Option- platform number */
        unsigned int kernelId;         /**< Cmd Line Option- kernel number */
        std::string deviceType;        /**< Cmd Line Option- set device type(cpu|gpu) */
        std::string dumpBinary;        /**< Cmd Line Option- Dump Binary with name */
        std::string loadBinary;        /**< Cmd Line Option- Load Binary with name */
        std::string flags;             /**< Cmd Line Option- compiler flags */

        /**
        */
        CommandArgsCL(bool enableMultiDevice = false)
            :CmdArgsParserCL ()
        {
            deviceType = "gpu";
            multiDevice = enableMultiDevice;
            deviceId = 0;
            platformId = 0;
            enablePlatform = false;
            enableDeviceId = false;
            gpu = true;
            amdPlatform = false;
        }

        /**
        * isDumpBinaryEnabled
        * Checks if dump Binary Option is enabled
        * @return true if DumpBinary Enabled else false
        */
        bool isDumpBinaryEnabled()
        {
            if(dumpBinary.size() == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        /**
         * isLoadBinaryEnabled
         * Checks if the sample wants to load a prebuilt binary
         * @return true if LoadBinary Enabled else false
         */
        bool isLoadBinaryEnabled()
        {
            if(loadBinary.size() == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        /**
         * isCompilerFlagsSpecified
         * Checks if any compiler flag is specified for the kernel
         * @return true if CompierFlag Enabled else false
         */
        bool isComplierFlagsSpecified()
        {
            if(flags.size() == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        /**
         * isPlatformEnabled
         * Checks if platform option is used
         * @return true if PlatformId Enabled else false
         */
        bool isPlatformEnabled()
        {
            return enablePlatform;
        }

        /**
         * isDeviceEnabled
         * Checks if device option is used
         * @return true if DeviceId Enabled else false
         */
        bool isDeviceIdEnabled()
        {
            return enableDeviceId;
        }

        /**
         * isThereGPU
         * Checks if a GPU is Present
         * @return true if GPU Present else false
         */
        bool isThereGPU()
        {
            return gpu;
        }

        /**
         * isAmdPlatform
         * Checks if AMD Platform is used
         * @return true if AMD Platform Enabled else false
         */
        bool isAmdPlatform()
        {
            return amdPlatform;
        }


        /**
        * parseCommandLine
        * parses the command line options given by user
        * @param argc Number of elements in cmd line input
        * @param argv array of char* storing the CmdLine Options
        * @return 0 on success Positive if expected and Non-zero on failure
        */
        int parseCommandLine(int argc, char **argv)
        {
            if(!parse(argv,argc))
            {
                usage();
                if((isArgSet("h",true) == true) || (isArgSet("help",false) == true))
                {
                    exit(SDK_SUCCESS);
                }
                return SDK_FAILURE;
            }
            if((isArgSet("h",true) == true) || (isArgSet("help",false) == true))
            {
                usage();
                exit(SDK_SUCCESS);
            }
            // Print the sdk version and exit the application
            if(isArgSet("v", true) || isArgSet("version", false))
            {
                std::cout << "SDK version : " << sampleVerStr.c_str() << std::endl;
                exit(0);
            }

            if(isArgSet("printKernels", false))
            {

		std::string filePath = getPath() + "kernels";    
            	//cout<<filePath<<endl;
		std::vector<string> kernels; 
		kernels = listdir(filePath.c_str());
		printArrayString("Kernels Availables: ", kernels, kernels.size());
                exit(0);
            }

            if(isArgSet("compileKernelId", false))
            {

		std::string filePath = getPath() + "kernels";    
            	//cout<<filePath<<endl;
		std::vector<string> kernels; 
		kernels = listdir(filePath.c_str());
		//printArrayString("Kernels Availables: ", kernels, kernels.size());
                exit(0);
            }

            if(isArgSet("infoAll", false))
            {

		infoTest();
                exit(0);
            }


            if(isArgSet("p",true) || isArgSet("platformId",false))
            {
                enablePlatform = true;
            }
            if(isArgSet("d",true) || isArgSet("deviceId",false))
            {
                enableDeviceId = true;
            }
            /* check about the validity of the device type */
            if(multiDevice)
            {
                if(!((deviceType.compare("cpu") == 0 )
                        || (deviceType.compare("gpu") ==0)
                        || (deviceType.compare("all") ==0)))
                {
                    std::cout << "Error. Invalid device options. "
                              << "only \"cpu\" or \"gpu\" or \"all\" supported\n";
                    usage();
                    return SDK_FAILURE;
                }
            }
            else
            {
                if(!((deviceType.compare("cpu") == 0 ) || (deviceType.compare("gpu") ==0)))
                {
                    std::cout << "Error. Invalid device options. "
                              << "only \"cpu\" or \"gpu\" or \"all\" supported\n";
                    usage();
                    return SDK_FAILURE;
                }
            }
            if(dumpBinary.size() != 0 && loadBinary.size() != 0)
            {
                std::cout << "Error. --dump and --load options are mutually exclusive\n";
                usage();
                return SDK_FAILURE;
            }
            if(loadBinary.size() != 0 && flags.size() != 0)
            {
                std::cout << "Error. --flags and --load options are mutually exclusive\n";
                usage();
                return SDK_FAILURE;
            }
            if(validatePlatformAndDeviceOptions() != SDK_SUCCESS)
            {
                std::cout << "validatePlatfromAndDeviceOptions failed.\n ";
                return SDK_FAILURE;
            }
            return SDK_SUCCESS;
        }

        /**
         * validatePlatformAndDeviceOptions
         * Validates if the intended platform and device is used
         * @return 0 on success Positive if expected and Non-zero on failure
         */
        int validatePlatformAndDeviceOptions()
        {
            cl_int status = CL_SUCCESS;
            cl_uint numPlatforms;
            cl_platform_id platform = NULL;
            status = clGetPlatformIDs(0, NULL, &numPlatforms);
            if(status != CL_SUCCESS)
            {
	        //std::cout<<"Error: clGetPlatformIDs failed. Error code : ";
                //std::cout << getOpenCLErrorCodeStr(status) << std::endl;
		ErrorCL::getInstance()->CHECK_OPENCL_ERROR(status,"clGetPlatformIDs failed");
                return SDK_FAILURE;
            }
            if (0 < numPlatforms)
            {
                // Validate platformId
                if(platformId >= numPlatforms)
                {
                    if(numPlatforms - 1 == 0)
                    {
                        std::cout << "platformId should be 0" << std::endl;
                    }
                    else
                    {
                        std::cout << "platformId should be 0 to " << numPlatforms - 1 << std::endl;
                    }
                    usage();
                    return SDK_FAILURE;
                }
                // Get selected platform
                cl_platform_id* platforms = new cl_platform_id[numPlatforms];
                status = clGetPlatformIDs(numPlatforms, platforms, NULL);
                if(status != CL_SUCCESS)
                {
                    //std::cout<<"Error: clGetPlatformIDs failed. Error code : ";
                    //std::cout << getOpenCLErrorCodeStr(status) << std::endl;
		    ErrorCL::getInstance()->CHECK_OPENCL_ERROR(status,"clGetPlatformIDs failed");
                    return SDK_FAILURE;
                }
                // Print all platforms
                for (unsigned i = 0; i < numPlatforms; ++i)
                {
                    char pbuf[100];
                    status = clGetPlatformInfo(platforms[i],
                                               CL_PLATFORM_VENDOR,
                                               sizeof(pbuf),
                                               pbuf,
                                               NULL);
                    if(status != CL_SUCCESS)
                    {
                        //std::cout<<"Error: clGetPlatformInfo failed. Error code : ";
                        //std::cout << getOpenCLErrorCodeStr(status) << std::endl;
            		ErrorCL::getInstance()->CHECK_OPENCL_ERROR(status,"clGetPlatformInfo failed");
                        return SDK_FAILURE;
                    }
                    //std::cout << "Platform " << i << " : " << pbuf << std::endl;
                }
                // Get AMD platform
                for (unsigned i = 0; i < numPlatforms; ++i)
                {
                    char pbuf[100];
                    status = clGetPlatformInfo(platforms[i],
                                               CL_PLATFORM_VENDOR,
                                               sizeof(pbuf),
                                               pbuf,
                                               NULL);
                    if(status != CL_SUCCESS)
                    {
                        //std::cout<<"Error: clGetPlatformInfo failed. Error code : ";
                        //std::cout << getOpenCLErrorCodeStr(status) << std::endl;
         		ErrorCL::getInstance()->CHECK_OPENCL_ERROR(status,"clGetPlatformInfo failed");
                        return SDK_FAILURE;
                    }
                    platform = platforms[i];
                    if (!strcmp(pbuf, "Advanced Micro Devices, Inc."))
                    {
                        break;
                    }
                }
                if(isPlatformEnabled())
                {
                    platform = platforms[platformId];
                }
                // Check for AMD platform
                char pbuf[100];
                status = clGetPlatformInfo(platform,
                                           CL_PLATFORM_VENDOR,
                                           sizeof(pbuf),
                                           pbuf,
                                           NULL);
                if(status != CL_SUCCESS)
                {
                    //std::cout<<"Error: clGetPlatformInfo failed. Error code : ";
                    //std::cout << getOpenCLErrorCodeStr(status) << std::endl;
		    ErrorCL::getInstance()->CHECK_OPENCL_ERROR(status,"clGetPlatformInfo failed");

                    return SDK_FAILURE;
                }
                if (!strcmp(pbuf, "Advanced Micro Devices, Inc."))
                {
                    amdPlatform = true;
                }
                cl_device_type dType = CL_DEVICE_TYPE_GPU;
                if(deviceType.compare("cpu") == 0)
                {
                    dType = CL_DEVICE_TYPE_CPU;
                }
                if(deviceType.compare("gpu") == 0)
                {
                    dType = CL_DEVICE_TYPE_GPU;
                }
                else
                {
                    dType = CL_DEVICE_TYPE_ALL;
                }
                // Check for GPU
                if(dType == CL_DEVICE_TYPE_GPU)
                {
                    cl_context_properties cps[3] =
                    {
                        CL_CONTEXT_PLATFORM,
                        (cl_context_properties)platform,
                        0
                    };
                    cl_context context = clCreateContextFromType(cps,
                                         dType,
                                         NULL,
                                         NULL,
                                         &status);
                    if(status == CL_DEVICE_NOT_FOUND)
                    {
                        dType = CL_DEVICE_TYPE_CPU;
                        gpu = false;
                    }
                    clReleaseContext(context);
                }
                // Get device count
                cl_uint deviceCount = 0;
                status = clGetDeviceIDs(platform, dType, 0, NULL, &deviceCount);
                if(status != CL_SUCCESS)
                {
                    //std::cout<<"Error: clGetDeviceIDs failed. Error code : ";
                    //std::cout << getOpenCLErrorCodeStr(status) << std::endl;
		    ErrorCL::getInstance()->CHECK_OPENCL_ERROR(status,"clGetDeviceIDs failed");
                    return SDK_FAILURE;
                }
                // Validate deviceId
                if(deviceId >= deviceCount)
                {
                    if(deviceCount - 1 == 0)
                    {
                        std::cout << "deviceId should be 0" << std::endl;
                    }
                    else
                    {
                        std::cout << "deviceId should be 0 to " << deviceCount - 1 << std::endl;
                    }
                    usage();
                    return SDK_FAILURE;
                }
                delete[] platforms;
            }
            return SDK_SUCCESS;
        }
        int initialize()
        {
            int defaultOptions = 11;
            if(multiDevice)
            {
                defaultOptions = 10;
            }
            Option *optionList = new Option[defaultOptions];
            CHECK_ALLOCATION(optionList, "Error. Failed to allocate memory (optionList)\n");
            optionList[0]._sVersion = "";
            optionList[0]._lVersion = "device";
            if(multiDevice)
            {
                optionList[0]._description = "Execute the openCL kernel on a device";
                optionList[0]._usage = "[cpu|gpu|all]";
            }
            else
            {
                optionList[0]._description = "Execute the openCL kernel on a device";
                optionList[0]._usage = "[cpu|gpu]";
            }
            optionList[0]._type = CA_ARG_STRING;
            optionList[0]._value = &deviceType;
            optionList[1]._sVersion = "q";
            optionList[1]._lVersion = "quiet";
            optionList[1]._description = "Quiet mode. Suppress all text output.";
            optionList[1]._usage = "";
            optionList[1]._type = CA_NO_ARGUMENT;
            optionList[1]._value = &quiet;
            optionList[2]._sVersion = "e";
            optionList[2]._lVersion = "verify";
            optionList[2]._description = "Verify results against reference implementation.";
            optionList[2]._usage = "";
            optionList[2]._type = CA_NO_ARGUMENT;
            optionList[2]._value = &verify;
            optionList[3]._sVersion = "t";
            optionList[3]._lVersion = "timing";
            optionList[3]._description = "Print timing.";
            optionList[3]._type = CA_NO_ARGUMENT;
            optionList[3]._value = &timing;
            
/*
	    optionList[4]._sVersion = "";
            optionList[4]._lVersion = "dump";
            optionList[4]._description = "Dump binary image for all devices";
            optionList[4]._usage = "[filename]";
            optionList[4]._type = CA_ARG_STRING;
            optionList[4]._value = &dumpBinary;
            optionList[5]._sVersion = "";
            optionList[5]._lVersion = "load";
            optionList[5]._description = "Load binary image and execute on device";
            optionList[5]._usage = "[filename]";
            optionList[5]._type = CA_ARG_STRING;
            optionList[5]._value = &loadBinary;
            optionList[6]._sVersion = "";
            optionList[6]._lVersion = "flags";
            optionList[6]._description =
                "Specify filename containing the compiler flags to build kernel";
            optionList[6]._usage = "[filename]";
            optionList[6]._type = CA_ARG_STRING;
            optionList[6]._value = &flags;
*/            

	    optionList[4]._sVersion = "p";
            optionList[4]._lVersion = "platformId";
            optionList[4]._description =
                "Select platformId to be used[0 to N-1 where N is number platforms available].";
            optionList[4]._usage = "[value]";
            optionList[4]._type = CA_ARG_INT;
            optionList[4]._value = &platformId;

            optionList[5]._sVersion = "v";
            optionList[5]._lVersion = "version";
            optionList[5]._description = "AMD APP SDK version string.";
            optionList[5]._usage = "";
            optionList[5]._type = CA_NO_ARGUMENT;
            optionList[5]._value = &version;

            optionList[6]._sVersion = "i";
            optionList[6]._lVersion = "iterations";
            optionList[6]._description = "Number of iterations to execute kernel";
            optionList[6]._usage = "";
            optionList[6]._type = CA_ARG_INT;
            optionList[6]._value = &iterations_value;

            optionList[7]._sVersion = "";
            optionList[7]._lVersion = "printKernels";
            optionList[7]._description = "Print all kernels availables";
            optionList[7]._usage = "";
            optionList[7]._type = CA_NO_ARGUMENT;
            optionList[7]._value = &printAvaiKernel;

            optionList[8]._sVersion = "k";
            optionList[8]._lVersion = "kernelId";
            optionList[8]._description = "Select kernelId to be used";
            optionList[8]._usage = "[value]";
            optionList[8]._type = CA_ARG_INT;
            optionList[8]._value = &kernelId;

            optionList[9]._sVersion = "";
            optionList[9]._lVersion = "infoAll";
            optionList[9]._description = "Print informations about OPENCL platforms and devices";
            optionList[9]._usage = "";
            optionList[9]._type = CA_NO_ARGUMENT;
            optionList[9]._value = &printInfoAll;

            if(multiDevice == false)
            {
                optionList[10]._sVersion = "d";
                optionList[10]._lVersion = "deviceId";
                optionList[10]._description =
                    "Select deviceId to be used[0 to N-1 where N is number devices available].";
                optionList[10]._usage = "[value]";
                optionList[10]._type = CA_ARG_INT;
                optionList[10]._value = &deviceId;
            }

            _numArgs = defaultOptions;
            _options = optionList;
            return SDK_SUCCESS;
        }

};

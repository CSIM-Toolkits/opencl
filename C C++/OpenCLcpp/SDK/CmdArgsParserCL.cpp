
/**************************************************************************
* SDKCmdArgsParser                                                          *
* class implements Support for Command Line Options for any sample        *
**************************************************************************/
class CmdArgsParserCL
{
    protected:
        int _numArgs;               /**< number of arguments */
        int _argc;                  /**< number of arguments */
        int _seed;                  /**< seed value */
        char ** _argv;              /**< array of char* holding CmdLine Options */
        Option * _options;          /**< struct option object */
        bool version;               /**< Cmd Line Option- if version */
        bool printAvaiKernel;       /**< Cmd Line Option- if print Kernels availables */
	bool printInfoAll;	    /**< Cmd Line Option- if print all info */
        std::string name;           /**< Name of the Sample */
        sdkVersionStr sdkVerStr;    /**< SDK version string */
    public:
        bool quiet;                 /**< Cmd Line Option- if Quiet */
        int iterations_value;	    /**< Cmd Line Option- if version */
        bool verify;                /**< Cmd Line Option- if verify */
        bool timing;                /**< Cmd Line Option- if Timing */
	std::string sampleVerStr;   /**< Sample version string */

    protected:

        /**
         * usage
         * Displays the various options available for any sample
         */
        void usage()
        {
            std::cout<<"Usage\n";
            help();
        }

        /**
        *******************************************************************
        * @brief Constructor private and cannot be called directly
        ******************************************************************/
        CmdArgsParserCL (void)
        {
            _options = NULL;
            _numArgs = 0;
            _argc = 0;
            _argv = NULL;
            _seed = 123;
            quiet = 0;
            verify = 0;
            timing = 0;
	    iterations_value=1;
        }
    private:

        /**
        *******************************************************************
        * @fn match
        * @param argv array of CMDLine Options
        * @param argc number of CMdLine Options
		* @param totalArgc total number of Original command line Options
		* @param inv_arg pointer to an integer
        * @return SDK_SUCCESS on success, SDK_FAILURE otherwise
        ******************************************************************/
        int match(char ** argv, int argc, int totalArgc, int *inv_arg)
		{
			int matched = 0;
			int shortVer = true;
			char * arg = *argv;
			if(argc > 1)
			{
				if (*arg == '-' && *(arg + 1) == '-')
				{
					shortVer = false;
					arg++;
				}
				else if (*arg != '-')
				{
					if(argc == totalArgc)
						*inv_arg = 0;
					else
						*inv_arg = 1;
					return matched;
				}
			}
			else
			{
				if (*arg == '-' && *(arg + 1) == '-')
				{
					shortVer = false;
					arg++;
				}
				else if(*arg != '-')
				{
					*inv_arg = 1;
					return matched;
				}
			}
			arg++;
			for (int count = 0; count < _numArgs; count++)
			{
				if (shortVer)
				{
					matched = _options[count]._sVersion.compare(arg) == 0 ? 1 : 0;
				}
				else
				{
					matched = _options[count]._lVersion.compare(arg) == 0 ? 1 : 0;
				}
				if (matched == 1)
				{
					int extra_arg = 0;
					if (_options[count]._type == CA_NO_ARGUMENT)
					{
						*((bool *)_options[count]._value) = true;
						if (argc > 1 && *(*(argv + 1)) != '-')
						{
							printf("Invalid Argument for %s\n", argv[0]);
							*inv_arg = 1;
							return SDK_FAILURE;
						}
					}
					else if (_options[count]._type == CA_ARG_FLOAT)
					{

						if (argc > 1)
						{
							if (sscanf(*(argv + 1), "%f", (float *)_options[count]._value) != 1)
							{
								printf("Error :: argument value for %s is not an integer\n", argv[0]);
								*inv_arg = 1;
								return SDK_FAILURE;
							}
							if (argc > 2) {
								if (*(*(argv + 2)) != '-')
								{
									printf("Invalid argument for %s\n", argv[0]);
									*inv_arg = 1;
									return SDK_FAILURE;
								}
							}
							matched++;
						}
						else
						{
							std::cout << "Error. Missing argument for \"" << (*argv) << "\"\n";
							*inv_arg = 1;
							return SDK_FAILURE;
						}
					}
					else if (_options[count]._type == CA_ARG_DOUBLE)
					{
						if (argc > 1)
						{
							if (sscanf(*(argv + 1), "%lf", (double *)_options[count]._value) != 1)
							{
								printf("Error :: argument value for %s is not an integer\n", argv[0]);
								*inv_arg = 1;
								return SDK_FAILURE;
							}
							if (argc > 2) {
								if (*(*(argv + 2)) != '-')
								{
									printf("Invalid argument for %s\n", argv[0]);
									*inv_arg = 1;
									return SDK_FAILURE;
								}
							}
							matched++;
						}
						else
						{
							std::cout << "Error. Missing argument for \"" << (*argv) << "\"\n";
							*inv_arg = 1;
							return SDK_FAILURE;
						}
					}
					else if (_options[count]._type == CA_ARG_INT)
					{
						if (argc > 1)
						{
							if ((sscanf(*(argv + 1), "%d", (int *)_options[count]._value) != 1))
							{
								printf("Error :: argument value for %s is not an integer\n", argv[0]);
								*inv_arg = 1;
								return SDK_FAILURE;
							}
							if (argc > 2) {
								if (*(*(argv + 2)) != '-')
								{
									printf("Invalid argument for %s\n", argv[0]);
									*inv_arg = 1;
									return SDK_FAILURE;
								}
							}
							matched++;
						}
						else
						{
							std::cout << "Error. Missing argument for \"" << (*argv) << "\"\n";
							*inv_arg = 1;
							return SDK_FAILURE;
						}
					}
					else
					{
						if (argc > 1)
						{
							std::string * str = (std::string *)_options[count]._value;
							str->clear();
							str->append(*(argv + 1));
							matched++;
						}
						else
						{
							std::cout << "Error. Missing argument for \"" << (*argv) << "\"\n";
							*inv_arg = 1;
							return SDK_FAILURE;
						}
					}
					*inv_arg = 0;
					break;
				}
			}
			*inv_arg = 0;
			return matched;
		}

    public:

        /**
        *******************************************************************
        * @brief Destructor of SDKCmdArgsParser
        ******************************************************************/
        ~CmdArgsParserCL ()
        {
            if(_options)
            {
                delete[] _options;
            }
        }
        /**
        *******************************************************************
        * @fn AddOption
        * @brief Function to add a new CmdLine Option
        * @param op Option object
        * @return SDK_SUCCESS on success, SDK_FAILURE otherwise
        ******************************************************************/
        int AddOption(Option* op)
        {
            if(!op)
            {
                std::cout<<"Error. Cannot add option, NULL input";
                return -1;
            }
            else
            {
                Option* save = NULL;
                if(_options != NULL)
                {
                    save = _options;
                }
		//cout<<"NumArgs: "<< _numArgs<<endl;
                _options = new Option[_numArgs + 1];
                if(!_options)
                {
                    std::cout<<"Error. Cannot add option ";
                    std::cout<<op->_sVersion<<". Memory allocation error\n";
                    return SDK_FAILURE;
                }
                if(_options != NULL)
                {
                    for(int i=0; i< _numArgs; ++i)
                    {
                        _options[i] = save[i];
                    }
                }
                _options[_numArgs] = *op;
                _numArgs++;
                delete []save;
            }
            return SDK_SUCCESS;
        }

        /**
        *******************************************************************
        * @fn DeleteOption
        * @brief Function to a delete CmdLine Option
        * @param op Option object
        * @return SDK_SUCCESS on success, SDK_FAILURE otherwise
        ******************************************************************/
        int DeleteOption(Option* op)
        {
            if(!op || _numArgs <= 0)
            {
                std::cout<<"Error. Cannot delete option."
                         <<"Null pointer or empty option list\n";
                return SDK_FAILURE;
            }
            for(int i = 0; i < _numArgs; i++)
            {
                if(op->_sVersion == _options[i]._sVersion ||
                        op->_lVersion == _options[i]._lVersion )
                {
                    for(int j = i; j < _numArgs-1; j++)
                    {
                        _options[j] = _options[j+1];
                    }
                    _numArgs--;
                }
            }
            return SDK_SUCCESS;
        }

        /**
        *******************************************************************
        * @fn parse
        * @brief Function to parse the Cmdline Options
        * @param argv array of strings of CmdLine Options
        * @param argc Number of CmdLine Options
        * @return 0 on success Positive if expected and Non-zero on failure
        ******************************************************************/
        int parse(char ** p_argv, int p_argc)
		{
			int matched = 0;
			int argc, totalArgc;
			char **argv;
			int ret = 0;
			_argc = p_argc;
			_argv = p_argv;
			totalArgc = argc = p_argc;
			argv = p_argv;
			if (argc == 1)
			{
				return SDK_FAILURE;
			}
			while (argc > 0)
			{
				int inv_arg = 0;
				matched = match(argv, argc, totalArgc, &inv_arg);
				argc -= (matched > 0 ? matched : 1);
				argv += (matched > 0 ? matched : 1);
				if (inv_arg)
				{
					return 0;
				}

			}
			return matched;
		}

        /**
        *******************************************************************
        * @fn isArgSet
        * @brief Function to check if a argument is set
        * @param arg option string
        * @param shortVer if the option is short version. (Opt param default=false)
        * @return true if success else false
        ******************************************************************/
        bool isArgSet(std::string str, bool shortVer = false)
        {
            bool enabled = false;
            for (int count = 0; count < _argc; count++)
            {
                char * arg = _argv[count];
                if (*arg != '-')
                {
                    continue;
                }
                else if (*arg == '-' && *(arg+1) == '-' && !shortVer)
                {
                    arg++;
                }
                arg++;
                if (str.compare(arg) == 0)
                {
                    enabled = true;
                    break;
                }
            }
            return enabled;
        }

        /**
        *******************************************************************
        * @fn help
        * @brief Function to write help text
        ******************************************************************/
        void help(void)
        {
            std::cout <<  "-h, " << std::left << std::setw(14)
                      << "" "--help" << std::left << std::setw(32) <<" "
                      << "Display this information\n";
            for (int count = 0; count < _numArgs; count++)
            {
                if (_options[count]._sVersion.length() > 0)
                {
                    std::cout<< std::left << std::setw(4) <<  "-" + _options[count]._sVersion +
                             ", ";
                }
                else
                {
                    std::cout << "    ";
                }
                std::cout<< std::left<< std::setw(14) <<  "--" + _options[count]._lVersion;
                if(!_options[count]._usage.empty())
                {
                    std::cout <<std::left <<std::setw(32) << _options[count]._usage ;
                }
                else
                {
                    std::cout <<std::left <<std::setw(32) << "";
                }
                std::cout<< _options[count]._description + "\n";
            }
        }
        /**
        * parseCommandLine
        * parses the command line options given by user
        * @param argc Number of elements in cmd line input
        * @param argv array of char* storing the CmdLine Options
        * @return 0 on success Positive if expected and Non-zero on failure
        */
        virtual int parseCommandLine(int argc, char **argv) = 0;
};

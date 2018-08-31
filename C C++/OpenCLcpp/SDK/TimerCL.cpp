
/**
 * Timer
 * struct to handle time measuring functionality
 */
class TimerCL
{
    private:

        struct Timer
        {
            std::string name;   /**< name name of time object*/
            long long _freq;    /**< _freq frequency*/
            double _clocks;  /**< _clocks number of ticks at end*/
            double _start;   /**< _start start point ticks*/
        };

        std::vector<Timer*> _timers;      /**< _timers vector to Timer objects */
        

    public :
        double totalTime;                 /** total time taken */
        /**
         * Constructor
         */
        TimerCL()
        {
        }

        /**
         * Destructor
         */
        ~TimerCL()
        {
            while(!_timers.empty())
            {
                Timer *temp = _timers.back();
                _timers.pop_back();
                delete temp;
            }
        }

        /**
        * CreateTimer
        */
        int createTimer()
        {
            Timer* newTimer = new Timer;
            newTimer->_start = 0;
            newTimer->_clocks = 0;
	    #ifdef _WIN32
             QueryPerformanceFrequency((LARGE_INTEGER*)&newTimer->_freq);
	    #else
             newTimer->_freq = (long long)1.0E3;
	    #endif
            /* Push back the address of new Timer instance created */
            _timers.push_back(newTimer);
            return (int)(_timers.size() - 1);
        }

        /**
        * resetTimer
        */
        int resetTimer(int handle)
        {
            if(handle >= (int)_timers.size())
            {
                error("Cannot reset timer. Invalid handle.");
                return -1;
            }
            (_timers[handle]->_start) = 0;
            (_timers[handle]->_clocks) = 0;
            return SDK_SUCCESS;
        }
        /**
        * startTimer
        */
        int startTimer(int handle)
        {
            if(handle >= (int)_timers.size())
            {
                error("Cannot reset timer. Invalid handle.");
                return SDK_FAILURE;
            }
#ifdef _WIN32
			long long tmpStart;
			QueryPerformanceCounter((LARGE_INTEGER*)&(tmpStart));
			_timers[handle]->_start = (double)tmpStart;
#else
            struct timeval s;
            gettimeofday(&s, 0);
            _timers[handle]->_start = s.tv_sec * 1.0E3 + ((double)(s.tv_usec / 1.0E3));
#endif
            return SDK_SUCCESS;
        }

        /**
        * stopTimer
        */
        int stopTimer(int handle)
        {
            double n=0;
            if(handle >= (int)_timers.size())
            {
                error("Cannot reset timer. Invalid handle.");
                return SDK_FAILURE;
            }
#ifdef _WIN32
			long long n1;
            QueryPerformanceCounter((LARGE_INTEGER*)&(n1));
			n = (double) n1;
#else
            struct timeval s;
            gettimeofday(&s, 0);
            n = s.tv_sec * 1.0E3+ (double)(s.tv_usec/1.0E3);
#endif
            n -= _timers[handle]->_start;
            _timers[handle]->_start = 0;
            _timers[handle]->_clocks += n;
            return SDK_SUCCESS;
        }

        /**
        * readTimer
        */
        double readTimer(int handle)
        {
            if(handle >= (int)_timers.size())
            {
                error("Cannot read timer. Invalid handle.");
                return SDK_FAILURE;
            }
            double reading = double(_timers[handle]->_clocks);
            reading = double(reading / _timers[handle]->_freq);
            return reading;
        }


};


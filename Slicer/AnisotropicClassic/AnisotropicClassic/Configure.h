
#pragma once


using namespace std;


#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#define SDK_VERSION "AMD-APP-SDK-v2.9-1.599.1"

#define SAMPLE_VERSION "APP-USP-DCM-1.0.0"

#define __CL_ENABLE_EXCEPTIONS


#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/cl.hpp>
#endif


/******************************************************************************
* Included header files                                                       *
******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <malloc.h>
#include <math.h>
#include <numeric>
#include <stdint.h>
#include <algorithm>
#include <dirent.h>




#if defined(__MINGW32__) && !defined(__MINGW64_VERSION_MAJOR)
#define _aligned_malloc __mingw_aligned_malloc
#define _aligned_free  __mingw_aligned_free
#endif // __MINGW32__  and __MINGW64_VERSION_MAJOR


#ifndef _WIN32
#if defined(__INTEL_COMPILER)
#pragma warning(disable : 1125)
#endif
#endif

#ifdef _WIN32 
#include <windows.h>
#include <direct.h>
#else
#include <sys/time.h>
#include <linux/limits.h>
#include <unistd.h>
#endif





/******************************************************************************
* Defined macros                                                              *
******************************************************************************/
#define SDK_SUCCESS 0
#define SDK_FAILURE 1
#define SDK_EXPECTED_FAILURE 2

#define SDK_VERSION_MAJOR 2
#define SDK_VERSION_MINOR 9
#define SDK_VERSION_SUB_MINOR 1
#define SDK_VERSION_BUILD 1
#define SDK_VERSION_REVISION 1

#define DEBUG(name) printer(#name, (name))


#define CHECK_OPENCL_ERROR(actual, msg) \
    if(checkVal(actual, CL_SUCCESS, msg)) \
{ \
    std::cout << "Location : " << __FILE__ << ":" << __LINE__<< std::endl; \
    return SDK_FAILURE; \
    }

#define CHECK_ALLOCATION(actual, msg) \
    if(actual == NULL) \
{ \
    error(msg); \
    std::cout << "Location : " << __FILE__ << ":" << __LINE__<< std::endl; \
    return SDK_FAILURE; \
    }

#define CHECK_ERROR(actual, reference, msg) \
    if(actual != reference) \
{ \
    error(msg); \
    std::cout << "Location : " << __FILE__ << ":" << __LINE__<< std::endl; \
    return SDK_FAILURE; \
    }

#define FREE(ptr) \
{ \
    if(ptr != NULL) \
{ \
    free(ptr); \
    ptr = NULL; \
    } \
    }

#ifdef _WIN32
#define ALIGNED_FREE(ptr) \
{ \
    if(ptr != NULL) \
{ \
    _aligned_free(ptr); \
    ptr = NULL; \
    } \
    }
#endif




#define UNUSED(expr) (void)(expr);


/**
 * GLOBAL DEFINED Macros
 */
#define CL_CONTEXT_OFFLINE_DEVICES_AMD        0x403F


/******************************************************************************
* Included SDK files                                                       *
******************************************************************************/
#include "UtilCL.h"
#include "LogCL.cpp"






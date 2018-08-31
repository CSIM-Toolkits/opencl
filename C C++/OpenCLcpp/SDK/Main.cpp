

#define DEBUG
#define IMAGE_FORMAT_2D
#define INPUT_IMAGE "FilterImage_Input.bmp"
#define GROUP_SIZE 256

#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;

#include "SDKOpencl.cpp"



int main(int argc, char * argv[])
{


	SDKOpencl sdk;


	if( sdk.initialize()!= SDK_SUCCESS)
	{
		return SDK_FAILURE;
	}


	if(sdk.sampleArgs->parseCommandLine(argc, argv))
	{
		return SDK_FAILURE;
	}

	if(sdk.setupCL(std::string(INPUT_IMAGE))!=SDK_SUCCESS){
		return SDK_FAILURE;
	}
	


	sdk.finalize();

}




#include "itkImageFileWriter.h"

#include "itkCastImageFilter.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"

#include "itkPluginUtilities.h"

#include "itkImportImageFilter.h"

#include "AnisotropicClassicCLP.h"

#include "itkQualityImageFilter.h"

#include "Configure.h"

namespace
{


/************ OPENCL OBJECTS ************/
cl::Context context;                           /* OPENCL context */
std::vector<cl::Device> devices;               /* OPENCL device list */
std::vector<cl::Platform> platforms;           /* OPENCL list of platforms */


cl::CommandQueue commandQueue;                 /* OPENCL command queue */
cl::Program program;                           /* OPENCL program  */
cl::Kernel kernel;                             /* OPENCL kernel */
cl_uint width;                                 /* OPENCL image width */
cl_uint height;                                /* OPENCL image height */
cl_uint deep;                                  /* OPENCL image deep */
size_t blockSizeX;                             /* OPENCL work-group size in x-direction */
size_t blockSizeY;                             /* OPENCL work-group size in y-direction */
size_t blockSizeZ;                             /* OPENCL work-group size in z-direction */
cl_int eventStatus = CL_QUEUED;                /* OPENCL event status */
cl_int err = CL_SUCCESS;                       /* OPENCL status opencl errors*/
cl_device_type dType;                          /* OPENCL type of device (CPU | GPU | ALL)*/
cl::Event Event;                               /* OPENCL event object */
cl::Buffer inputImage2D;                       /* OPENCL buffer for input 3dimage */
cl::Buffer outputImage2D;                      /* OPENCL buffer for output 3dimage */


/************ AUXILIARY OBJECTS ************/
std::vector<BufferObj> vectorBuffer;           /* Vector of all buffers*/
std::vector<BuildOption> vectOption;           /* Vector of all build options*/
std::string stringBuildOptions;                /* String build options for kernel compilation */

float* pixelData;       		               /* Pointer to input image data */
float* pixelDataOut;                           /* Pointer to output image data */
int sizePixel;                                 /* Total size of image*/

float kappa;                                   /* AnisotropicClassic coeficient kappa*/
float delta;                                   /* AnisotropicClassic coeficient delta or time step*/
int numIterations;                             /* AnisotropicClassic number of iterations*/

int dr; float dd; float auxEven; float auxOdd; /* AnisotropicClassic auxiliary variables*/

float sumTotalExec;                            /* AnisotropicClassic run time in seconds*/


/************ VARIABLES FOR PROCEDURAL ALGORITHM ************/
float* GradNData;
float* GradNLData;
float* GradLData;
float* GradSLData;
float* GradSData;
float* GradSOData;
float* GradOData;
float* GradNOData;

float* fPerona0Data;
float* fPerona1Data;
float* fPerona2Data;
float* fPerona3Data;
float* fPerona4Data;
float* fPerona5Data;
float* fPerona6Data;
float* fPerona7Data;



/************ ITK OBJECTS ************/
typedef itk::Image<float, 3> ImageType;
typedef itk::Image<short, 3> OutPutImageType;
typedef itk::ImageFileReader< ImageType>  ReaderType;
typedef itk::ImageFileWriter< OutPutImageType>  WriterType;



/* GradientAnisotropicDiffusionImageFilter output pixel type MUST be float or double
 * to prevent computational errors */
typedef itk::GradientAnisotropicDiffusionImageFilter<ImageType,ImageType > FilterType;
FilterType::Pointer filter;

/* CastImageFilter converts image to short */
typedef itk::CastImageFilter<ImageType, OutPutImageType >  CastFilterType;
CastFilterType::Pointer castFilter;

/* ImportImageFilter import the GPU output image buffer */
typedef itk::ImportImageFilter<float, 3>   ImportFilterType;
ImportFilterType::Pointer importFilter;

/* QualityImageFilter calculate signal-to-noise ratio (SNR) */
typedef itk::QualityImageFilter<ImageType> SNRFilterType;
SNRFilterType::Pointer SNRfilter = SNRFilterType::New();

typename ReaderType::Pointer reader;
typename WriterType::Pointer writer;
typename ImageType::Pointer image;
typename ImageType::RegionType region;
typename ImageType::SizeType size;
typename ImageType::SpacingType pxSpace;

itk::TimeProbe cputimer;                       /* ITK timer for cpu execution*/
itk::TimeProbe gputimer;                       /* ITK timer for gpu execution*/

/*********** OPENCL METHODS *************/
void Init(){


    blockSizeX=8;
    blockSizeY=8;
    blockSizeZ = 4;
    stringBuildOptions="";
    //dType = CL_DEVICE_TYPE_GPU;   /*ON GPU*/
    dType = CL_DEVICE_TYPE_ALL;   /*ALL DEVICES*/

    dr=1;
    dd= pow(2, 1.0/2.0);

    sumTotalExec = 0.0;

#ifdef VERBOSE

    DEBUG(dr);
    DEBUG(dd);

#endif

    vectOption.clear();
    vectorBuffer.clear();

    importFilter = ImportFilterType::New();
    castFilter = CastFilterType::New();
    filter = FilterType::New();
    reader = ReaderType::New();
    writer = WriterType::New();


}


int Allocate(std::string inputVolume){


    reader->SetFileName( inputVolume.c_str() );
    reader->Update();

    image = reader->GetOutput();

    region = image->GetLargestPossibleRegion();

    size = region.GetSize();

    pxSpace = image->GetSpacing();

    auxEven = delta * (1 / pow(dr, 2));
    auxOdd = delta * (1 / pow(dd, 2));


#ifdef VERBOSE


    DEBUG(auxEven);
    DEBUG(auxOdd);
    DEBUG((int)size[0]);
    DEBUG((int)size[1]);
    DEBUG((int)size[2]);
    DEBUG((int)pxSpace[0]);
    DEBUG((int)pxSpace[1]);
    DEBUG((int)pxSpace[2]);
    //std::cout << reader<< std::endl;
    //std::cout << image<< std::endl;

#endif

    width = size[0];
    height= size[1];
    deep = size[2];


    /*alocate and fill buffer input image data*/
    pixelData  = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    memcpy(pixelData, image->GetBufferPointer(), size[0]*size[1]*size[2]*sizeof(float));
    CHECK_ALLOCATION(pixelData,"Error: Alocate() - Failed to allocate memory! (outputImageData)");

    /*alocate buffer ouput image data*/
    pixelDataOut = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(pixelDataOut,"Error: Alocate() - Failed to allocate memory! (outputImageData)");

    // initialize the buffer OutPut Image to NULL
    memcpy(pixelDataOut, pixelData, width * height * deep * sizeof(float));

    /*gradient objects allocate*/
    GradNData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradNData,"Error: Alocate() - Failed to allocate memory! (GradNData)");

    GradNLData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradNLData,"Error: Alocate() - Failed to allocate memory! (GradNLData)");

    GradLData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradLData,"Error: Alocate() - Failed to allocate memory! (GradLData)");

    GradSLData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradSLData,"Error: Alocate() - Failed to allocate memory! (GradSLData)");

    GradSData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradSData,"Error: Alocate() - Failed to allocate memory! (GradSData)");

    GradSOData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradSOData,"Error: Alocate() - Failed to allocate memory! (GradSOData)");

    GradOData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradOData,"Error: Alocate() - Failed to allocate memory! (GradOData)");

    GradNOData = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(GradNOData,"Error: Alocate() - Failed to allocate memory! (GradNOData)");

    fPerona0Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona0Data,"Error: Alocate() - Failed to allocate memory! (fPerona0Data)");

    fPerona1Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona1Data,"Error: Alocate() - Failed to allocate memory! (fPerona1Data)");

    fPerona2Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona2Data,"Error: Alocate() - Failed to allocate memory! (fPerona2Data)");

    fPerona3Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona3Data,"Error: Alocate() - Failed to allocate memory! (fPerona3Data)");

    fPerona4Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona4Data,"Error: Alocate() - Failed to allocate memory! (fPerona4Data)");

    fPerona5Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona5Data,"Error: Alocate() - Failed to allocate memory! (fPerona5Data)");

    fPerona6Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona6Data,"Error: Alocate() - Failed to allocate memory! (fPerona6Data)");

    fPerona7Data = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(fPerona7Data,"Error: Alocate() - Failed to allocate memory! (fPerona7Data)");


    /*gradient objects*/
    // initialize the Gradiate Objects OutPut to NULL
    memset(GradNData, 0, width * height * deep * sizeof(float));
    memset(GradNLData, 0, width * height * deep * sizeof(float));
    memset(GradLData, 0, width * height * deep * sizeof(float));
    memset(GradSLData, 0, width * height * deep * sizeof(float));
    memset(GradSData, 0, width * height * deep * sizeof(float));
    memset(GradSOData, 0, width * height * deep * sizeof(float));
    memset(GradOData, 0, width * height * deep * sizeof(float));
    memset(GradNOData, 0, width * height * deep * sizeof(float));

    memset(fPerona0Data, 0, width * height * deep * sizeof(float));
    memset(fPerona1Data, 0, width * height * deep * sizeof(float));
    memset(fPerona2Data, 0, width * height * deep * sizeof(float));
    memset(fPerona3Data, 0, width * height * deep * sizeof(float));
    memset(fPerona4Data, 0, width * height * deep * sizeof(float));
    memset(fPerona5Data, 0, width * height * deep * sizeof(float));
    memset(fPerona6Data, 0, width * height * deep * sizeof(float));
    memset(fPerona7Data, 0, width * height * deep * sizeof(float));



    sizePixel = (size[0]*size[1]*size[2]);


    BuildOption widthOption;
    widthOption.name = "width";
    widthOption.value = &width;
    widthOption.type = TYPE_INT;
    vectOption.push_back(widthOption);

    BuildOption heightOption;
    heightOption.name = "height";
    heightOption.value = &height;
    heightOption.type = TYPE_INT;
    vectOption.push_back(heightOption);

    BuildOption deepOption;
    deepOption.name = "deep";
    deepOption.value = &deep;
    deepOption.type = TYPE_INT;
    vectOption.push_back(deepOption);

    stringBuildOptions = CreateStringBuildOptions(vectOption);


    return SDK_SUCCESS;

}



int GetPlataformsAndDevices(){

    int deviceCount = 0;

    /*Get plataforms installed in PC*/
    err = cl::Platform::get(&platforms);
    CHECK_OPENCL_ERROR(err, "Platform::get() failed.");

    std::vector<cl::Platform>::iterator i;

#ifdef VERBOSE
    DEBUG((int)platforms.size());
    //std::cout<<"Plataform size: "<< platforms.size()<<std::endl;
#endif

    if(platforms.size() > 0)
    {
        i = platforms.begin() + 0;

    }


    cl_context_properties cps[3] =
    {
        CL_CONTEXT_PLATFORM,(cl_context_properties)(*i)(),0
    };

    /*Create Context */
    context = cl::Context(dType, cps, NULL, NULL, &err);
    CHECK_OPENCL_ERROR(err, "Context::Context() failed.");



    /*Get devices informations*/
    devices = context.getInfo<CL_CONTEXT_DEVICES>(&err);
    CHECK_OPENCL_ERROR(err, "Context::getInfo() failed.");

    deviceCount = (int)devices.size();

#ifdef VERBOSE
    //std::cout << "Platform :" << (*i).getInfo<CL_PLATFORM_VENDOR>().c_str() << "\n";

    int j = 0;
    for (std::vector<cl::Device>::iterator i = devices.begin(); i != devices.end();
         ++i, ++j)
    {
        std::cout << "Device " << j << " : ";
        std::string deviceName = (*i).getInfo<CL_DEVICE_NAME>();
        std::cout << deviceName.c_str() << "\n";
    }
    std::cout << "\n";
#endif
    if (deviceCount == 0)
    {
        std::cout << "No device available\n";
        return SDK_FAILURE;
    }

    return SDK_SUCCESS;
}


int CommandQueue(cl::Device device){

    commandQueue = cl::CommandQueue(context, device, 0,&err);
    CHECK_OPENCL_ERROR(err, "CommandQueue::CommandQueue() failed.");

    return SDK_SUCCESS;

}


int CreateInputAndOuputBufferImage(){

    vectorBuffer.clear();

    /* Create and initialize input buffer image*/
    inputImage2D = cl::Buffer(context,
                              CL_MEM_READ_ONLY,
                              sizeof(float) * width * height* deep ,
                              NULL,
                              &err);


    CHECK_OPENCL_ERROR(err, "cl::Buffer::cl::Buffer() failed. (inputImage2D)");

    /* Create and initialize outinput buffer image*/
    outputImage2D = cl::Buffer(context,
                               CL_MEM_WRITE_ONLY,
                               sizeof(float)* width * height* deep ,
                               NULL,
                               &err);
    CHECK_OPENCL_ERROR(err, "cl::Buffer::cl::Buffer() failed. (outputImage2D)");


    BufferObj imageInputBuffer;
    imageInputBuffer.buffer = inputImage2D;
    imageInputBuffer.data = pixelData;
    imageInputBuffer.size = sizeof(float) * width * height* deep;
    imageInputBuffer.type = TYPE_INBUFFER;

    BufferObj imageOutputBuffer;
    imageOutputBuffer.buffer = outputImage2D;
    imageOutputBuffer.data = pixelDataOut;
    imageOutputBuffer.size = sizeof(float) * width * height* deep;
    imageOutputBuffer.type = TYPE_OUTBUFFER;

    BufferObj CoefKappa;
    CoefKappa.buffer = NULL;
    CoefKappa.dataFLOAT = kappa;
    CoefKappa.size = sizeof(float);
    CoefKappa.type = TYPE_FLOAT;

    BufferObj AuxEven;
    AuxEven.buffer = NULL;
    AuxEven.dataFLOAT = auxEven;
    AuxEven.size = sizeof(float);
    AuxEven.type = TYPE_FLOAT;

    BufferObj AuxOdd;
    AuxOdd.buffer = NULL;
    AuxOdd.dataFLOAT = auxOdd;
    AuxOdd.size = sizeof(float);
    AuxOdd.type = TYPE_FLOAT;


    vectorBuffer.push_back(imageInputBuffer);
    vectorBuffer.push_back(imageOutputBuffer);

    vectorBuffer.push_back(CoefKappa);
    vectorBuffer.push_back(AuxEven);
    vectorBuffer.push_back(AuxOdd);


    return SDK_SUCCESS;

}


int FillBuffers(std::vector<BufferObj> vect){

    std::vector<BufferObj>::iterator i;
    int j = 0;
#ifdef VERBOSE
    //DEBUG((int)vect.size());
    std::cout << "FillBuffers Size: " << vect.size()<<std::endl;
#endif

    for (i = vect.begin(); i < vect.end(); ++i, ++j)
    {

        if((*i).type == TYPE_INBUFFER ){

            err = commandQueue.enqueueWriteBuffer(
                        (*i).buffer,
                        CL_TRUE,
                        0,
                        (*i).size,
                        (*i).data,
                        NULL,
                        &Event);
            CHECK_OPENCL_ERROR(err,"CommandQueue::enqueueWriteImage failed.");

            eventStatus = CL_QUEUED;
            while(eventStatus != CL_COMPLETE)
            {
                err = Event.getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS,&eventStatus);
                CHECK_OPENCL_ERROR(err,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
            }
        }


    }


    return SDK_SUCCESS;
}


int LoadKernelAndCompile(std::string fullPath,std::string kernelName){

    // create a CL program using the kernel source
    SDKFile kernelFile;
    //std::string kernelPath = getPath();

    //kernelPath.append(fileName);
    if(!kernelFile.open(fullPath.c_str()))
    {
        std::cout << "Failed to load kernel file : " << fullPath << std::endl;
        return SDK_FAILURE;
    }

    // create program source
    cl::Program::Sources programSource(1,std::make_pair(kernelFile.source().data(),kernelFile.source().size()));

    // Create program object
    program = cl::Program(context, programSource, &err);
    CHECK_OPENCL_ERROR(err, "Program::Program() failed.");

    err = program.build(devices, stringBuildOptions.c_str());

    if(err != CL_SUCCESS)
    {
        if(err == CL_BUILD_PROGRAM_FAILURE)
        {
            std::string str = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]);

            std::cout << " \n\t\t\tBUILD LOG\n";
            std::cout << " ************************************************\n";
            std::cout << str << std::endl;
            std::cout << " ************************************************\n";
        }
    }
    CHECK_OPENCL_ERROR(err, "Program::build() failed.");

    // Create kernel
    kernel = cl::Kernel(program, kernelName.c_str(),  &err);
    CHECK_OPENCL_ERROR(err, "Kernel::Kernel() failed.");

    // Check group size against group size returned by kernel
    size_t kernelWorkGroupSize = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(devices[0], &err);
    CHECK_OPENCL_ERROR(err, "Kernel::getWorkGroupInfo()  failed.");
#ifdef VERBOSE
    DEBUG((int)kernelWorkGroupSize);
    //std::cout<<"DEVICE WORKGROUP SIZE: " << kernelWorkGroupSize << std::endl;
#endif
    if((blockSizeX * blockSizeY) > kernelWorkGroupSize)
    {

        std::cout << "Out of Resources!" << std::endl;
        std::cout << "Group Size specified : "<< blockSizeX * blockSizeY << std::endl;
        std::cout << "Max Group Size supported on the kernel : "<< kernelWorkGroupSize << std::endl;
        std::cout << "Falling back to " << kernelWorkGroupSize << std::endl;


        if(blockSizeX > kernelWorkGroupSize)
        {
            blockSizeX = kernelWorkGroupSize;
            blockSizeY = 1;
        }
    }
    return SDK_SUCCESS;

}
int setArgBuffer(std::vector<BufferObj> vect){


    // Set appropriate arguments to the kernel
    std::vector<BufferObj>::iterator i;
    int j = 0;
#ifdef VERBOSE
    //DEBUG((int)vect.size());
    std::cout << "setArgBuffer Size: " << vect.size()<<std::endl;
#endif

    for (i = vect.begin(); i < vect.end(); ++i, ++j)
    {
        if((*i).type == TYPE_INBUFFER || (*i).type == TYPE_OUTBUFFER ){
            err = kernel.setArg(j, (*i).buffer);
            CHECK_OPENCL_ERROR(err, "Kernel::setArgBUFFER() failed.");
        }else if ((*i).type == TYPE_INT ){

            intptr_t ValueDim = (intptr_t)((*i).dataINT);

            err = kernel.setArg(j, (int)ValueDim);
            CHECK_OPENCL_ERROR(err, "Kernel::setArgINT() failed.");
        }else if ((*i).type == TYPE_FLOAT ){

            float ValueDim = (float)((*i).dataFLOAT);

            err = kernel.setArg(j, (float)ValueDim);
            CHECK_OPENCL_ERROR(err, "Kernel::setArgFLOAT() failed.");
        }

    }


    return SDK_SUCCESS;

}


int runCL(){

    /*
    * Enqueue a kernel run call.
    */

    cl::NDRange offset(0,0,0);
    cl::NDRange globalThreads(width,height,deep);
    cl::NDRange localThreads(blockSizeX,blockSizeY,blockSizeZ);


    err = commandQueue.enqueueNDRangeKernel(
                kernel,
                offset,
                globalThreads,
                localThreads,
                0,
                &Event);
    CHECK_OPENCL_ERROR(err, "CommandQueue::enqueueNDRangeKernel() failed.");

#ifdef VERBOSE
    message("Running Kernel...");
#endif
    err = commandQueue.flush();
    CHECK_OPENCL_ERROR(err, "cl::CommandQueue.flush failed.");
    eventStatus = CL_QUEUED;
    while(eventStatus != CL_COMPLETE)
    {
        err = Event.getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS,&eventStatus);
        CHECK_OPENCL_ERROR(err,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
    }

    return SDK_SUCCESS;

}


int readBufferOutput(std::vector<BufferObj> vect){

    std::vector<BufferObj>::iterator i;
    int j = 0;
#ifdef VERBOSE
    std::cout << "readBufferGradientsOutput Size: " << vect.size()<<std::endl;
#endif

    for (i = vect.begin(); i < vect.end(); ++i, ++j)
    {

        if((*i).type == TYPE_OUTBUFFER ){

            // Enqueue readBuffer
            err = commandQueue.enqueueReadBuffer(
                        (*i).buffer,
                        CL_FALSE,
                        0,
                        (*i).size,
                        (*i).data,
                        NULL,
                        &Event);
            CHECK_OPENCL_ERROR(err, "CommandQueue::enqueueReadImage failed.");


            eventStatus = CL_QUEUED;
            while(eventStatus != CL_COMPLETE)
            {
                err = Event.getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS,&eventStatus);
                CHECK_OPENCL_ERROR(err,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");

            }
        }


    }

    return SDK_SUCCESS;


}

int writeOutputImage(std::string outputVolume){


    ImportFilterType::SizeType  sizeImport;
    sizeImport[0]  = width;  // size along X
    sizeImport[1]  = height;  // size along Y
    sizeImport[2]  = deep;  // size along Y
    ImportFilterType::IndexType start;
    start.Fill( 0 );
    ImportFilterType::RegionType regionImport;
    regionImport.SetIndex( start );
    regionImport.SetSize(  sizeImport  );

    importFilter->SetRegion( regionImport );


    const itk::SpacePrecisionType origin[ 3 ] = { 0.0, 0.0, 0.0};
    importFilter->SetOrigin( origin );

    //const itk::SpacePrecisionType  spacing[ 3 ] =  { 1.0, 1.0, 2};
    importFilter->SetSpacing( pxSpace );

    const bool importImageFilterWillOwnTheBuffer = true;
    importFilter->SetImportPointer( pixelDataOut, sizePixel,
                                    importImageFilterWillOwnTheBuffer );

    importFilter->Update();
    castFilter->SetInput(importFilter->GetOutput() );
    castFilter->Update();

    writer->SetFileName( outputVolume.c_str() );
    writer->SetInput(  castFilter->GetOutput()  );


    //    SNRfilter->SetReferenceImage(image);
    //    SNRfilter->SetCompareImage(importFilter->GetOutput());

    //    std::cout<<SNRfilter->SNR()<<std::endl;

    writer->SetUseCompression(1);


    return SDK_SUCCESS;
}


/***********DO IT*************/
template <class T>
int DoIt( int argc, char * argv[], T )
{
    PARSE_ARGS;


    Init();

#ifdef VERBOSE
    DEBUG(numInterationInput);
    DEBUG(kappaInput);
    DEBUG(deltaInput);
#endif

    numIterations = numInterationInput;
    kappa = kappaInput;
    delta = deltaInput;


    if(Allocate(inputVolume)!= SDK_SUCCESS){
        return SDK_FAILURE;
    }


    if(deviceType.compare("GPU")==0){


#ifdef VERBOSE
        message("GPU PROCESSING GRADIENTS...");
#endif
        if(GetPlataformsAndDevices()!= SDK_SUCCESS){
            return SDK_FAILURE;
        }


        if(CommandQueue(devices[0])!= SDK_SUCCESS){
            return SDK_FAILURE;
        }

        if(CreateInputAndOuputBufferImage()!= SDK_SUCCESS){
            return SDK_FAILURE;
        }

        if(FillBuffers(vectorBuffer)!= SDK_SUCCESS){
            return SDK_FAILURE;
        }



        for(int interations=0; interations < numIterations;interations++){

#ifdef VERBOSE
            DEBUG(interations);
#endif

            gputimer.Reset();
            gputimer.Start();

            //Second execution
            if(LoadKernelAndCompile("/home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/AnisotropicClassic/Anisotropic.cl","AnisotropicClassic2")!= SDK_SUCCESS){
                return SDK_FAILURE;
            }


            if(setArgBuffer(vectorBuffer)!= SDK_SUCCESS){
                return SDK_FAILURE;
            }

            if(runCL()!= SDK_SUCCESS){
                return SDK_FAILURE;
            }


            //Get Image output result
            if(readBufferOutput(vectorBuffer)!= SDK_SUCCESS){
                return SDK_FAILURE;
            }


            err = commandQueue.enqueueWriteBuffer(
                        vectorBuffer.at(0).buffer,
                        CL_TRUE,
                        0,
                        vectorBuffer.at(0).size,
                        pixelDataOut,
                        NULL,
                        &Event);
            CHECK_OPENCL_ERROR(err,"CommandQueue::enqueueWriteImage failed.");

            eventStatus = CL_QUEUED;
            while(eventStatus != CL_COMPLETE)
            {
                err = Event.getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS,&eventStatus);
                CHECK_OPENCL_ERROR(err,"cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
            }

            gputimer.Stop();

            sumTotalExec = sumTotalExec + gputimer.GetTotal();


        }

#ifdef VERBOSE
        std::cout << "GPU Filter  took " << sumTotalExec << " seconds with\n";
#endif

        if(writeOutputImage(outputVolume)!= SDK_SUCCESS){
            return SDK_FAILURE;
        }

        try
        {
            writer->Update();

            /*CALCULATE SNR*/
            SNRfilter->SetReferenceImage(image);
            SNRfilter->SetCompareImage(importFilter->GetOutput());
            std::cout<<"SNR VALUE: "<<SNRfilter->SNR()<<std::endl;


        }
        catch( itk::ExceptionObject & exp )
        {
            std::cerr << "Exception caught !" << std::endl;
            std::cerr << exp << std::endl;
            return EXIT_FAILURE;
        }


    }else if (deviceType.compare("CPU ITK")==0){
#ifdef VERBOSE
        message("CPU PROCESSING...");
#endif


        cputimer.Reset();
        cputimer.Start();

        filter->SetInput( image );
        filter->SetNumberOfIterations( numIterations );
        filter->SetTimeStep( deltaInput );
        filter->SetConductanceParameter( kappa );
        //filter->SetFixedAverageGradientMagnitude(0);

        castFilter= CastFilterType::New();
        castFilter->SetInput(filter->GetOutput());

        cputimer.Stop();
        std::cout << "CPU ITK Anisotropic filter took " << cputimer.GetTotal() << " seconds with\n" << std::endl;

        writer->SetFileName( outputVolume.c_str() );
        writer->SetInput( castFilter->GetOutput() );
        writer->SetUseCompression(1);



        try
        {
            writer->Update();


            /*CALCULATE SNR*/
            SNRfilter->SetReferenceImage(image);
            SNRfilter->SetCompareImage(filter->GetOutput());
            std::cout<<"SNR VALUE: "<<SNRfilter->SNR()<<std::endl;


        }
        catch( itk::ExceptionObject & exp )
        {
            std::cerr << "Exception caught !" << std::endl;
            std::cerr << exp << std::endl;
            return EXIT_FAILURE;
        }


    }else if (deviceType.compare("CPU PROCEDURAL")==0){
#ifdef VERBOSE
        message("CPU PROCESSING...");
#endif


        cputimer.Reset();
        cputimer.Start();

        for(int interations=0; interations < numIterations;interations++){

            for(int giz=0; giz<deep; giz++){
                for(int giy=0; giy<height; giy++){
                    for(int gix=0; gix<width; gix++){


                        int index = width*(giz*height + giy) + gix;


                        bool isValid = true;
                        if(gix < 0 || gix >= width) isValid = false;
                        if(giy < 0 || giy >= height) isValid = false;
                        if(giz < 0 || giz >= deep) isValid = false;


                        if( isValid )
                        {

                            //do gradient north
                            if((index-(int)width)<=0){
                                GradNData[index] = 0.0;
                            }else{

                                int auxInt = index - (int)width;
                                GradNData[index] =  pixelData[auxInt] - pixelData[index];
                            }

                            //do gradient south
                            if((index+ (int)width)> ((int)width*(int)height)){
                                GradSData[index] = 0;
                            }else{
                                int auxInt = index + (int)width;
                                GradSData[index] =  pixelData[auxInt] - pixelData[index];
                            }

                            //do gradiente east and west
                            GradLData[index] =  pixelData[index + 1] - pixelData[index];
                            GradOData[index] =  pixelData[index - 1] - pixelData[index];

                            //do gradient northeast
                            if((index - (int)width + 1)<0){
                                GradNLData[index] = 0;
                            }else{

                                int auxInt = index - (int)width + 1;
                                GradNLData[index] =  pixelData[auxInt] - pixelData[index];
                            }

                            //do gradient northwest
                            if((index - (int)width - 1)<0){
                                GradNOData[index] = 0;
                            }else{
                                int auxInt = index - (int)width - 1;
                                GradNOData[index] =  pixelData[auxInt] - pixelData[index];
                            }


                            //do gradient southeast
                            if((index + (int)width + 1)> ((int)width*(int)height)){
                                GradSLData[index] = 0;
                            }else{
                                int auxInt = index + (int)width + 1;
                                GradSLData[index] =  pixelData[auxInt] - pixelData[index];
                            }

                            //do gradient south-west
                            if((index + (int)width - 1)> ((int)width*(int)height)){
                                GradSOData[index] = 0;
                            }else{
                                int auxInt = index + (int)width - 1;
                                GradSOData[index] =  pixelData[auxInt] - pixelData[index];
                            }

                            fPerona0Data[index] = exp(-pow((float)(GradNData[index]/kappa),2));
                            fPerona1Data[index] = exp(-pow((float)(GradNLData[index]/kappa),2));
                            fPerona2Data[index] = exp(-pow((float)(GradLData[index]/kappa),2));
                            fPerona3Data[index] = exp(-pow((float)(GradSLData[index]/kappa),2));
                            fPerona4Data[index] = exp(-pow((float)(GradSData[index]/kappa),2));
                            fPerona5Data[index] = exp(-pow((float)(GradSOData[index]/kappa),2));
                            fPerona6Data[index] = exp(-pow((float)(GradOData[index]/kappa),2));
                            fPerona7Data[index] = exp(-pow((float)(GradNOData[index]/kappa),2));


                        }


                        float diffImg[8];

                        diffImg[0] = auxEven*fPerona0Data[index]*GradNData[index];
                        diffImg[1] = auxOdd*fPerona1Data[index]*GradNLData[index];
                        diffImg[2] = auxEven*fPerona2Data[index]*GradLData[index];
                        diffImg[3] = auxOdd*fPerona3Data[index]*GradSLData[index];
                        diffImg[4] = auxEven*fPerona4Data[index]*GradSData[index];
                        diffImg[5] = auxOdd*fPerona5Data[index]*GradSOData[index];
                        diffImg[6] = auxEven*fPerona6Data[index]*GradOData[index];
                        diffImg[7] = auxOdd*fPerona7Data[index]*GradNOData[index];

                        float sum=0.0;

                        for (int k = 0; k < 8; k++) {
                            sum += diffImg[k];
                        }


                        pixelDataOut[index] = (float)(pixelData[index] + sum);



                    }
                }
            }


            memcpy(pixelData,pixelDataOut, width * height * deep * sizeof(float));



        }//fim iteracoes



        cputimer.Stop();

        std::cout << "CPU PROCEDURAL Anisotropic filter took " << cputimer.GetTotal() << " seconds with\n" << std::endl;

        if(writeOutputImage(outputVolume)!= SDK_SUCCESS){
            return SDK_FAILURE;
        }

        try
        {
            writer->Update();

            /*CALCULATE SNR*/
            SNRfilter->SetReferenceImage(image);
            SNRfilter->SetCompareImage(importFilter->GetOutput());
            std::cout<<"SNR VALUE: "<<SNRfilter->SNR()<<std::endl;


        }
        catch( itk::ExceptionObject & exp )
        {
            std::cerr << "Exception caught !" << std::endl;
            std::cerr << exp << std::endl;
            return EXIT_FAILURE;
        }

    }





    return EXIT_SUCCESS;
}

} // end of namespace


/***********MAIN*************/
int main( int argc, char * argv[] )
{
    PARSE_ARGS;

    itk::ImageIOBase::IOPixelType     pixelType;
    itk::ImageIOBase::IOComponentType componentType;

    try
    {
        itk::GetImageType(inputVolume, pixelType, componentType);

        // This filter handles all types on input, but only produces
        // signed types
        switch( componentType )
        {
        case itk::ImageIOBase::UCHAR:
            return DoIt( argc, argv, static_cast<unsigned char>(0) );
            break;
        case itk::ImageIOBase::CHAR:
            return DoIt( argc, argv, static_cast<char>(0) );
            break;
        case itk::ImageIOBase::USHORT:
            return DoIt( argc, argv, static_cast<unsigned short>(0) );
            break;
        case itk::ImageIOBase::SHORT:
            return DoIt( argc, argv, static_cast<short>(0) );
            break;
        case itk::ImageIOBase::UINT:
            return DoIt( argc, argv, static_cast<unsigned int>(0) );
            break;
        case itk::ImageIOBase::INT:
            return DoIt( argc, argv, static_cast<int>(0) );
            break;
        case itk::ImageIOBase::ULONG:
            return DoIt( argc, argv, static_cast<unsigned long>(0) );
            break;
        case itk::ImageIOBase::LONG:
            return DoIt( argc, argv, static_cast<long>(0) );
            break;
        case itk::ImageIOBase::FLOAT:
            return DoIt( argc, argv, static_cast<float>(0) );
            break;
        case itk::ImageIOBase::DOUBLE:
            return DoIt( argc, argv, static_cast<double>(0) );
            break;
        case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
        default:
            std::cout << "unknown component type" << std::endl;
            break;
        }
    }

    catch( itk::ExceptionObject & excep )
    {
        std::cerr << argv[0] << ": exception caught !" << std::endl;
        std::cerr << excep << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

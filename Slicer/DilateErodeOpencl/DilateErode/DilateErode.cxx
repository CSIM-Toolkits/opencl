
#include "itkImageFileWriter.h"

#include "itkSmoothingRecursiveGaussianImageFilter.h"

#include "itkPluginUtilities.h"

#include "itkImportImageFilter.h"

#include "itkBinaryBallStructuringElement.h"

#include "DilateErodeCLP.h"

#include "Configure.h"


namespace
{

cl::Context context;                           /**< CL context */
std::vector<cl::Device> devices;               /**< CL device list */
std::vector<cl::Platform> platforms;           /**< list of platforms */


cl::CommandQueue commandQueue;                 /**< CL command queue */
cl::Program program;                           /**< CL program  */
cl::Kernel kernel;                             /**< CL kernel */
cl_uint width;                                 /**< Width of image */
cl_uint height;                                /**< Height of image */
cl_uint deep;                                  /**< Deep of image */
size_t kernelWorkGroupSize;                    /**< Group Size returned by kernel */
size_t blockSizeX;                             /**< Work-group size in x-direction */
size_t blockSizeY;                             /**< Work-group size in y-direction */
size_t blockSizeZ;                             /**< Work-group size in z-direction */
int sizePixel;                                 /**< Total size of image*/
cl_int eventStatus = CL_QUEUED;                /** CL event status  */
cl::Event Event;                               /** CL event  */

cl_int err = CL_SUCCESS;                       /** CL status opencl errors  */
cl_device_type dType;                          /** CL type of device (CPU | GPU)*/


/*Data objects*/
float* pixelData;       		       /**< Pointer to image data */
float* pixelDataOut;                           /**< Pointer to image data */
float* pixelDataKernel;                        /**< Pointer to kernel data */


/*Parameter to send to kernel (buffers)*/
cl::Buffer inputImage2D;                       /**< CL Input image2d */
cl::Buffer outputImage2D;                      /**< CL Output image2d */
cl::Buffer OP;                                 /**< CL kernel*/

int radius;                                    /**< radius of kernel*/
int m_seCount;                                 /**< Count of numbers 1 in kernel */
int borderFg;                                  /**< Border */
int fgValue;                                   /**< ForeGround Value */
int bgValue;                                   /**< BackGround Value */


std::vector<BufferObj> vectorBuffer;           /**< All buffers*/
std::vector<BuildOption> vectOption;           /**< All build options*/
std::string stringBuildOptions;


itk::TimeProbe cputimer;                       /**< timer for cpu execution*/
itk::TimeProbe gputimer;                       /**< timer for gpu execution*/



/*ITK OBJECTS*/
typedef itk::Image<float, 3> ImageType;
typedef itk::Image<short, 3> OutPutImageType;

typedef itk::ImageFileReader< ImageType  >  ReaderType;
typedef itk::ImageFileWriter< OutPutImageType >  WriterType;

typedef itk::ImportImageFilter<float, 3>   ImportFilterType;
ImportFilterType::Pointer importFilter;


typedef itk::CastImageFilter<ImageType, OutPutImageType >  CastFilterType;
CastFilterType::Pointer castFilter;

typename ReaderType::Pointer reader;
typename WriterType::Pointer writer;

typedef itk::BinaryBallStructuringElement< float, 3 > SRType;
typename SRType::SizeType   sizeKernel;

typename ImageType::Pointer image;
typename ImageType::RegionType region;
typename ImageType::SizeType size;
typename ImageType::SpacingType pxSpace;

void Init(){


    blockSizeX=8;
    blockSizeY=8;
    blockSizeZ = 4;
    stringBuildOptions="";
    //dType = CL_DEVICE_TYPE_GPU;   /*ON GPU*/
    dType = CL_DEVICE_TYPE_ALL;   /*ALL DEVICES*/


    radius =0;
    m_seCount = 0;
    fgValue=0;
    bgValue=0;
    borderFg = 0;

    vectOption.clear();
    vectorBuffer.clear();

    importFilter = ImportFilterType::New();
    castFilter = CastFilterType::New();
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


    SRType kernel;
    kernel.SetRadius(radius);
    kernel.CreateStructuringElement();

    sizeKernel = kernel.GetSize();

    pixelDataKernel = (float*)malloc(sizeKernel[0]*sizeKernel[1]*sizeKernel[2] * sizeof(float));
    CHECK_ALLOCATION(pixelDataKernel,"Error: Alocate() - Failed to allocate memory! (pixelDataKernel)");


    typename SRType::ConstIterator nit = kernel.Begin();

    for(int i=0; i< sizeKernel[0]*sizeKernel[1]*sizeKernel[2];i++)
    {

        pixelDataKernel[i] = (float)*nit;
#ifdef VERBOSE
        //std::cout << pixelDataKernel[i] << ",";
#endif
        if(pixelDataKernel[i] == 1){ ++m_seCount;}

        ++nit;

    }


#ifdef VERBOSE

    DEBUG(m_seCount);
    DEBUG((int)sizeKernel[0]);
    DEBUG((int)sizeKernel[1]);
    DEBUG((int)sizeKernel[2]);
    DEBUG((float)sizeKernel[0]*sizeKernel[1]*sizeKernel[1]);
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


    pixelData  = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    memcpy(pixelData, image->GetBufferPointer(), size[0]*size[1]*size[2]*sizeof(float));
    CHECK_ALLOCATION(pixelData,"Error: Alocate() - Failed to allocate memory! (outputImageData)");


    pixelDataOut = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    CHECK_ALLOCATION(pixelDataOut,"Error: Alocate() - Failed to allocate memory! (outputImageData)");


    // initialize the Image OutPut data to NULL
    memset(pixelDataOut, 0, width * height * deep * sizeof(float));


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


    /* Create and initialize input buffer image*/
    inputImage2D = cl::Buffer(context,
                              CL_MEM_READ_ONLY,
                              sizeof(float) * width * height * deep ,
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

    /* Create and initialize input buffer image*/
    OP = cl::Buffer(context,
                    CL_MEM_READ_ONLY,
                    sizeof(float) * sizeKernel[0]*sizeKernel[1]*sizeKernel[2] ,
            NULL,
            &err);

    CHECK_OPENCL_ERROR(err, "cl::Buffer::cl::Buffer() failed. (inSize)");



    BufferObj imageInputBuffer;
    imageInputBuffer.buffer = inputImage2D;
    imageInputBuffer.data = pixelData;
    imageInputBuffer.size = sizeof(float) * width * height* deep ;
    imageInputBuffer.type = TYPE_INBUFFER;

    BufferObj imageOutPutBuffer;
    imageOutPutBuffer.buffer = outputImage2D;
    imageOutPutBuffer.data = pixelDataOut;
    imageOutPutBuffer.size = sizeof(float) * width * height* deep ;
    imageOutPutBuffer.type = TYPE_OUTBUFFER;


    BufferObj OPBuffer;
    OPBuffer.buffer = OP;
    OPBuffer.data = pixelDataKernel;
    OPBuffer.size = sizeof(float) * sizeKernel[0]*sizeKernel[1]*sizeKernel[2] ;
    OPBuffer.type = TYPE_INBUFFER;


    BufferObj RadiusParam;
    RadiusParam.buffer = NULL;
    RadiusParam.dataINT = radius;
    RadiusParam.size = sizeof(int);
    RadiusParam.type = TYPE_INT;


    BufferObj SeSumParam;
    SeSumParam.buffer = NULL;
    SeSumParam.dataINT = m_seCount;
    SeSumParam.size = sizeof(int);
    SeSumParam.type = TYPE_INT;


    BufferObj fgValueParam;
    fgValueParam.buffer = NULL;
    fgValueParam.dataINT = fgValue;
    fgValueParam.size = sizeof(int);
    fgValueParam.type = TYPE_INT;


    BufferObj bgValueParam;
    bgValueParam.buffer = NULL;
    bgValueParam.dataINT = bgValue;
    bgValueParam.size = sizeof(int);
    bgValueParam.type = TYPE_INT;


    BufferObj borderFgParam;
    borderFgParam.buffer = NULL;
    borderFgParam.dataINT = borderFg;
    borderFgParam.size = sizeof(int);
    borderFgParam.type = TYPE_INT;

    vectorBuffer.push_back(imageInputBuffer);
    vectorBuffer.push_back(imageOutPutBuffer);

    vectorBuffer.push_back(OPBuffer);

    vectorBuffer.push_back(RadiusParam);
    vectorBuffer.push_back(SeSumParam);
    vectorBuffer.push_back(fgValueParam);
    vectorBuffer.push_back(bgValueParam);
    vectorBuffer.push_back(borderFgParam);



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
    kernelWorkGroupSize = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(devices[0], &err);
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


int readBufferOutput(){

    // Enqueue readBuffer
    err = commandQueue.enqueueReadBuffer(
                outputImage2D,
                CL_FALSE,
                0,
                sizeof(float)* width * height * deep,
                pixelDataOut,
                NULL,
                &Event);
    CHECK_OPENCL_ERROR(err, "CommandQueue::enqueueReadImage failed.");

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

    writer->SetUseCompression(1);


    return SDK_SUCCESS;
}


template <class T>
int DoIt( int argc, char * argv[], T )
{
    PARSE_ARGS;

    Init();


#ifdef VERBOSE
    DEBUG(foreGround);
    DEBUG(backGround);
    DEBUG(radiusIn);
    DEBUG(boundary);
#endif

    radius = radiusIn;
    fgValue = foreGround;
    bgValue = backGround;
    borderFg = boundary;

    if(Allocate(inputVolume)!= SDK_SUCCESS){
        return SDK_FAILURE;
    }

    if(deviceType.compare("GPU")==0){
#ifdef VERBOSE
        message("GPU PROCESSING...");
#endif

        gputimer.Reset();
        gputimer.Start();

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

        if(filterType.compare("Dilate")==0){

            if(LoadKernelAndCompile("/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/GPUBinaryDilateImageFilter.cl","BinaryDilateFilter")!= SDK_SUCCESS){
                return SDK_FAILURE;
            }

        }else if(filterType.compare("Erode")==0){
            if(LoadKernelAndCompile("/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/GPUBinaryErodeImageFilter.cl","BinaryErodeFilter")!= SDK_SUCCESS){
                return SDK_FAILURE;
            }
        }



        if(setArgBuffer(vectorBuffer)!= SDK_SUCCESS){
            return SDK_FAILURE;
        }




        if(runCL()!= SDK_SUCCESS){
            return SDK_FAILURE;
        }



        //Finish first kernel execution
        //Get Image result
        if(readBufferOutput()!= SDK_SUCCESS){
            return SDK_FAILURE;
        }

        gputimer.Stop();

        std::cout << "GPU sobel filter took " << gputimer.GetTotal() << " seconds with\n" << std::endl;

    }else if(deviceType.compare("CPU")==0){
#ifdef VERBOSE
        message("CPU PROCESSING...");
#endif

        cputimer.Reset();
        cputimer.Start();
        if(filterType.compare("Dilate")==0){

            for(int giz=0; giz<deep; giz++){
                for(int giy=0; giy<height; giy++){
                    for(int gix=0; gix<width; gix++){

                        unsigned int gidx = width*(giz*height + giy) + gix;
                        unsigned int opIdx = (2*radius + 1)*(2*radius + 1)*(2*radius + 1) - 1;

                        bool isValid = true;
                        if(gix < 0 || gix >= width) isValid = false;
                        if(giy < 0 || giy >= height) isValid = false;
                        if(giz < 0 || giz >= deep) isValid = false;

                        float result = pixelData[gidx];
                        bool finished = false;


                        if( isValid )
                        {
                            for(int z = -radius; z <= radius; z++)
                            {
                                for(int y = -radius; y <= radius; y++)
                                {
                                    for(int x = -radius; x <= radius; x++)
                                    {
                                        if(pixelDataKernel[opIdx] == 1){
                                            int tx = gix-x;
                                            if(tx < 0 || tx >= width){
                                                if(borderFg){ result = fgValue; finished = true; break; }
                                                --opIdx; continue; }

                                            int ty = giy-y;
                                            if(ty < 0 || ty >= height){
                                                if(borderFg){ result = fgValue; finished = true; break; }
                                                --opIdx; continue; }

                                            int tz = giz-z;
                                            if(tz < 0 || tz >= deep){
                                                if(borderFg){ result = fgValue; finished = true; break; }
                                                --opIdx; continue; }

                                            unsigned int tidx = width*height*tz + width*ty + tx;
                                            if(pixelData[tidx] == fgValue){
                                                result = fgValue;
                                                finished = true;
                                                break;
                                            }
                                        }
                                        --opIdx;
                                    }
                                    if(finished) break;
                                }
                                if(finished) break;
                            }

                            pixelDataOut[gidx] = result;

                        }
                    }
                }
            }


        }else if (filterType.compare("Erode")==0){

            for(int giz=0; giz<deep; giz++){
                for(int giy=0; giy<height; giy++){
                    for(int gix=0; gix<width; gix++){


                        unsigned int gidx = width*(giz*height + giy) + gix;
                        unsigned int sum = 0;
                        unsigned int opIdx = 0;

                        bool isValid = true;
                        if(gix < 0 || gix >= width) isValid = false;
                        if(giy < 0 || giy >= height) isValid = false;
                        if(giz < 0 || giz >= deep) isValid = false;

                        float result = pixelData[gidx];
                        bool finished = false;


                        if( isValid )
                        {

                            for(int z = -radius; z <= radius; z++)
                            {
                                for(int y = -radius; y <= radius; y++)
                                {
                                    for(int x = -radius; x <= radius; x++)
                                    {
                                        if(pixelDataKernel[opIdx] == 1){
                                            int tx = gix-x;
                                            if(tx < 0 || tx >= width){
                                                  if(!borderFg){ finished = true; break; }
                                                  ++opIdx; ++sum; continue;
                                            }

                                            int ty = giy-y;
                                            if(ty < 0 || ty >= height){
                                                if(!borderFg){ finished = true; break; }
                                                ++opIdx; ++sum; continue;
                                            }

                                            int tz = giz-z;
                                            if(tz < 0 || tz >= deep){
                                                if(!borderFg){ finished = true; break; }
                                                ++opIdx; ++sum; continue;
                                            }

                                            unsigned int tidx = width*height*tz + width*ty + tx;

                                            if(pixelData[tidx] == fgValue){
                                              ++sum;
                                            }
                                        }
                                        opIdx++;
                                    }
                                    if(finished) break;
                                }
                                if(finished) break;
                            }

                            if(pixelData[gidx] == fgValue && sum < m_seCount)
                                result = bgValue;

                            pixelDataOut[gidx] = result;

                        }
                    }
                }
            }


        }



        cputimer.Stop();

        std::cout << "CPU " + filterType +  " filter took " << cputimer.GetTotal() << " seconds with\n" << std::endl;

    }

//    textFile textfile;

//    textfile.filePath = std::string("/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/");
//    textfile.fileName = std::string("OriginalImage.txt");
//    writeImageTextFile(textfile,pixelData,width,height,deep);


//    textfile.fileName = std::string("OutputImage.txt");
//    writeImageTextFile(textfile,pixelDataOut,width,height,deep);

    if(writeOutputImage(outputVolume)!= SDK_SUCCESS){
        return SDK_FAILURE;
    }

    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & exp )
    {
        std::cerr << "Exception caught !" << std::endl;
        std::cerr << exp << std::endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

} // end of anonymous namespace

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

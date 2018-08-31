#include "itkImageFileWriter.h"

#include "itkSmoothingRecursiveGaussianImageFilter.h"

#include "itkPluginUtilities.h"

#include "itkImportImageFilter.h"

#include "SobelFilterOpenCLCLP.h"

using namespace std;
#include "Configure.h"

// Use an anonymous namespace to keep class types and function names
// from colliding when module is used as shared object module.  Every
// thing should be in an anonymous namespace except for the module
// entry point, e.g. main()
//
namespace
{

cl_double setupTime;                /**< time taken to setup OpenCL resources and building kernel */
cl_double kernelTime;               /**< time taken to run kernel and read result back */

cl::Context context;                            /**< CL context */
std::vector<cl::Device> devices;                /**< CL device list */
std::vector<cl::Device> device;                 /**< CL device to be used */
std::vector<cl::Platform> platforms;            /**< list of platforms */
cl::Buffer inputImage2D;                       /**< CL Input image2d */
cl::Buffer outputImage2D;                      /**< CL Output image2d */
cl::CommandQueue commandQueue;                  /**< CL command queue */
cl::Program program;                            /**< CL program  */
cl::Kernel kernel;                              /**< CL kernel */

float* pixelData;       /**< Pointer to image data */
float* pixelDataOut;       /**< Pointer to image data */
cl_uint pixelSize;                  /**< Size of a pixel in BMP format> */
cl_uint width;                      /**< Width of image */
cl_uint height;                     /**< Height of image */
cl_uint deep;                     /**< Deep of image */
size_t kernelWorkGroupSize;         /**< Group Size returned by kernel */
size_t blockSizeX;                  /**< Work-group size in x-direction */
size_t blockSizeY;                  /**< Work-group size in y-direction */
int radius = 3;

itk::TimeProbe cputimer;
itk::TimeProbe gputimer;



template <class T>
int DoIt( int argc, char * argv[], T )
{
    PARSE_ARGS;

    std::cout<<"Device Type:"<<deviceType<<std::endl;


    blockSizeX=16;
    blockSizeY=16;


    typedef itk::Image<float, 3> ImageType;
    typedef itk::Image<short, 3> OutPutImageType;

    typedef itk::ImageFileReader< ImageType  >  ReaderType;
    typedef itk::ImageFileWriter< OutPutImageType >  WriterType;

    typedef itk::ImportImageFilter< float, 3 >   ImportFilterType;
    ImportFilterType::Pointer importFilter = ImportFilterType::New();


    typedef itk::CastImageFilter<ImageType, OutPutImageType >  CastFilterType;
    CastFilterType::Pointer castFilter = CastFilterType::New();

    typename ReaderType::Pointer reader = ReaderType::New();
    typename WriterType::Pointer writer = WriterType::New();


    reader->SetFileName( inputVolume.c_str());
    reader->Update();

    typename ImageType::Pointer image = reader->GetOutput();

    typename ImageType::RegionType region = image->GetLargestPossibleRegion();

    typename ImageType::SizeType size = region.GetSize();

    std::cout << "width : " << size[0] << std::endl;
    std::cout << "heigth : " << size[1] << std::endl;
    std::cout << "deep : " << size[2] << std::endl;

    width= size[0];
    height=size[1];
    deep=size[2];

    pixelData  = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));
    memcpy( pixelData, image->GetBufferPointer(), size[0]*size[1]*size[2]*sizeof(float));

    pixelDataOut = (float*)malloc(size[0]*size[1]*size[2] * sizeof(float));

    // error check
    CHECK_ALLOCATION(pixelDataOut,
                     "Failed to allocate memory! (outputImageData)");


    // initialize the Image data to NULL
    memset(pixelDataOut, 0, width * height *deep * sizeof(float));


    int sizePixel = (size[0]*size[1]*size[2]);

    if(deviceType.compare("GPU")==0){


        std::cout<< "GPU Processing"<<std::endl;

        cl_int err = CL_SUCCESS;
        cl_device_type dType;

        dType = CL_DEVICE_TYPE_GPU;

        err = cl::Platform::get(&platforms);
        CHECK_OPENCL_ERROR(err, "Platform::get() failed.");

        std::vector<cl::Platform>::iterator i;
        if(platforms.size() > 0)
        {
            i = platforms.begin() + 0;

        }

        cl_context_properties cps[3] =
        {
            CL_CONTEXT_PLATFORM,
            (cl_context_properties)(*i)(),
            0
        };

        context = cl::Context(dType, cps, NULL, NULL, &err);
        CHECK_OPENCL_ERROR(err, "Context::Context() failed.");

        devices = context.getInfo<CL_CONTEXT_DEVICES>(&err);
        CHECK_OPENCL_ERROR(err, "Context::getInfo() failed.");

        std::cout << "Platform :" << (*i).getInfo<CL_PLATFORM_VENDOR>().c_str() << "\n";
        int deviceCount = (int)devices.size();
        int j = 0;
        for (std::vector<cl::Device>::iterator i = devices.begin(); i != devices.end();
             ++i, ++j)
        {
            std::cout << "Device " << j << " : ";
            std::string deviceName = (*i).getInfo<CL_DEVICE_NAME>();
            std::cout << deviceName.c_str() << "\n";
        }
        std::cout << "\n";

        if (deviceCount == 0)
        {
            std::cout << "No device available\n";
            return SDK_FAILURE;
        }

        commandQueue = cl::CommandQueue(context, devices[0], 0,
                &err);
        CHECK_OPENCL_ERROR(err, "CommandQueue::CommandQueue() failed.");

        /*
     * Create and initialize memory objects
     */
        inputImage2D = cl::Buffer(context,
                                  CL_MEM_READ_ONLY,
                                  sizeof(float) * width * height * deep ,
                                  NULL,
                                  &err);


        CHECK_OPENCL_ERROR(err, "Image2D::Image2D() failed. (inputImage2D)");



        // Create memory objects for output Image
        outputImage2D = cl::Buffer(context,
                                   CL_MEM_WRITE_ONLY,
                                   sizeof(float)* width * height * deep,
                                   NULL,
                                   &err);
        CHECK_OPENCL_ERROR(err, "Image2D::Image2D() failed. (outputImage2D)");

        device.push_back(devices[0]);


        // build Program
        buildProgramData buildData;
        buildData.kernelName = std::string("SobelFilter.cl");
        buildData.kernelPath = std::string("/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/SobelFilterOpenCL/");

        char buildOption[128];
        sprintf(buildOption, "-D width=%d -D height=%d -D depth=%d",width,height,deep);

        buildData.flagsStr = std::string(buildOption);
        buildOpenCLProgram(program, context, buildData,device);



        // Create kernel
        kernel = cl::Kernel(program, "SobelFilter",  &err);
        CHECK_OPENCL_ERROR(err, "Kernel::Kernel() failed.");

        // Check group size against group size returned by kernel
        kernelWorkGroupSize = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>
                (devices[0], &err);
        CHECK_OPENCL_ERROR(err, "Kernel::getWorkGroupInfo()  failed.");

        if((blockSizeX * blockSizeY) > kernelWorkGroupSize)
        {

            std::cout << "Out of Resources!" << std::endl;
            std::cout << "Group Size specified : "
                      << blockSizeX * blockSizeY << std::endl;
            std::cout << "Max Group Size supported on the kernel : "
                      << kernelWorkGroupSize << std::endl;
            std::cout << "Falling back to " << kernelWorkGroupSize << std::endl;


            if(blockSizeX > kernelWorkGroupSize)
            {
                blockSizeX = kernelWorkGroupSize;
                blockSizeY = 1;
            }
        }


        cl_int status;

        cl::size_t<3> originWriteImage;
        originWriteImage[0] = 0;
        originWriteImage[1] = 0;
        originWriteImage[2] = 0;

        cl::size_t<3> regionWriteImage;
        regionWriteImage[0] = width;
        regionWriteImage[1] = height;
        regionWriteImage[2] = 1;

        gputimer.Reset();
        gputimer.Start();

        cl::Event writeEvt;
        status = commandQueue.enqueueWriteBuffer(
                    inputImage2D,
                    CL_TRUE,
                    0,
                    sizeof(float)* width * height * deep,
                    pixelData,
                    NULL,
                    &writeEvt);
        CHECK_OPENCL_ERROR(status,
                           "CommandQueue::enqueueWriteImage failed. (inputImage2D)");

        status = commandQueue.flush();
        CHECK_OPENCL_ERROR(status, "cl::CommandQueue.flush failed.");

        cl_int eventStatus = CL_QUEUED;
        while(eventStatus != CL_COMPLETE)
        {
            status = writeEvt.getInfo<cl_int>(
                        CL_EVENT_COMMAND_EXECUTION_STATUS,
                        &eventStatus);
            CHECK_OPENCL_ERROR(status,
                               "cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");

        }


        // Set appropriate arguments to the kernel
        // input buffer image
        status = kernel.setArg(0, inputImage2D);
        CHECK_OPENCL_ERROR(status, "Kernel::setArg() failed. (inputImageBuffer)");

        // outBuffer imager
        status = kernel.setArg(1, outputImage2D);
        CHECK_OPENCL_ERROR(status, "Kernel::setArg() failed. (outputImageBuffer)");


        /*
     * Enqueue a kernel run call.
     */

        cl::NDRange offset(0,0,0);
        cl::NDRange globalThreads(width, height, deep);
        cl::NDRange localThreads(blockSizeX, blockSizeY,1);

        cl::Event ndrEvt;
        status = commandQueue.enqueueNDRangeKernel(
                    kernel,
                    offset,
                    globalThreads,
                    localThreads,
                    0,
                    &ndrEvt);
        CHECK_OPENCL_ERROR(status, "CommandQueue::enqueueNDRangeKernel() failed.");

        status = commandQueue.flush();
        CHECK_OPENCL_ERROR(status, "cl::CommandQueue.flush failed.");

        eventStatus = CL_QUEUED;
        while(eventStatus != CL_COMPLETE)
        {
            status = ndrEvt.getInfo<cl_int>(
                        CL_EVENT_COMMAND_EXECUTION_STATUS,
                        &eventStatus);
            CHECK_OPENCL_ERROR(status,
                               "cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");
        }



        // Enqueue readBuffer
        cl::Event readEvt;
        status = commandQueue.enqueueReadBuffer(
                    outputImage2D,
                    CL_FALSE,
                    0,
                    sizeof(float)* width * height * deep,
                    pixelDataOut,
                    NULL,
                    &readEvt);
        CHECK_OPENCL_ERROR(status, "CommandQueue::enqueueReadImage failed.");

        status = commandQueue.flush();
        CHECK_OPENCL_ERROR(status, "cl::CommandQueue.flush failed.");

        eventStatus = CL_QUEUED;
        while(eventStatus != CL_COMPLETE)
        {
            status = readEvt.getInfo<cl_int>(
                        CL_EVENT_COMMAND_EXECUTION_STATUS,
                        &eventStatus);
            CHECK_OPENCL_ERROR(status,
                               "cl:Event.getInfo(CL_EVENT_COMMAND_EXECUTION_STATUS) failed.");

        }

        gputimer.Stop();
         std::cout << "GPU mean filter took " << gputimer.GetMean() << " seconds with\n" << std::endl;

    }
    else if(deviceType.compare("CPU")==0){

        std::cout<< "CPU Processing"<<std::endl;
        cputimer.Reset();
        cputimer.Start();

        int index = 0;
        int arg[9];
        float neighborhood[9];
        float Gx=0.0, Gy=0.0, G=0.0;

        int step = 1;
        int count = 0;
        float sum = 0.0;


        for(int gix=0; gix<width; gix++){
            for(int giy=0; giy<height; giy++){
                for(int giz=0; giz<deep; giz++){

                    index = width*(giz*height + giy) + gix;

                    count=0;
                    //get neigborhood
                    for(int j=-step;j<step+1;j++){
                        for(int i=-step;i<step+1;i++){
                            arg[count] = 0.0;
                            arg[count]=index + (width*j) + i;
                            count++;
                        }
                    }

                    sum=0.0;
                    //sum
                    for(int i=0;i<9;i++){
                        if(!isnan((float)arg[i])) neighborhood[i]=pixelData[arg[i]];

                    }



                    Gx = -neighborhood[0] -(int)2*neighborhood[3] - neighborhood[6] + neighborhood[2] + (int)2*neighborhood[5] + neighborhood[8];
                    Gy = -neighborhood[6] -(int)2*neighborhood[7] - neighborhood[8] + neighborhood[0] + (int)2*neighborhood[1] + neighborhood[2];
                    //G = native_divide(native_sqrt(Gx * Gx + Gy * Gy), (float)(2));

                    G = pow(Gx * Gx + Gy * Gy, 1.0/2.0);


                    pixelDataOut[index] = G;



                    //fim laço triplo
                }}}

        cputimer.Stop();

        std::cout << "CPU mean filter took " << cputimer.GetMean() << " seconds with\n" << std::endl;


    }
    ImportFilterType::SizeType  sizeImport;
    sizeImport[0]  = size[0];  // size along X
    sizeImport[1]  = size[1];  // size along Y
    sizeImport[2]  = size[2];  // size along Y
    ImportFilterType::IndexType start;
    start.Fill( 0 );
    ImportFilterType::RegionType regionImport;
    regionImport.SetIndex( start );
    regionImport.SetSize(  sizeImport  );

    importFilter->SetRegion( regionImport );


    const itk::SpacePrecisionType origin[ 3 ] = { 0.0, 0.0, 0.0};
    importFilter->SetOrigin( origin );

    const itk::SpacePrecisionType  spacing[ 3 ] =  { 1.0, 1.0, 2.6};
    importFilter->SetSpacing( spacing );

    const bool importImageFilterWillOwnTheBuffer = true;
    importFilter->SetImportPointer( pixelDataOut, sizePixel,
                                    importImageFilterWillOwnTheBuffer );

    importFilter->Update();
    castFilter->SetInput(importFilter->GetOutput() );
    castFilter->Update();

    writer->SetFileName( outputVolume.c_str() );
    writer->SetInput(  castFilter->GetOutput()  );



    writer->SetUseCompression(1);
    writer->Update();

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

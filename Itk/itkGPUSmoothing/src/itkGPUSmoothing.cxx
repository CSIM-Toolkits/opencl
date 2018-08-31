
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMeanImageFilter.h"
#include "itkImportImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkImageLinearIteratorWithIndex.h"

using namespace std;
#include <Configure.h>



        cl_double setupTime;                /**< time taken to setup OpenCL resources and building kernel */
        cl_double kernelTime;               /**< time taken to run kernel and read result back */

        cl::Context context;                            /**< CL context */
        std::vector<cl::Device> devices;                /**< CL device list */
        std::vector<cl::Device> device;                 /**< CL device to be used */
        std::vector<cl::Platform> platforms;            /**< list of platforms */
        cl::Buffer inputImage2D;                       /**< CL Input image2d */
        cl::Buffer outputImage2D;                      /**< CL Output image2d */
        cl::Buffer QOutputImage2D;
        cl::CommandQueue commandQueue;                  /**< CL command queue */
        cl::Program program;                            /**< CL program  */
        cl::Kernel kernel;                              /**< CL kernel */


        float* pixelData;       /**< Pointer to image data */
        float* pixelDataOut;       /**< Pointer to image data */
        float* qpixelDataOut;       /**< Pointer to image data */
        cl_uint pixelSize;                  /**< Size of a pixel in BMP format> */
        cl_uint width;                      /**< Width of image */
        cl_uint height;                     /**< Height of image */
        size_t kernelWorkGroupSize;         /**< Group Size returned by kernel */
        size_t blockSizeX;                  /**< Work-group size in x-direction */
	size_t blockSizeY;                  /**< Work-group size in y-direction */

float getMinimum(float* array, int width, int height, int depth){

	 float min = 0.0;
	  
	 for(int x=0; x<width;x++){
	  for(int y=0; y<height;y++){
	   for(int z=0; z<depth;z++){

	     int index = width*(z*height + y) + x;
	     if(array[index]<min) min= array[index];
	   

	 }}}


	return min;
}      

void add(float* array,int width,int height, float c) {
	for (int i=0; i<width*height; i++){
		array[i] = array[i] + c;
	}
}


int main(int argc, char *argv[])
{

  blockSizeX=256;
  blockSizeY=1;
  if( argc <  3 )
  {
    std::cerr << "Error: missing arguments" << std::endl;
    std::cerr << "inputfile outputfile [num_dimensions]" << std::endl;
    return EXIT_FAILURE;
  }


  typedef itk::Image<float, 2> ImageType;
  typedef itk::Image<unsigned char, 2> OutPutImageType;

  typedef itk::ImageFileReader< ImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutPutImageType >  WriterType;

  typedef itk::ImportImageFilter< float, 2 >   ImportFilterType;
  ImportFilterType::Pointer importFilter = ImportFilterType::New();


  typedef itk::CastImageFilter<ImageType, OutPutImageType >  CastFilterType;
 CastFilterType::Pointer castFilter = CastFilterType::New();

  typename ReaderType::Pointer reader = ReaderType::New();
  typename WriterType::Pointer writer = WriterType::New();


  reader->SetFileName( argv[1] );
  reader->Update();

  ImageType::Pointer image = reader->GetOutput();

  ImageType::RegionType region = image->GetLargestPossibleRegion();

  ImageType::SizeType size = region.GetSize();

  std::cout << "width : " << size[0] << std::endl;
  std::cout << "heigth : " << size[1] << std::endl;
  //std::cout << reader<< std::endl;
  //std::cout << image<< std::endl;


  width  = size[0];
  height = size[1];

  pixelData  = (float*)malloc(size[0]*size[1] * sizeof(float)); 
  memcpy( pixelData, image->GetBufferPointer(), size[0]*size[1]*sizeof(float));

  pixelDataOut = (float*)malloc(size[0]*size[1] * sizeof(float));
  qpixelDataOut = (float*)malloc(size[0]*size[1] * sizeof(float));

    // error check
    CHECK_ALLOCATION(pixelDataOut,
                     "Failed to allocate memory! (outputImageData)");
    // error check
    CHECK_ALLOCATION(qpixelDataOut,
                     "Failed to allocate memory! (outputImageData)");


    // initialize the Image data to NULL
    memset(pixelDataOut, 0, width * height * sizeof(float));
    memset(qpixelDataOut, 0, width * height * sizeof(float));

  
   int sizePixel = (size[0]*size[1]);

  /*Parameters and Pre-processing in HOST*/
   cl_float minImg = getMinimum(pixelData,size[0],size[1],0);

    if (minImg < 0 && abs(minImg) < 0.05) {
        add(qpixelDataOut, width,height,(-1) * 0.05);
    }

/*
	for(int i=0; i< sizePixel;i++ ){

		std::cout<<"Index["<< i << "] = " << qpixelDataOut[i]<<std::endl;

	}

  typedef itk::ImageLinearIteratorWithIndex< ImageType >      IteratorType;

  IteratorType inputIt( image, image->GetRequestedRegion() );
  inputIt.SetDirection(0);


  for ( inputIt.GoToBegin(); ! inputIt.IsAtEnd(); inputIt.NextLine())
    {
    inputIt.GoToBeginOfLine();
    while ( ! inputIt.IsAtEndOfLine() )
      {
      std::cout<< inputIt.Get()<<std::endl;
      ++inputIt;
      }
    }
*/

/*
int valueMax=0;

for(int i=0; i< sizePixel;i++ ){

  std::cout<<"Index["<< i << "] = " << pixelData[i]<<std::endl;
	if(valueMax<pixelData[i]){
	valueMax = pixelData[i];
	}

}

  std::cout << "Máximo : " << valueMax << std::endl;
*/

//------


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
                               sizeof(float) * width * height ,
                               NULL,
                               &err);


    CHECK_OPENCL_ERROR(err, "Image2D::Image2D() failed. (inputImage2D)");
 


    // Create memory objects for output Image
    outputImage2D = cl::Buffer(context,
                                CL_MEM_WRITE_ONLY,
                                sizeof(float)* width * height,
				NULL,
                                &err);
    CHECK_OPENCL_ERROR(err, "Image2D::Image2D() failed. (outputImage2D)");


    QOutputImage2D = cl::Buffer(context,
                                CL_MEM_WRITE_ONLY,
                                sizeof(float)* width * height,
				NULL,
                                &err);
    CHECK_OPENCL_ERROR(err, "Image2D::Image2D() failed. (outputImage2D)");

    device.push_back(devices[0]);

    // create a CL program using the kernel source
    appsdk::SDKFile kernelFile;
    std::string kernelPath = getPath();

        kernelPath.append("Anomalous.cl");
        if(!kernelFile.open(kernelPath.c_str()))
        {
            std::cout << "Failed to load kernel file : " << kernelPath << std::endl;
            return SDK_FAILURE;
        }

        // create program source
        cl::Program::Sources programSource(1,
                                           std::make_pair(kernelFile.source().data(),
                                                   kernelFile.source().size()));

        // Create program object
        program = cl::Program(context, programSource, &err);
        CHECK_OPENCL_ERROR(err, "Program::Program() failed.");

        char buildOption[128];
        sprintf(buildOption, "-D width=%d -D height=%d -D depth=%d ",width,height,1);

        std::string flagsStr = std::string(buildOption);



    err = program.build(device, flagsStr.c_str());

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
    kernel = cl::Kernel(program, "Anomalous",  &err);
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


    cl::Event writeEvt;
    status = commandQueue.enqueueWriteBuffer(
                 inputImage2D,
                 CL_TRUE,
                 0,
                 sizeof(float)* width * height,
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


    status = commandQueue.enqueueWriteBuffer(
                 QOutputImage2D,
                 CL_TRUE,
                 0,
                 sizeof(float)* width * height,
                 qpixelDataOut,
                 NULL,
                 &writeEvt);
    CHECK_OPENCL_ERROR(status,
                       "CommandQueue::enqueueWriteImage failed. (inputImage2D)");

    status = commandQueue.flush();
    CHECK_OPENCL_ERROR(status, "cl::CommandQueue.flush failed.");

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

    // outBuffer imager
    status = kernel.setArg(2, QOutputImage2D);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg() failed. (outputImageBuffer)");

    status = kernel.setArg(3, minImg);
    CHECK_OPENCL_ERROR(status, "Kernel::setArg() failed. (outputImageBuffer)");



    /*
    * Enqueue a kernel run call.
    */

    cl::NDRange offset(0,0);
    //std::cout<<"Tamanho: "<< width<< " - " << height<<std::endl;
    cl::NDRange globalThreads(width, height);
    cl::NDRange localThreads(blockSizeX, blockSizeY);

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



    // Enqueue Read Image
    //originWriteImage[0] = 0;
    //originWriteImage[1] = 0;
    //originWriteImage[2] = 0;

    //regionWriteImage[0] = width;
    //regionWriteImage[1] = height;
    //regionWriteImage[2] = 1;

    // Enqueue readBuffer
    cl::Event readEvt;
    status = commandQueue.enqueueReadBuffer(
                 outputImage2D,
                 CL_FALSE,
		 0,
                 sizeof(float)* width * height,
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

//float valueMax =0;
//for(int j=0;j<100;j++){
        //pixelDataOut[j]= 6800;
	//std::cout<<"["<<j<<"]= "<<pixelDataOut[j] <<std::endl;
	//if(valueMax<pixelDataOut[j]){
	//valueMax = pixelDataOut[j];
	//}
//}

  //std::cout << "Máximo : " << valueMax << std::endl;


//-------



  ImportFilterType::SizeType  sizeImport;
	  sizeImport[0]  = size[0];  // size along X
	  sizeImport[1]  = size[1];  // size along Y
  ImportFilterType::IndexType start;
  	  start.Fill( 0 );
  ImportFilterType::RegionType regionImport;
	  regionImport.SetIndex( start );
	  regionImport.SetSize(  sizeImport  );

  importFilter->SetRegion( regionImport );


  const itk::SpacePrecisionType origin[ 2 ] = { 0.0, 0.0};
  importFilter->SetOrigin( origin );

  const itk::SpacePrecisionType  spacing[ 2 ] =  { 1.0, 1.0};
  importFilter->SetSpacing( spacing );

  const bool importImageFilterWillOwnTheBuffer = true;
  importFilter->SetImportPointer( pixelDataOut, sizePixel,
                                  importImageFilterWillOwnTheBuffer );


 castFilter->SetInput(importFilter->GetOutput() );
 castFilter->Update();

  writer->SetFileName( argv[2] );
  writer->SetInput(  castFilter->GetOutput()  );

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



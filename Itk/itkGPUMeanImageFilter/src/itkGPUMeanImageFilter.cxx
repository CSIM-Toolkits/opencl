

#include "itkGPUImage.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMeanImageFilter.h"

#include "itkGPUKernelManager.h"
#include "itkGPUContextManager.h"





int main(int argc, char *argv[])
{


  if(!itk::IsGPUAvailable())
  {
    std::cerr << "OpenCL-enabled GPU is not present." << std::endl;
    return EXIT_FAILURE;
  }

  if( argc <  3 )
  {
    std::cerr << "Error: missing arguments" << std::endl;
    std::cerr << "inputfile outputfile [num_dimensions]" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inFile( argv[1] );
  std::string outFile( argv[2] );

  typedef itk::GPUImage<float, 2> ImageType;
  typedef itk::GPUImage<unsigned char, 2> OutPutImageType;

  typedef itk::ImageFileReader< ImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutPutImageType >  WriterType;

  typename ReaderType::Pointer reader = ReaderType::New();
  typename WriterType::Pointer writer = WriterType::New();




  reader->SetFileName(inFile);
  reader->Update();

  writer->SetFileName( outFile );


  ImageType::Pointer image = reader->GetOutput();
  ImageType::Pointer  outputImage;


  ImageType::RegionType region = image->GetLargestPossibleRegion();

  ImageType::SizeType size = region.GetSize();



  outputImage = ImageType::New();
  outputImage->SetRegions( region );
  outputImage->Allocate();
  outputImage->FillBuffer( 0.0f );



  int radiusX=2, radiusY=2, width, heigth;

  width = size[0];

  heigth = size[1];

  std::cout << "width : " << size[0] << std::endl;
  std::cout << "heigth : " << size[1] << std::endl;

  //
  // create GPU program object
  //
  itk::GPUKernelManager::Pointer kernelManager = itk::GPUKernelManager::New();

  // Pega o código do arquivo .cl 
  kernelManager->LoadProgramFromFile("/home/alexandrefreitas/Projetos/ITKProjects/itkGPUMeanImageFilter/src/GPUMeanImageFilter.cl", "#define PIXELTYPE float\n");


  //
  // create addition kernel
  //
  int kernel_meanFilter = kernelManager->CreateKernel("MeanFilter2D");

  image->SetCurrentCommandQueue( 0 );
  outputImage->SetCurrentCommandQueue( 0 );
  kernelManager->SetCurrentCommandQueue( 0 );


  kernelManager->SetKernelArgWithImage(kernel_meanFilter, 0, image->GetGPUDataManager());
  kernelManager->SetKernelArgWithImage(kernel_meanFilter, 1, outputImage->GetGPUDataManager());
  kernelManager->SetKernelArg(kernel_meanFilter, 2, sizeof(int), &radiusX);
  kernelManager->SetKernelArg(kernel_meanFilter, 3, sizeof(int), &radiusY);
  kernelManager->SetKernelArg(kernel_meanFilter, 4, sizeof(int), &width);
  kernelManager->SetKernelArg(kernel_meanFilter, 5, sizeof(int), &heigth);

  kernelManager->LaunchKernel2D(kernel_meanFilter, size[0], size[1], 16, 16);


//Converter imagem de float para unsigned char, para gerar imagem png
  typedef itk::CastImageFilter< ImageType, OutPutImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( outputImage );

  writer->SetInput( filter->GetOutput() );
  writer->Update();



  return EXIT_SUCCESS;
}

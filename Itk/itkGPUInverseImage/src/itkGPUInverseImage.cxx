/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

/**
 * Test program for itkGPUImage class.
 * This program shows how to use GPU image and GPU program.
 */
//#include "pathToOpenCLSourceCode.h"



#include "itkGPUImage.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMeanImageFilter.h"
#include "itkImageLinearIteratorWithIndex.h"

#include "itkGPUKernelManager.h"
#include "itkGPUContextManager.h"
#include "itkGPUImageOps.h"
#include "itkCastImageFilter.h"





int main(int argc, char *argv[])
{

  //Debug
  std::ostringstream defines;
  defines << "#define VERBOSE" << "\n";

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




  unsigned int nElem = size[0]*size[1];

  std::cout << "width : " << size[0] << std::endl;
  std::cout << "heigth : " << size[1] << std::endl;

  //
  // create GPU program object
  //
  itk::GPUKernelManager::Pointer kernelManager = itk::GPUKernelManager::New();

  // Pega o código do arquivo .cl 
  kernelManager->LoadProgramFromFile("/home/alexandrefreitas/Projetos/ITKProjects/itkGPUInverseImage/src/itkGPUInverseImage.cl", "#define PIXELTYPE float\n");


  //
  // create addition kernel
  //
  int kernel_inverse = kernelManager->CreateKernel("imageInverse2D");

  image->SetCurrentCommandQueue( 0 );
  outputImage->SetCurrentCommandQueue( 0 );
  kernelManager->SetCurrentCommandQueue( 0 );


  kernelManager->SetKernelArgWithImage(kernel_inverse, 0, image->GetGPUDataManager());
  kernelManager->SetKernelArgWithImage(kernel_inverse, 1, outputImage->GetGPUDataManager());
  kernelManager->SetKernelArg(kernel_inverse, 2, sizeof(unsigned int), &nElem);
  kernelManager->LaunchKernel2D(kernel_inverse, size[0], size[1], 16, 16);


//Converter imagem de float para unsigned char, para gerar imagem png
  typedef itk::CastImageFilter< ImageType, OutPutImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( outputImage );

  writer->SetInput( filter->GetOutput() );
  writer->Update();



  return EXIT_SUCCESS;
}

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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGPUNeighborhoodOperatorImageFilter.h"
#include "itkGPUMyNeighborhoodOperatorImageFilter.h"


#include "itkGPUImage.h"
#include "itkGPUKernelManager.h"
#include "itkGPUContextManager.h"
#include "itkGPUImageToImageFilter.h"


#include "itkTimeProbe.h"
#include "itkGaussianOperator.h"
#include "itkSobelOperator.h"
/**
 * Testing GPU Neighborhood Operator Image Filter
 */

template< unsigned int VImageDimension >
int runGPUNeighborhoodOperatorImageFilterTest(const std::string& inFile, const std::string& outFile)
{

  typedef unsigned char InputPixelType;
  typedef unsigned char OutputPixelType;

  typedef itk::GPUImage< InputPixelType,  VImageDimension >   InputImageType;
  typedef itk::GPUImage< OutputPixelType, VImageDimension >   OutputImageType;

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  typename ReaderType::Pointer reader = ReaderType::New();
  typename WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( inFile );
  writer->SetFileName( outFile );

  typedef itk::NumericTraits<OutputPixelType>::ValueType RealOutputPixelValueType;

  typedef itk::NeighborhoodOperatorImageFilter< InputImageType, OutputImageType > NeighborhoodFilterType;
  typedef itk::GPUNeighborhoodOperatorImageFilter< InputImageType, OutputImageType > GPUNeighborhoodFilterType;

  typedef itk::GPUMyNeighborhoodOperatorImageFilter< InputImageType, OutputImageType > GPUNeighborhoodFilterType2;

  // Create 1D Gaussian operator
  typedef itk::GaussianOperator< RealOutputPixelValueType, VImageDimension > OperatorType;

  OperatorType oper;
  oper.SetDirection(0);
  oper.SetVariance( 8 );
  oper.CreateDirectional();

  std::cout<<oper<<std::endl;

  // test 1~8 threads for CPU
  for(int nThreads = 1; nThreads <= 8; nThreads++)
  {
    typename NeighborhoodFilterType::Pointer CPUFilter = NeighborhoodFilterType::New();

    itk::TimeProbe cputimer;
    cputimer.Start();

    CPUFilter->SetNumberOfThreads( nThreads );

    CPUFilter->SetInput( reader->GetOutput() );
    CPUFilter->SetOperator( oper );
    CPUFilter->Update();

    cputimer.Stop();

    std::cout << "CPU NeighborhoodFilter took " << cputimer.GetMean() << " seconds with "
              << CPUFilter->GetNumberOfThreads() << " threads.\n" << std::endl;

    // -------

    if( nThreads == 8 )
    {
      typename GPUNeighborhoodFilterType2::Pointer GPUFilter = GPUNeighborhoodFilterType2::New();

      itk::TimeProbe gputimer;
      gputimer.Start();

      GPUFilter->SetInput( reader->GetOutput() );
      GPUFilter->SetOperator( oper );
      GPUFilter->Update();
      GPUFilter->GetOutput()->UpdateBuffers(); // synchronization point (GPU->CPU memcpy)

      gputimer.Stop();
      std::cout << "GPU NeighborhoodFilter took " << gputimer.GetMean() << " seconds.\n" << std::endl;
      writer->SetInput( GPUFilter->GetOutput() );
      writer->Update();

    }

  }

  return EXIT_SUCCESS;
}

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

  unsigned int dim = 3;
  if( argc >= 4 )
  {
    dim = atoi( argv[3] );
  }

  if( dim == 2 )
  {
    return runGPUNeighborhoodOperatorImageFilterTest<2>(inFile, outFile);
  }
  else if( dim == 3 )
  {
    return runGPUNeighborhoodOperatorImageFilterTest<3>(inFile, outFile);
  }
  else
  {
    std::cerr << "Error: only 2 or 3 dimensions allowed, " << dim << " selected." << std::endl;
    return EXIT_FAILURE;
  }
}

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
#ifndef __itkGPUMyMeanImageFilter_h
#define __itkGPUMyMeanImageFilter_h

#include "itkMeanImageFilter.h"
#include "itkGPUBoxImageFilter.h"
#include "itkVersion.h"
#include "itkObjectFactoryBase.h"
#include "itkOpenCLUtil.h"

namespace itk
{
/** \class GPUMyMeanImageFilter
 *
 * \brief GPU-enabled implementation of the MeanImageFilter.
 *
 * Current GPU mean filter reads in neighborhood pixels from global memory.
 *
 * \ingroup ITKGPUSmoothing
 */

/** Create a helper GPU Kernel class for GPUMyMeanImageFilter */
itkGPUKernelClassMacro(GPUMyMeanImageFilterKernel);

template< typename TInputImage, typename TOutputImage >
class GPUMyMeanImageFilter : public GPUBoxImageFilter< TInputImage, TOutputImage, MeanImageFilter< TInputImage, TOutputImage > >
{
public:
  /** Standard class typedefs. */
  typedef GPUMyMeanImageFilter                                                                               Self;
  typedef GPUImageToImageFilter< TInputImage, TOutputImage, MeanImageFilter< TInputImage, TOutputImage > > Superclass;
  typedef SmartPointer< Self >                                                                             Pointer;
  typedef SmartPointer< const Self >                                                                       ConstPointer;

  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(GPUMyMeanImageFilter, Superclass);

  /** Superclass typedefs. */
  typedef typename Superclass::OutputImageRegionType OutputImageRegionType;
  typedef typename Superclass::OutputImagePixelType  OutputImagePixelType;

  /** Some convenient typedefs. */
  typedef TInputImage                           InputImageType;
  typedef typename InputImageType::Pointer      InputImagePointer;
  typedef typename InputImageType::ConstPointer InputImageConstPointer;
  typedef typename InputImageType::RegionType   InputImageRegionType;
  typedef typename InputImageType::PixelType    InputImagePixelType;

  /** ImageDimension constants */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

  /** Get OpenCL Kernel source as a string, creates a GetOpenCLSource method */
  //itkGetOpenCLSourceFromKernelMacro(GPUMyMeanImageFilterKernel);

  void TestClass()
  {
    std::cout<<"Classe Ok"<<std::endl; 
  }

protected:
  GPUMyMeanImageFilter();
  ~GPUMyMeanImageFilter();

  virtual void PrintSelf(std::ostream & os, Indent indent) const;

  virtual void GPUGenerateData();

private:
  GPUMyMeanImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);     //purposely not implemented

  int m_MeanFilterGPUKernelHandle;
};

/** \class GPUMyMeanImageFilterFactory
 *
 * \brief Object Factory implemenatation for GPUMyMeanImageFilter
 * \ingroup ITKGPUSmoothing
 */
class GPUMyMeanImageFilterFactory : public ObjectFactoryBase
{
public:
  typedef GPUMyMeanImageFilterFactory Self;
  typedef ObjectFactoryBase         Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Class methods used to interface with the registered factories. */
  virtual const char* GetITKSourceVersion() const {
    return ITK_SOURCE_VERSION;
  }
  const char* GetDescription() const {
    return "A Factory for GPUMyMeanImageFilter";
  }

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(GPUMyMeanImageFilterFactory, itk::ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  {
    GPUMyMeanImageFilterFactory::Pointer factory = GPUMyMeanImageFilterFactory::New();

    ObjectFactoryBase::RegisterFactory(factory);
  }


private:
  GPUMyMeanImageFilterFactory(const Self&); //purposely not implemented
  void operator=(const Self&);            //purposely not implemented

#define OverrideMyMeanFilterTypeMacro(ipt,opt,dm) \
    { \
    typedef Image<ipt,dm> InputImageType; \
    typedef Image<opt,dm> OutputImageType; \
    this->RegisterOverride( \
      typeid(MeanImageFilter<InputImageType,OutputImageType>).name(), \
      typeid(GPUMyMeanImageFilter<InputImageType,OutputImageType>).name(), \
      "GPU Mean Image Filter Override", \
      true, \
      CreateObjectFunction<GPUMyMeanImageFilter<InputImageType,OutputImageType> >::New() ); \
    }

  GPUMyMeanImageFilterFactory()
  {
    if( IsGPUAvailable() )
      {
      OverrideMyMeanFilterTypeMacro(unsigned char, unsigned char, 1);
      OverrideMyMeanFilterTypeMacro(char, char, 1);
      OverrideMyMeanFilterTypeMacro(float,float,1);
      OverrideMyMeanFilterTypeMacro(int,int,1);
      OverrideMyMeanFilterTypeMacro(unsigned int,unsigned int,1);
      OverrideMyMeanFilterTypeMacro(double,double,1);

      OverrideMyMeanFilterTypeMacro(unsigned char, unsigned char, 2);
      OverrideMyMeanFilterTypeMacro(char, char, 2);
      OverrideMyMeanFilterTypeMacro(float,float,2);
      OverrideMyMeanFilterTypeMacro(int,int,2);
      OverrideMyMeanFilterTypeMacro(unsigned int,unsigned int,2);
      OverrideMyMeanFilterTypeMacro(double,double,2);

      OverrideMyMeanFilterTypeMacro(unsigned char, unsigned char, 3);
      OverrideMyMeanFilterTypeMacro(char, char, 3);
      OverrideMyMeanFilterTypeMacro(float,float,3);
      OverrideMyMeanFilterTypeMacro(int,int,3);
      OverrideMyMeanFilterTypeMacro(unsigned int,unsigned int,3);
      OverrideMyMeanFilterTypeMacro(double,double,3);
      }
  }

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkGPUMyMeanImageFilter.hxx"
#endif

#endif

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

# compile CXX with /usr/bin/c++
CXX_FLAGS =   -Wno-array-bounds -msse2 -I/home/alexandrefreitas/Projetos/ITKProjects/itkGPUSobel/bin/ITKIOFactoryRegistration -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Video/Filtering/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Video/IO/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Video/Core/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Registration/RegistrationMethodsv4/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Registration/Metricsv4/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/Optimizersv4/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/LevelSetsv4/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/Watersheds/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/Voronoi/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Bridge/VTK/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/SpatialFunction/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/RegionGrowing/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/QuadEdgeMeshFiltering/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/NeuralNetworks/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/MarkovRandomFieldsClassifiers/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/LabelVoting/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/KLMRegionGrowing/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageFusion/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/TransformMatlab/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/TransformInsightLegacy/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/TransformHDF5/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/TransformBase/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/RAW/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/MRC/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/HDF5/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/Siemens/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/GE/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/IPL/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/CSV/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/HDF5/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/HDF5/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/GPUThresholding/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/GPUSmoothing/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Registration/GPUPDEDeformable/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Registration/GPUCommon/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/GPUImageFilterBase/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/GPUAnisotropicSmoothing/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/GPUFiniteDifference/include -I/opt/AMDAPPSDK-2.9-1/include/CL -I/opt/AMDAPPSDK-2.9-1/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/GPUCommon/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/Mesh/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/GIFTI/src/gifticlib -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Registration/FEM/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Registration/PDEDeformable/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/FEM/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Registration/Common/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/SpatialObjects/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/XML/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/Eigen/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/DisplacementField/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/DiffusionTensorImage/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/Denoising/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/DeformableMesh/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/Deconvolution/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/DICOMParser/src/DICOMParser -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/DICOMParser/src/DICOMParser -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/Convolution/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/FFT/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/Colormap/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/Classifiers/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/BioCell/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/BiasCorrection/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/Polynomials/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/AntiAlias/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/LevelSets/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/SignedDistanceFunction/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/Optimizers/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageFeature/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageSources/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageGradient/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/Smoothing/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageCompare/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/FastMarching/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/QuadEdgeMesh/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/DistanceMap/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/NarrowBand/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/BinaryMathematicalMorphology/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/LabelMap/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/MathematicalMorphology/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Segmentation/ConnectedComponents/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/Thresholding/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageLabel/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageIntensity/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/Path/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageStatistics/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/SpatialObjects/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/Mesh/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageCompose/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/TestKernel/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/VTK/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/Stimulate/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/PNG/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/PNG/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/PNG/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/NRRD/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/NrrdIO/src/NrrdIO -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/NrrdIO/src/NrrdIO -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/NIFTI/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/NIFTI/src/nifti/znzlib -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/NIFTI/src/nifti/niftilib -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/Meta/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/MetaIO/src/MetaIO -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/MetaIO/src/MetaIO -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/LSM/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/TIFF/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/TIFF/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/TIFF/src/itktiff -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/TIFF/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/JPEG/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/JPEG/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/JPEG/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/GIPL/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/GDCM/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/GDCM/src/gdcm/Source/DataStructureAndEncodingDefinition -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/GDCM/src/gdcm/Source/MessageExchangeDefinition -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/GDCM/src/gdcm/Source/InformationObjectDefinition -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/GDCM/src/gdcm/Source/Common -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/GDCM/src/gdcm/Source/DataDictionary -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/GDCM/src/gdcm/Source/MediaStorageAndFileFormat -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/GDCM/src/gdcm/Source/Common -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/GDCM -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/ZLIB/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/ZLIB/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/OpenJPEG/src/openjpeg -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/OpenJPEG/src/openjpeg -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/Expat/src/expat -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/Expat/src/expat -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/BioRad/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/BMP/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/IO/ImageBase/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/IO/ImageBase -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/AnisotropicSmoothing/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageGrid/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/ImageFunction/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/Transform/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Numerics/Statistics/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/Netlib -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/ImageAdaptors/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/CurvatureFlow/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Filtering/ImageFilterBase/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/FiniteDifference/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/Core/Common/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/Core/Common -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/VNLInstantiation/include -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/VNL/src/vxl/core -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/VNL/src/vxl/vcl -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/VNL/src/vxl/v3p/netlib -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/VNL/src/vxl/core -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/VNL/src/vxl/vcl -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/VNL/src/vxl/v3p/netlib -I/home/alexandrefreitas/MestradoBibliotecas/ITK/bin/Modules/ThirdParty/KWSys/src -I/home/alexandrefreitas/MestradoBibliotecas/ITK/InsightToolkit-4.5.2/Modules/ThirdParty/DoubleConversion/src/double-conversion -I/home/alexandrefreitas/Projetos/ITKProjects/itkGPUSobel/src   

CXX_DEFINES = -DITK_IO_FACTORY_REGISTER_MANAGER


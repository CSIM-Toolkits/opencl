# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/bin

# Include any dependencies generated for this target.
include CMakeFiles/ItkGPU.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ItkGPU.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ItkGPU.dir/flags.make

CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o: CMakeFiles/ItkGPU.dir/flags.make
CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o: /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/src/itkGPUDiscreteGaussianImageFilterTest.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o -c /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/src/itkGPUDiscreteGaussianImageFilterTest.cxx

CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/src/itkGPUDiscreteGaussianImageFilterTest.cxx > CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.i

CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/src/itkGPUDiscreteGaussianImageFilterTest.cxx -o CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.s

CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.requires:
.PHONY : CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.requires

CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.provides: CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.requires
	$(MAKE) -f CMakeFiles/ItkGPU.dir/build.make CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.provides.build
.PHONY : CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.provides

CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.provides.build: CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o

# Object files for target ItkGPU
ItkGPU_OBJECTS = \
"CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o"

# External object files for target ItkGPU
ItkGPU_EXTERNAL_OBJECTS =

ItkGPU: CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o
ItkGPU: CMakeFiles/ItkGPU.dir/build.make
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkdouble-conversion-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitksys-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkvnl_algo-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkvnl-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkv3p_netlib-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKCommon-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkNetlibSlatec-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKStatistics-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOImageBase-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOBMP-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOBioRad-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKEXPAT-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkopenjpeg-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkzlib-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmDICT-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmMSFF-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOGDCM-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOGIPL-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkjpeg-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOJPEG-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitktiff-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOTIFF-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOLSM-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKMetaIO-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOMeta-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKznz-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKniftiio-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIONIFTI-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKNrrdIO-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIONRRD-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkpng-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOPNG-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOStimulate-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOVTK-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKMesh-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKSpatialObjects-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKPath-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKLabelMap-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKQuadEdgeMesh-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKOptimizers-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKPolynomials-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKBiasCorrection-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKBioCell-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKDICOMParser-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOXML-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOSpatialObjects-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKFEM-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKgiftiio-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOMesh-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUCommon-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUFiniteDifference-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUAnisotropicSmoothing-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUImageFilterBase-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUSmoothing-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUThresholding-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkhdf5_cpp-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkhdf5-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOCSV-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOIPL-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOGE-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOSiemens-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOHDF5-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOMRC-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOTransformBase-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOTransformHDF5-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOTransformInsightLegacy-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOTransformMatlab-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKKLMRegionGrowing-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKVTK-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKWatersheds-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKVideoCore-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKVideoIO-4.5.a
ItkGPU: /opt/AMDAPPSDK-2.9-1/lib/x86_64/libOpenCL.so.1
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmMSFF-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkopenjpeg-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmDICT-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmIOD-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmDSED-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmCommon-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmjpeg8-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmjpeg12-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmjpeg16-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkgdcmuuid-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOTIFF-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitktiff-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkjpeg-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKNrrdIO-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkpng-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKPolynomials-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOXML-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKMetaIO-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKOptimizers-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKgiftiio-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKEXPAT-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKniftiio-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKznz-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUFiniteDifference-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUImageFilterBase-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKGPUCommon-4.5.a
ItkGPU: /opt/AMDAPPSDK-2.9-1/lib/x86_64/libOpenCL.so.1
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOGE-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOIPL-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkhdf5_cpp-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkhdf5-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkzlib-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOTransformBase-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKSpatialObjects-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKMesh-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKPath-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKStatistics-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkNetlibSlatec-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKIOImageBase-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKVideoCore-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKCommon-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkdouble-conversion-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitksys-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libITKVNLInstantiation-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkvnl_algo-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkv3p_lsqr-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkvnl-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkvcl-4.5.a
ItkGPU: /home/alexandrefreitas/MestradoBibliotecas/ITK/bin/lib/libitkv3p_netlib-4.5.a
ItkGPU: CMakeFiles/ItkGPU.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ItkGPU"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ItkGPU.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ItkGPU.dir/build: ItkGPU
.PHONY : CMakeFiles/ItkGPU.dir/build

CMakeFiles/ItkGPU.dir/requires: CMakeFiles/ItkGPU.dir/itkGPUDiscreteGaussianImageFilterTest.o.requires
.PHONY : CMakeFiles/ItkGPU.dir/requires

CMakeFiles/ItkGPU.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ItkGPU.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ItkGPU.dir/clean

CMakeFiles/ItkGPU.dir/depend:
	cd /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/src /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/src /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/bin /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/bin /home/alexandrefreitas/Projetos/ITKProjects/itkGPUDiscreteGaussianImageFilterTest/bin/CMakeFiles/ItkGPU.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ItkGPU.dir/depend


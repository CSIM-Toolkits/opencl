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
CMAKE_SOURCE_DIR = /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/bin

# Include any dependencies generated for this target.
include CMakeFiles/ItkGPU.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ItkGPU.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ItkGPU.dir/flags.make

CMakeFiles/ItkGPU.dir/itkGPUAniso.o: CMakeFiles/ItkGPU.dir/flags.make
CMakeFiles/ItkGPU.dir/itkGPUAniso.o: /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/src/itkGPUAniso.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ItkGPU.dir/itkGPUAniso.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ItkGPU.dir/itkGPUAniso.o -c /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/src/itkGPUAniso.cxx

CMakeFiles/ItkGPU.dir/itkGPUAniso.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ItkGPU.dir/itkGPUAniso.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/src/itkGPUAniso.cxx > CMakeFiles/ItkGPU.dir/itkGPUAniso.i

CMakeFiles/ItkGPU.dir/itkGPUAniso.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ItkGPU.dir/itkGPUAniso.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/src/itkGPUAniso.cxx -o CMakeFiles/ItkGPU.dir/itkGPUAniso.s

CMakeFiles/ItkGPU.dir/itkGPUAniso.o.requires:
.PHONY : CMakeFiles/ItkGPU.dir/itkGPUAniso.o.requires

CMakeFiles/ItkGPU.dir/itkGPUAniso.o.provides: CMakeFiles/ItkGPU.dir/itkGPUAniso.o.requires
	$(MAKE) -f CMakeFiles/ItkGPU.dir/build.make CMakeFiles/ItkGPU.dir/itkGPUAniso.o.provides.build
.PHONY : CMakeFiles/ItkGPU.dir/itkGPUAniso.o.provides

CMakeFiles/ItkGPU.dir/itkGPUAniso.o.provides.build: CMakeFiles/ItkGPU.dir/itkGPUAniso.o

# Object files for target ItkGPU
ItkGPU_OBJECTS = \
"CMakeFiles/ItkGPU.dir/itkGPUAniso.o"

# External object files for target ItkGPU
ItkGPU_EXTERNAL_OBJECTS =

ItkGPU: CMakeFiles/ItkGPU.dir/itkGPUAniso.o
ItkGPU: CMakeFiles/ItkGPU.dir/build.make
ItkGPU: /usr/local/lib/libitkdouble-conversion-4.5.a
ItkGPU: /usr/local/lib/libitksys-4.5.a
ItkGPU: /usr/local/lib/libitkvnl_algo-4.5.a
ItkGPU: /usr/local/lib/libitkvnl-4.5.a
ItkGPU: /usr/local/lib/libitkv3p_netlib-4.5.a
ItkGPU: /usr/local/lib/libITKCommon-4.5.a
ItkGPU: /usr/local/lib/libitkNetlibSlatec-4.5.a
ItkGPU: /usr/local/lib/libITKStatistics-4.5.a
ItkGPU: /usr/local/lib/libITKIOImageBase-4.5.a
ItkGPU: /usr/local/lib/libITKIOBMP-4.5.a
ItkGPU: /usr/local/lib/libITKIOBioRad-4.5.a
ItkGPU: /usr/local/lib/libITKEXPAT-4.5.a
ItkGPU: /usr/local/lib/libitkopenjpeg-4.5.a
ItkGPU: /usr/local/lib/libitkzlib-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmDICT-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmMSFF-4.5.a
ItkGPU: /usr/local/lib/libITKIOGDCM-4.5.a
ItkGPU: /usr/local/lib/libITKIOGIPL-4.5.a
ItkGPU: /usr/local/lib/libitkjpeg-4.5.a
ItkGPU: /usr/local/lib/libITKIOJPEG-4.5.a
ItkGPU: /usr/local/lib/libitktiff-4.5.a
ItkGPU: /usr/local/lib/libITKIOTIFF-4.5.a
ItkGPU: /usr/local/lib/libITKIOLSM-4.5.a
ItkGPU: /usr/local/lib/libITKMetaIO-4.5.a
ItkGPU: /usr/local/lib/libITKIOMeta-4.5.a
ItkGPU: /usr/local/lib/libITKznz-4.5.a
ItkGPU: /usr/local/lib/libITKniftiio-4.5.a
ItkGPU: /usr/local/lib/libITKIONIFTI-4.5.a
ItkGPU: /usr/local/lib/libITKNrrdIO-4.5.a
ItkGPU: /usr/local/lib/libITKIONRRD-4.5.a
ItkGPU: /usr/local/lib/libitkpng-4.5.a
ItkGPU: /usr/local/lib/libITKIOPNG-4.5.a
ItkGPU: /usr/local/lib/libITKIOStimulate-4.5.a
ItkGPU: /usr/local/lib/libITKIOVTK-4.5.a
ItkGPU: /usr/local/lib/libITKMesh-4.5.a
ItkGPU: /usr/local/lib/libITKSpatialObjects-4.5.a
ItkGPU: /usr/local/lib/libITKPath-4.5.a
ItkGPU: /usr/local/lib/libITKLabelMap-4.5.a
ItkGPU: /usr/local/lib/libITKQuadEdgeMesh-4.5.a
ItkGPU: /usr/local/lib/libITKOptimizers-4.5.a
ItkGPU: /usr/local/lib/libITKPolynomials-4.5.a
ItkGPU: /usr/local/lib/libITKBiasCorrection-4.5.a
ItkGPU: /usr/local/lib/libITKBioCell-4.5.a
ItkGPU: /usr/local/lib/libITKDICOMParser-4.5.a
ItkGPU: /usr/local/lib/libITKIOXML-4.5.a
ItkGPU: /usr/local/lib/libITKIOSpatialObjects-4.5.a
ItkGPU: /usr/local/lib/libITKFEM-4.5.a
ItkGPU: /usr/local/lib/libITKgiftiio-4.5.a
ItkGPU: /usr/local/lib/libITKIOMesh-4.5.a
ItkGPU: /usr/local/lib/libitkhdf5_cpp-4.5.a
ItkGPU: /usr/local/lib/libitkhdf5-4.5.a
ItkGPU: /usr/local/lib/libITKIOCSV-4.5.a
ItkGPU: /usr/local/lib/libITKIOIPL-4.5.a
ItkGPU: /usr/local/lib/libITKIOGE-4.5.a
ItkGPU: /usr/local/lib/libITKIOSiemens-4.5.a
ItkGPU: /usr/local/lib/libITKIOHDF5-4.5.a
ItkGPU: /usr/local/lib/libITKIOMRC-4.5.a
ItkGPU: /usr/local/lib/libITKIOTransformBase-4.5.a
ItkGPU: /usr/local/lib/libITKIOTransformHDF5-4.5.a
ItkGPU: /usr/local/lib/libITKIOTransformInsightLegacy-4.5.a
ItkGPU: /usr/local/lib/libITKIOTransformMatlab-4.5.a
ItkGPU: /usr/local/lib/libITKKLMRegionGrowing-4.5.a
ItkGPU: /usr/local/lib/libITKVTK-4.5.a
ItkGPU: /usr/local/lib/libITKWatersheds-4.5.a
ItkGPU: /usr/local/lib/libITKVideoCore-4.5.a
ItkGPU: /usr/local/lib/libITKVideoIO-4.5.a
ItkGPU: /opt/AMDAPPSDK-2.9-1/lib/x86_64/libOpenCL.so.1
ItkGPU: /usr/local/lib/libitkgdcmMSFF-4.5.a
ItkGPU: /usr/local/lib/libitkopenjpeg-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmDICT-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmIOD-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmDSED-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmCommon-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmjpeg8-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmjpeg12-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmjpeg16-4.5.a
ItkGPU: /usr/local/lib/libitkgdcmuuid-4.5.a
ItkGPU: /usr/local/lib/libITKIOTIFF-4.5.a
ItkGPU: /usr/local/lib/libitktiff-4.5.a
ItkGPU: /usr/local/lib/libitkjpeg-4.5.a
ItkGPU: /usr/local/lib/libITKNrrdIO-4.5.a
ItkGPU: /usr/local/lib/libitkpng-4.5.a
ItkGPU: /usr/local/lib/libITKPolynomials-4.5.a
ItkGPU: /usr/local/lib/libITKIOXML-4.5.a
ItkGPU: /usr/local/lib/libITKMetaIO-4.5.a
ItkGPU: /usr/local/lib/libITKOptimizers-4.5.a
ItkGPU: /usr/local/lib/libITKgiftiio-4.5.a
ItkGPU: /usr/local/lib/libITKEXPAT-4.5.a
ItkGPU: /usr/local/lib/libITKniftiio-4.5.a
ItkGPU: /usr/local/lib/libITKznz-4.5.a
ItkGPU: /usr/local/lib/libITKIOGE-4.5.a
ItkGPU: /usr/local/lib/libITKIOIPL-4.5.a
ItkGPU: /usr/local/lib/libitkhdf5_cpp-4.5.a
ItkGPU: /usr/local/lib/libitkhdf5-4.5.a
ItkGPU: /usr/local/lib/libitkzlib-4.5.a
ItkGPU: /usr/local/lib/libITKIOTransformBase-4.5.a
ItkGPU: /usr/local/lib/libITKSpatialObjects-4.5.a
ItkGPU: /usr/local/lib/libITKMesh-4.5.a
ItkGPU: /usr/local/lib/libITKPath-4.5.a
ItkGPU: /usr/local/lib/libITKStatistics-4.5.a
ItkGPU: /usr/local/lib/libitkNetlibSlatec-4.5.a
ItkGPU: /usr/local/lib/libITKIOImageBase-4.5.a
ItkGPU: /usr/local/lib/libITKVideoCore-4.5.a
ItkGPU: /usr/local/lib/libITKCommon-4.5.a
ItkGPU: /usr/local/lib/libitkdouble-conversion-4.5.a
ItkGPU: /usr/local/lib/libitksys-4.5.a
ItkGPU: /usr/local/lib/libITKVNLInstantiation-4.5.a
ItkGPU: /usr/local/lib/libitkvnl_algo-4.5.a
ItkGPU: /usr/local/lib/libitkv3p_lsqr-4.5.a
ItkGPU: /usr/local/lib/libitkvnl-4.5.a
ItkGPU: /usr/local/lib/libitkvcl-4.5.a
ItkGPU: /usr/local/lib/libitkv3p_netlib-4.5.a
ItkGPU: CMakeFiles/ItkGPU.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ItkGPU"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ItkGPU.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ItkGPU.dir/build: ItkGPU
.PHONY : CMakeFiles/ItkGPU.dir/build

CMakeFiles/ItkGPU.dir/requires: CMakeFiles/ItkGPU.dir/itkGPUAniso.o.requires
.PHONY : CMakeFiles/ItkGPU.dir/requires

CMakeFiles/ItkGPU.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ItkGPU.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ItkGPU.dir/clean

CMakeFiles/ItkGPU.dir/depend:
	cd /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/src /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/src /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/bin /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/bin /home/alexandrefreitas/Projetos/ITKProjects/itkGPUAniso/bin/CMakeFiles/ItkGPU.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ItkGPU.dir/depend


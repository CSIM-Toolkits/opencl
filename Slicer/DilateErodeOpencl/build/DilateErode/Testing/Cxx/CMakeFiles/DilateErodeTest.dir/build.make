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
CMAKE_SOURCE_DIR = /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build

# Include any dependencies generated for this target.
include DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/depend.make

# Include the progress variables for this target.
include DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/progress.make

# Include the compile flags for this target's objects.
include DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/flags.make

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o: DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/flags.make
DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o: ../DilateErode/Testing/Cxx/DilateErodeTest.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o"
	cd /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o -c /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/Testing/Cxx/DilateErodeTest.cxx

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.i"
	cd /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/Testing/Cxx/DilateErodeTest.cxx > CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.i

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.s"
	cd /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/Testing/Cxx/DilateErodeTest.cxx -o CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.s

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.requires:
.PHONY : DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.requires

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.provides: DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.requires
	$(MAKE) -f DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/build.make DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.provides.build
.PHONY : DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.provides

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.provides.build: DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o

# Object files for target DilateErodeTest
DilateErodeTest_OBJECTS = \
"CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o"

# External object files for target DilateErodeTest
DilateErodeTest_EXTERNAL_OBJECTS =

DilateErode/Testing/Cxx/DilateErodeTest: DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o
DilateErode/Testing/Cxx/DilateErodeTest: DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/build.make
DilateErode/Testing/Cxx/DilateErodeTest: lib/Slicer-4.4/cli-modules/libDilateErodeLib.so
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/Slicer-build/bin/libITKFactoryRegistration.so
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKSpatialObjects-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKPath-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKMesh-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOJPEG-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOGDCM-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkgdcmMSFF-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkgdcmDICT-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkgdcmIOD-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkgdcmDSED-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkgdcmCommon-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKEXPAT-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkopenjpeg-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOBMP-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOLSM-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOTIFF-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitktiff-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkjpeg-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOPNG-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkpng-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOVTK-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOStimulate-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOBioRad-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOMeta-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKMetaIO-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOMRC-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIONIFTI-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKniftiio-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKznz-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIONRRD-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKNrrdIO-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOGIPL-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOTransformHDF5-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkhdf5_cpp-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkhdf5-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/zlib-install/lib/libzlib.a
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOTransformInsightLegacy-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOTransformMatlab-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOTransformBase-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKStatistics-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkNetlibSlatec-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIODCMTK-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOImageBase-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKCommon-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkdouble-conversion-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitksys-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKVNLInstantiation-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkvnl_algo-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkv3p_lsqr-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkvnl-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkvcl-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkv3p_netlib-4.6.so.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libi2d.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmjpeg.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libijg8.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libijg12.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libijg16.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmjpls.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libcharls.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmwlm.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmpstat.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmtls.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmsr.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmimage.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmdsig.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmqrdb.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmnet.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmrt.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmimgle.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libdcmdata.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/liboflog.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/DCMTK-build/lib/libofstd.so.3.6.1
DilateErode/Testing/Cxx/DilateErodeTest: DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable DilateErodeTest"
	cd /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DilateErodeTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/build: DilateErode/Testing/Cxx/DilateErodeTest
.PHONY : DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/build

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/requires: DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DilateErodeTest.cxx.o.requires
.PHONY : DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/requires

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/clean:
	cd /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx && $(CMAKE_COMMAND) -P CMakeFiles/DilateErodeTest.dir/cmake_clean.cmake
.PHONY : DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/clean

DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/depend:
	cd /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/Testing/Cxx /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : DilateErode/Testing/Cxx/CMakeFiles/DilateErodeTest.dir/depend


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
CMAKE_SOURCE_DIR = /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build

# Include any dependencies generated for this target.
include MeanFilter/CMakeFiles/MeanFilterLib.dir/depend.make

# Include the progress variables for this target.
include MeanFilter/CMakeFiles/MeanFilterLib.dir/progress.make

# Include the compile flags for this target's objects.
include MeanFilter/CMakeFiles/MeanFilterLib.dir/flags.make

MeanFilter/MeanFilterCLP.h: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/SlicerExecutionModel-build/GenerateCLP/bin/GenerateCLPLauncher
MeanFilter/MeanFilterCLP.h: ../MeanFilter/MeanFilter.xml
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating MeanFilterCLP.h"
	cd /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter && /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/SlicerExecutionModel-build/GenerateCLP/bin/GenerateCLPLauncher --InputXML /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/MeanFilter/MeanFilter.xml --OutputCxx /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter/MeanFilterCLP.h

MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o: MeanFilter/CMakeFiles/MeanFilterLib.dir/flags.make
MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o: ../MeanFilter/MeanFilter.cxx
MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o: MeanFilter/MeanFilterCLP.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o"
	cd /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o -c /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/MeanFilter/MeanFilter.cxx

MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.i"
	cd /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/MeanFilter/MeanFilter.cxx > CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.i

MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.s"
	cd /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/MeanFilter/MeanFilter.cxx -o CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.s

MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.requires:
.PHONY : MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.requires

MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.provides: MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.requires
	$(MAKE) -f MeanFilter/CMakeFiles/MeanFilterLib.dir/build.make MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.provides.build
.PHONY : MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.provides

MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.provides.build: MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o

# Object files for target MeanFilterLib
MeanFilterLib_OBJECTS = \
"CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o"

# External object files for target MeanFilterLib
MeanFilterLib_EXTERNAL_OBJECTS =

lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: MeanFilter/CMakeFiles/MeanFilterLib.dir/build.make
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKIOImageBase-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKStatistics-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkNetlibSlatec-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /opt/AMDAPPSDK-2.9-1/lib/x86_64/libOpenCL.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKCommon-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkdouble-conversion-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitksys-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libITKVNLInstantiation-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkvnl_algo-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkv3p_lsqr-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkvnl-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkvcl-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/ITKv4-build/lib/libitkv3p_netlib-4.6.so.1
lib/Slicer-4.4/cli-modules/libMeanFilterLib.so: MeanFilter/CMakeFiles/MeanFilterLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../lib/Slicer-4.4/cli-modules/libMeanFilterLib.so"
	cd /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MeanFilterLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MeanFilter/CMakeFiles/MeanFilterLib.dir/build: lib/Slicer-4.4/cli-modules/libMeanFilterLib.so
.PHONY : MeanFilter/CMakeFiles/MeanFilterLib.dir/build

MeanFilter/CMakeFiles/MeanFilterLib.dir/requires: MeanFilter/CMakeFiles/MeanFilterLib.dir/MeanFilter.cxx.o.requires
.PHONY : MeanFilter/CMakeFiles/MeanFilterLib.dir/requires

MeanFilter/CMakeFiles/MeanFilterLib.dir/clean:
	cd /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter && $(CMAKE_COMMAND) -P CMakeFiles/MeanFilterLib.dir/cmake_clean.cmake
.PHONY : MeanFilter/CMakeFiles/MeanFilterLib.dir/clean

MeanFilter/CMakeFiles/MeanFilterLib.dir/depend: MeanFilter/MeanFilterCLP.h
	cd /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/MeanFilter /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter /home/alexandrefreitas/Projetos/Slicer/MeanFilterOpencl/build/MeanFilter/CMakeFiles/MeanFilterLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MeanFilter/CMakeFiles/MeanFilterLib.dir/depend


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

# Utility rule file for Nightly.

# Include the progress variables for this target.
include CMakeFiles/Nightly.dir/progress.make

CMakeFiles/Nightly:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Build and test extension"
	/usr/bin/ctest -C Debug -DCTEST_BUILD_CONFIGURATION:STRING=Debug -DCTEST_MODEL:STRING=Nightly -DSCRIPT_ARGS_FILE:FILEPATH=/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErodeOpencl-test-command-args.cmake -S /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-r23774/Extensions/CMake/SlicerBlockBuildPackageAndUploadExtension.cmake -VV

Nightly: CMakeFiles/Nightly
Nightly: CMakeFiles/Nightly.dir/build.make
.PHONY : Nightly

# Rule to build all files generated by this target.
CMakeFiles/Nightly.dir/build: Nightly
.PHONY : CMakeFiles/Nightly.dir/build

CMakeFiles/Nightly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Nightly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Nightly.dir/clean

CMakeFiles/Nightly.dir/depend:
	cd /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/CMakeFiles/Nightly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Nightly.dir/depend


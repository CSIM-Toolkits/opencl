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
CMAKE_SOURCE_DIR = /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build

# Utility rule file for Experimental.

# Include the progress variables for this target.
include CMakeFiles/Experimental.dir/progress.make

CMakeFiles/Experimental:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Build and test extension"
	/usr/bin/ctest -C Debug -DCTEST_BUILD_CONFIGURATION:STRING=Debug -DCTEST_MODEL:STRING=Experimental -DSCRIPT_ARGS_FILE:FILEPATH=/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/SobelFilterOpenCL-test-command-args.cmake -S /home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-r23774/Extensions/CMake/SlicerBlockBuildPackageAndUploadExtension.cmake -VV

Experimental: CMakeFiles/Experimental
Experimental: CMakeFiles/Experimental.dir/build.make
.PHONY : Experimental

# Rule to build all files generated by this target.
CMakeFiles/Experimental.dir/build: Experimental
.PHONY : CMakeFiles/Experimental.dir/build

CMakeFiles/Experimental.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Experimental.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Experimental.dir/clean

CMakeFiles/Experimental.dir/depend:
	cd /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/CMakeFiles/Experimental.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Experimental.dir/depend


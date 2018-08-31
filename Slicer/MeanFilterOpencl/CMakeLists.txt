cmake_minimum_required(VERSION 2.8.9)

project(MeanFilterOpencl)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://www.example.com/Slicer/Extensions/MeanFilterOpencl")
set(EXTENSION_CATEGORY "OpenclExamples")
set(EXTENSION_CONTRIBUTORS "Alexandre (Duarte)")
set(EXTENSION_DESCRIPTION "This is an example of a simple extension of mean filter using opencl library")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/MeanFilterOpencl.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/MeanFilterOpencl/Screenshots/1.png")

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(MeanFilter)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})

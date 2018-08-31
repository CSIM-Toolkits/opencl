cmake_minimum_required(VERSION 2.8.9)

project(SobelFilterOpenCL)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://www.example.com/Slicer/Extensions/SobelFilterOpenCL")
set(EXTENSION_CATEGORY "OpenCL")
set(EXTENSION_CONTRIBUTORS "John Doe (AnyWare Corp.)")
set(EXTENSION_DESCRIPTION "This is an example of a simple extension")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/SobelFilterOpenCL.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/SobelFilterOpenCL/Screenshots/1.png")

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(SobelFilterOpenCL)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})

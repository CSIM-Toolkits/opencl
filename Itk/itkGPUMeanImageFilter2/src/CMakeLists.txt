# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 2.4)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()


# This project is designed to be built outside the Insight source tree.
project(ItkGPU)


#Find Opencl
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(OpenCL REQUIRED)

include_directories(${OPENCL_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})


# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ItkGPU itkGPUMeanImageFilter.cxx )

target_link_libraries(ItkGPU ${ITK_LIBRARIES} ${OPENCL_LIBRARIES})




MESSAGE(STATUS "CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR} )
MESSAGE(STATUS "CMAKE_BINARY_DIR:" ${CMAKE_SOURCE_DIR} )
MESSAGE(STATUS "OpenCL found: ${OPENCL_FOUND}")
MESSAGE(STATUS "OpenCL includes: ${OPENCL_INCLUDE_DIRS}")
MESSAGE(STATUS "OpenCL libraries: ${OPENCL_LIBRARIES}")

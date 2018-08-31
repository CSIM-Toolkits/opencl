
#-----------------------------------------------------------------------------
set(MODULE_NAME SobelFilterOpenCL)

#-----------------------------------------------------------------------------

#
# SlicerExecutionModel
#
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

#
# ITK
#
set(${PROJECT_NAME}_ITK_COMPONENTS
  ITKIOImageBase
  ITKSmoothing
  )
find_package(ITK 4.6 COMPONENTS ${${PROJECT_NAME}_ITK_COMPONENTS} REQUIRED)
set(ITK_NO_IO_FACTORY_REGISTER_MANAGER 1) # See Libs/ITKFactoryRegistration/CMakeLists.txt
include(${ITK_USE_FILE})



#Opencl
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/SobelFilterOpenCL)

find_package(OpenCL REQUIRED)

option(VERBOSE "VERBOSE" ON)
if(VERBOSE)
  MESSAGE(STATUS "VERBOSE OPTION: " ${VERBOSE} )
  add_definitions(-DVERBOSE)
endif()


MESSAGE(STATUS "CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR} )
MESSAGE(STATUS "OpenCL found: ${OPENCL_FOUND}")
MESSAGE(STATUS "OpenCL includes: ${OPENCL_INCLUDE_DIRS}")
MESSAGE(STATUS "OpenCL libraries: ${OPENCL_LIBRARIES}")


#-----------------------------------------------------------------------------
set(MODULE_INCLUDE_DIRECTORIES ${OPENCL_INCLUDE_DIRS}
  )

set(MODULE_SRCS
  )

set(MODULE_TARGET_LIBRARIES
 ${ITK_LIBRARIES} ${OPENCL_LIBRARIES}
  )

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  INCLUDE_DIRECTORIES ${MODULE_INCLUDE_DIRECTORIES}
  ADDITIONAL_SRCS ${MODULE_SRCS}
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project (vtkDataSetReaders)

set(VTK_REQUIRED_COMPONENTS
	# Core components
	vtkRenderingCore
	vtkRenderingOpenGL
	vtkjsoncpp
	vtkCommonCore
	vtkInteractionStyle)

find_package(VTK NO_MODULE REQUIRED COMPONENTS ${VTK_REQUIRED_COMPONENTS})
find_package(libLAS)

include(${libLAS_INCLUDE_DIRS})
include(${VTK_USE_FILE})

set (SOURCES
	 main.cpp
	 vtkGeoJSONReader.cxx
	 vtkGeoJSONReader.h
	 vtkGeoJSONFeature.cxx
	 vtkGeoJSONFeature.h
	 vtkLASReader.cxx
	 vtkLASReader.h)

include_directories(${libLAS_INCLUDE_DIRS})

add_executable(run ${SOURCES})
target_link_libraries(run ${VTK_LIBRARIES} ${libLAS_LIBRARIES})

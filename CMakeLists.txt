cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project ( geoJSONReader )

set(VTK_REQUIRED_COMPONENTS
  # Core components
  vtkRenderingCore
  vtkRenderingOpenGL
  vtkjsoncpp
  vtkCommonCore)

find_package(VTK NO_MODULE REQUIRED COMPONENTS ${VTK_REQUIRED_COMPONENTS})
include(${VTK_USE_FILE})

set (SOURCES
     main.cpp
     vtkGeoJSONReader.cxx
     vtkGeoJSONReader.h
     vtkGeoJSONFeature.cxx
     vtkGeoJSONFeature.h)

add_executable(run ${SOURCES})
target_link_libraries(run ${VTK_LIBRARIES})

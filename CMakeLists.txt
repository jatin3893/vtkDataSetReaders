cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project (vtkDataSetReaders)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(BUILD_SHARED_LIBS "Build vtkDataSetReaders with shared libraries" ON)

set(VTK_REQUIRED_COMPONENTS
	vtkjsoncpp
	vtkCommonCore
	vtkCommonExecutionModel
        vtkFiltersCore
)

option(BUILD_TESTING "Build test programs" ON)
option(BUILD_LAS "Build Lidar (LAS) reader (requires libLAS package" ON)
option(BUILD_POSTGRES "Build PostgresSQL reader (requires postgress package" ON)

if (BUILD_TESTING)
  list(APPEND VTK_REQUIRED_COMPONENTS
    vtkInteractionStyle
    vtkIOLegacy
    vtkRenderingCore
    vtkRenderingOpenGL
  )
endif()

if(BUILD_POSTGRES)
  list(APPEND VTK_REQUIRED_COMPONENTS vtkIOPostgreSQL)
endif()

find_package(VTK NO_MODULE REQUIRED COMPONENTS ${VTK_REQUIRED_COMPONENTS})
include(${VTK_USE_FILE})

set (SOURCES
	 vtkGeoJSONReader.cxx
	 vtkGeoJSONReader.h
	 vtkGeoJSONFeature.cxx
	 vtkGeoJSONFeature.h
)

set(libLAS_LIBRARIES "")
mark_as_advanced(FORCE libLAS_LIBRARIES)
if (BUILD_LAS)
  find_package(libLAS)
  include_directories(${libLAS_INCLUDE_DIRS})
  list(APPEND SOURCES vtkLASReader.h vtkLASReader.cxx)
endif()

if(BUILD_POSTGRES)
  list(APPEND SOURCES vtkPostgreSQLDatabase.h vtkPostgreSQLDatabase.cxx)
endif()


add_library(vtkDataSetReaders ${SOURCES})
target_link_libraries(vtkDataSetReaders ${VTK_LIBRARIES} ${libLAS_LIBRARIES})

add_subdirectory(Testing)


#add_executable(run main ${SOURCES})
#target_link_libraries(run ${VTK_LIBRARIES} ${libLAS_LIBRARIES})

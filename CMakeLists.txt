cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

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
    vtkRenderingCore
    vtkRenderingOpenGL
  )
endif()

if(BUILD_POSTGRES)
  list(APPEND VTK_REQUIRED_COMPONENTS vtkIOPostgreSQL)
endif()

if (BUILD_LAS)
  set(libLAS_LIBRARIES)
  mark_as_advanced(FORCE libLAS_LIBRARIES)
  find_package(libLAS)
  list(APPEND SOURCES vtkLASReader.h vtkLASReader.cxx)
endif()

find_package(VTK NO_MODULE REQUIRED COMPONENTS ${VTK_REQUIRED_COMPONENTS})
include(${VTK_USE_FILE})

# include export header modules so that we can easily control symbol exporting
# VTK Map is setup by default not to export symbols unless explicitly stated.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)


set (SOURCES
	  vtkGeoJSONReader.cxx
    vtkGeoJSONFeature.cxx
    )

set (HEADERS
    vtkGeoJSONReader.h
    vtkGeoJSONFeature.h
    ${CMAKE_CURRENT_BINARY_DIR}/vtkdatasetreaders_export.h
    )

if(BUILD_POSTGRES)
  list(APPEND SOURCES vtkPostgreSQLDatabase.cxx)
  list(APPEND HEADERS vtkPostgreSQLDatabase.h)
endif()

if (BUILD_LAS)
  list(APPEND SOURCES vtkLASReader.cxx)
  list(APPEND HEADERS vtkLASReader.h)
endif()

add_library(vtkDataSetReaders ${SOURCES})

target_link_libraries(vtkDataSetReaders
                      LINK_PUBLIC
                      ${VTK_LIBRARIES})

target_include_directories(vtkDataSetReaders
                           PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_LAS)
  target_link_libraries(vtkDataSetReaders LINK_PUBLIC ${libLAS_LIBRARIES} )

  #needs to be public since we include liblas headers in our headers
  target_include_directories(vtkDataSetReaders PUBLIC ${libLAS_INCLUDE_DIRS})
endif()

# On Mac OS X, set the directory included as part of the
# installed library's path. We only do this to libraries that we plan
# on installing
if (BUILD_SHARED_LIBS)
  set_target_properties(vtkDataSetReaders PROPERTIES
                        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")
else( )
  #explicitly enable fpic when building statically
  set_target_properties(vtkDataSetReaders PROPERTIES
                        POSITION_INDEPENDENT_CODE True
                        )
endif()

#setup export header
generate_export_header(vtkDataSetReaders)

#install all the headers and the library
install(TARGETS vtkDataSetReaders
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
install (FILES ${HEADERS} DESTINATION include)


if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()


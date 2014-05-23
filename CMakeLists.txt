cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)

set (VTK_DIR "Path To VTK Build Directory")

project ( geoJSONReader )

find_package(VTK REQUIRED)

include (${VTK_USE_FILE})

set (SOURCES main.cpp
                vtkgeojsonreader.cpp
                vtkgeojsonreader.h
                vtkgeojsonfeature.cpp
                vtkgeojsonfeature.h)

add_executable(run ${SOURCES})

target_link_libraries(run ${VTK_LIBRARIES})

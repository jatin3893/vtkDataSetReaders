cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)

set (VTK_DIR "/media/NewVolume/College_Files/Git_Repo/VTK_Kitware/BuildVTK/")
set (CMAKE_BUILD_TYPE "None")
set (CMAKE_INSTALL_PREFIX "/usr/local")

project ( geoJSONReader )

find_package(VTK REQUIRED)

include (${VTK_USE_FILE})

set (SOURCES main.cpp
                geoJSONReader.cpp
                geoJSONReader.h
                geoJSONReaderFeatures.h
                geoJSONReaderFeatures.cpp)

add_executable(run ${SOURCES})

target_link_libraries(run ${VTK_LIBRARIES})

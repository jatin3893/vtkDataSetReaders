include_directories(${CMAKE_SOURCE_DIR})

set (SOURCES
  TestGeoJSON
)
include_directories(${VTK_INCLUDE_DIRECTORIES})
add_executable(TestGeoJSON ${SOURCES})
target_link_libraries(TestGeoJSON vtkDataSetReaders ${VTK_LIBRARIES})

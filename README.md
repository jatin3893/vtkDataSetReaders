vtkGeoJSONReader
================

Extension for geoJSON Format Reader/Writer for VTK

About
================
The vtkGeoJSONReader filter reads a geoJSON file specification and converts it into vtk compatible datatypes like vtkPolyData.

Current implementation of the reader supports the following geoJSON geometries

-Point

-Multi Point

-Line String

-Multi Line String

-Polygon (Without holes)

-Multi Polygons (Without holes)



The implementation is based on VTK version 6. At present, it is not compatible with older versions of VTK.


More information about the geoJSON format can be obtained here:
http://geojson.org/


Sample geoJSON Formatted files for various countries can be found here:
https://github.com/johan/world.geo.json

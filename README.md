VTK geoJSON and LAS Data Set Readers
====================================

Extension for geoJSON and LIDAR data in LAS Format Reader/Writer for VTK

About
=====
The vtkGeoJSONReader filter reads a geoJSON file specification and converts it into vtk compatible datatypes like vtkPolyData.

Current implementation of the reader supports the following geoJSON geometries

-Point

-Multi Point

-Line String

-Multi Line String

-Polygon (Without holes)

-Multi Polygons (Without holes)



The implementation is based on VTK version 6. At present, it is not compatible with older versions of VTK.

Important URLs:
===============

More information about the geoJSON format can be obtained here:

http://geojson.org/


Sample geoJSON Formatted files for various countries can be found here:

https://github.com/johan/world.geo.json


Official libLAS Web Site:

http://www.liblas.org/


libLAS Git Repo:

https://github.com/libLAS/libLAS


LAS Specification:

http://www.asprs.org/a/society/committees/standards/LAS_1_4_r13.pdf

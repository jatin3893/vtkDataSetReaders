#ifndef GEOJSONREADERFEATURES_H
#define GEOJSONREADERFEATURES_H

#include <vtk_jsoncpp.h>
#include <vtkStdString.h>

#define POINT                   "Point"
#define MULTI_POINT             "MultiPoint"
#define LINE_STRING             "LineString"
#define MULTI_LINE_STRING       "MultiLineString"
#define POLYGON                 "Polygon"
#define MULTI_POLYGON           "MultiPolygon"
#define GEOMETRY_COLLECTION     "GeometryCollection"

class geoJSONReaderFeatures
{
public:
    geoJSONReaderFeatures(Json::Value root);
    void extractGeometry(Json::Value geometryObject);
    void extractProperties(Json::Value propertyObject);
private:
    bool isEqual(vtkStdString str1, vtkStdString str2);
};

#endif // GEOJSONREADERFEATURES_H

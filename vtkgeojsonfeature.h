#ifndef VTKGEOJSONFEATURE_H
#define VTKGEOJSONFEATURE_H

#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtk_jsoncpp.h>

#define POINT                   "Point"
#define MULTI_POINT             "MultiPoint"
#define LINE_STRING             "LineString"
#define MULTI_LINE_STRING       "MultiLineString"
#define POLYGON                 "Polygon"
#define MULTI_POLYGON           "MultiPolygon"
#define GEOMETRY_COLLECTION     "GeometryCollection"

class vtkGeoJSONFeature
{
public:
    vtkGeoJSONFeature();
    vtkPolyData *extractGeoJSONFeature(Json::Value root);
    vtkPolyData *GetOutput();

protected:
    vtkPolyData *outputData;

    vtkPolyData *extractGeoJSONFeatureGeometry(Json::Value root);
    double *extractPoint(Json::Value coordinates);
    vtkPoints *extractMultiPoint(Json::Value coordinates);
    vtkPolyData *extractLineString(Json::Value coordinates);
    vtkPolyData *extractMultiLineString(Json::Value coordinateArray);
    vtkPolyData *extractPolygon(Json::Value coordinate);
    vtkPolyData *extractMultiPolygon(Json::Value coordinateArray);
    bool isEqual(vtkStdString str1, vtkStdString str2);
};

#endif // VTKGEOJSONFEATURE_H

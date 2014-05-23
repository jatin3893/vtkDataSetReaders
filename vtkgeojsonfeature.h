#ifndef VTKGEOJSONFEATURE_H
#define VTKGEOJSONFEATURE_H

#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPolygon.h>
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
    vtkPolyData *extractPoint(Json::Value coordinates);
    vtkPolyData *extractMultiPoint(Json::Value coordinates);
    vtkPolyData *extractLineString(Json::Value coordinates);
    vtkPolyData *extractMultiLineString(Json::Value coordinateArray);
    vtkPolyData *extractPolygon(Json::Value coordinate);
    vtkPolyData *extractMultiPolygon(Json::Value coordinateArray);

    double *createPoint(Json::Value coordinates);

    bool isEqual(vtkStdString str1, vtkStdString str2);
};

#endif // VTKGEOJSONFEATURE_H

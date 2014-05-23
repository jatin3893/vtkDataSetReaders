#ifndef VTKGEOJSONFEATURE_H
#define VTKGEOJSONFEATURE_H

#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkLine.h>
#include <vtkPolygon.h>
#include <vtk_jsoncpp.h>

//Currently implemented geoJSON compatible Geometries
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

    //Extract the geometry and properties corresponding to the geoJSON feature stored at root
    vtkPolyData *extractGeoJSONFeature(Json::Value root);

    //Return the vtkPolyData corresponding to the geoJSON feature stord in featureRoot
    vtkPolyData *GetOutput();

protected:
    //vtkPolyData containing the polydata generated from the geoJSON feature
    vtkPolyData *outputData;

    //Json::Value featureRoot corresponds to the root of the geoJSON feature from which the geometry and properties are to be extracted
    Json::Value featureRoot;

    //Extract geoJSON geometry into vtkPolyData *
    vtkPolyData *extractGeoJSONFeatureGeometry(Json::Value root);

    //Extract geoJSON Point into vtkPolyData *
    vtkPolyData *extractPoint(Json::Value coordinates);

    //Extract geoJSON MultiPoint into vtkPolyData *
    vtkPolyData *extractMultiPoint(Json::Value coordinates);

    //Extract geoJSON Line String into vtkPolyData *
    vtkPolyData *extractLineString(Json::Value coordinates);

    //Extract geoJSON Multi Line String into vtkPolyData *
    vtkPolyData *extractMultiLineString(Json::Value coordinateArray);

    //Extract geoJSON Polygon into vtkPolyData *
    vtkPolyData *extractPolygon(Json::Value coordinate);

    //Extract geoJSON Multi Polygon into vtkPolyData *
    vtkPolyData *extractMultiPolygon(Json::Value coordinateArray);

    //Point[] from its JSON equivalent
    double *createPoint(Json::Value coordinates);

    //Case insensitive string comparison
    bool isEqual(vtkStdString str1, vtkStdString str2);
};

#endif // VTKGEOJSONFEATURE_H

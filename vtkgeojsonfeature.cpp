#include "vtkgeojsonfeature.h"

vtkGeoJSONFeature::vtkGeoJSONFeature()
{
}

vtkPoints *vtkGeoJSONFeature::extractMultiPoint(Json::Value coordinates)
{
    vtkPoints *points = vtkPoints::New();

    if(coordinates.isArray())
    {
        for(int i = 0; i < coordinates.size(); i++)
        {
            double *point = extractPoint(coordinates[i]);
            points->InsertNextPoint(point[0], point[1], point[2]);
        }
    }
    return points;
}

vtkPolyData *vtkGeoJSONFeature::GetOutput()
{
    return outputData;
}

double *vtkGeoJSONFeature::extractPoint(Json::Value coordinates)
{
    double *point = new double[3];
    if(coordinates.size() == 1)
    {
        Json::Value x = coordinates[0];
        point[0] = x.asDouble();
    }
    else if(coordinates.size() == 2)
    {
        Json::Value x = coordinates[0];
        Json::Value y = coordinates[1];
        point[0] = x.asDouble();
        point[1] = y.asDouble();
    }
    else if(coordinates.size() == 3)
    {
        Json::Value x = coordinates[0];
        Json::Value y = coordinates[1];
        Json::Value z = coordinates[2];
        point[0] = x.asDouble();
        point[1] = y.asDouble();
        point[2] = z.asDouble();
    }
    return point;
}
vtkPolyData *vtkGeoJSONFeature::extractLineString(Json::Value coordinates)
{
    return vtkPolyData::New();
}

vtkPolyData *vtkGeoJSONFeature::extractMultiLineString(Json::Value coordinateArray)
{
    return vtkPolyData::New();
}

vtkPolyData *vtkGeoJSONFeature::extractPolygon(Json::Value coordinate)
{
    return vtkPolyData::New();
}

vtkPolyData *vtkGeoJSONFeature::extractMultiPolygon(Json::Value coordinateArray)
{
    return vtkPolyData::New();
}

vtkPolyData *vtkGeoJSONFeature::extractGeoJSONFeature(Json::Value root)
{
    Json::Value type = root.get("type", -1);
    Json::Value geometry = root.get("geometry", -1);
    Json::Value properties = root.get("properties", -1);

    vtkPolyData *geometryPolyData = 0;

    if(isEqual(type.asString(), "feature"))
    {
        geometryPolyData = extractGeoJSONFeatureGeometry(geometry);
    }
    /*
     *Apply geometrical properties from "properties" on the polydata geometry.
    */
    return geometryPolyData;
}

vtkPolyData *vtkGeoJSONFeature::extractGeoJSONFeatureGeometry(Json::Value root)
{
    Json::Value type = root.get("type", -1);
    Json::Value coordinates = root.get("coordinates", -1);
    outputData = vtkPolyData::New();

    if(type.isString())
    {
        vtkStdString typeString = vtkStdString(type.asString());

        if(isEqual(typeString, POINT))
        {
            std::cout << "This is a Point!" << std::endl;
            double *point = extractPoint(coordinates);

            vtkPoints *points = vtkPoints::New();
            points->InsertNextPoint(point[0], point[1], point[2]);
            outputData->SetPoints(points);
        }
        else if(isEqual(typeString, MULTI_POINT))
        {
            std::cout << "This is a Multi Point!" << std::endl;
            vtkPoints *points = extractMultiPoint(coordinates);
            outputData->SetPoints(points);
        }
        else if(isEqual(typeString, LINE_STRING))
        {
            std::cout << "This is a Line String!" << std::endl;
            outputData = extractLineString(coordinates);
        }
        else if(isEqual(typeString, MULTI_LINE_STRING))
        {
            std::cout << "This is a Multi Line String!" << std::endl;
            outputData = extractMultiLineString(coordinates);
        }
        else if(isEqual(typeString, POLYGON))
        {
            std::cout << "This is a Polygon!" << std::endl;
            outputData = extractPolygon(coordinates);
        }
        else if(isEqual(typeString, MULTI_POLYGON))
        {
            std::cout << "This is a Multi Polygon";
            outputData = extractMultiPolygon(coordinates);
        }
        else if(isEqual(typeString, GEOMETRY_COLLECTION))
        {
            std::cout << "This is a Geometry Collection!" << std::endl;
            outputData = vtkPolyData::New();
        }
        else
        {
            std::cout << "This geometry ("<< typeString << ") has not been implemented yet";
            outputData = vtkPolyData::New();
        }
    }

}
bool vtkGeoJSONFeature::isEqual(vtkStdString str1, vtkStdString str2)
{
    if(str1.length() != str2.length())
        return false;

    int len = str1.length();
    for(int i = 0; i < len; i++)
    {
        if(str1[i] != str2[i] && str1[i] - 32 != str2[i] && str1[i] != str2[i] - 32)
            return false;
    }
    return true;
}

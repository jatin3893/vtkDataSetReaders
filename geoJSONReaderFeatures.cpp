#include "geoJSONReaderFeatures.h"


geoJSONReaderFeatures::geoJSONReaderFeatures(Json::Value root)
{
    Json::Value geometry = root.get("geometry", -1);
    Json::Value property = root.get("properties", -1);

    extractGeometry(geometry);
    extractProperties(property);
}


void geoJSONReaderFeatures::extractGeometry(Json::Value geometryObject)
{
    Json::Value type = geometryObject.get("type", -1);
    Json::Value coordinates = geometryObject.get("coordinates", -1);

    if(type.isString())
    {
        vtkStdString typeString = vtkStdString(type.asString());

        if(isEqual(typeString, POINT))
        {
            std::cout << "This is a Point!" << std::endl;
        }
        else if(isEqual(typeString, MULTI_POINT))
        {
            std::cout << "This is a Multi Point!" << std::endl;
        }
        else if(isEqual(typeString, LINE_STRING))
        {
            std::cout << "This is a Line String!" << std::endl;
        }
        else if(isEqual(typeString, MULTI_LINE_STRING))
        {
            std::cout << "This is a Multi Line String!" << std::endl;
        }
        else if(isEqual(typeString, POLYGON))
        {
            std::cout << "This is a Polygon!" << std::endl;
        }
        else if(isEqual(typeString, MULTI_POLYGON))
        {
            std::cout << "This is a Multi Polygon";
        }
        else if(isEqual(typeString, GEOMETRY_COLLECTION))
        {
            std::cout << "This is a Geometry Collection!" << std::endl;
        }
        else
        {
            std::cout << "This geometry ("<< typeString << ") has not been implemented yet";
        }
    }

}

void geoJSONReaderFeatures::extractProperties(Json::Value propertyObject)
{

}

bool geoJSONReaderFeatures::isEqual(vtkStdString str1, vtkStdString str2)
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

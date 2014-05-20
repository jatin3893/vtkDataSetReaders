#include <iostream>
#include <fstream>
#include "geoJSONReader.h"
using namespace std;
using namespace Json;
/*
 *type:
 *Feature Collection
 *Feature
 *Point
 *Line
 *LineString
 *Polygon
 *
 *MultiPoint
 *MultiPolygon
 *
*/
void parseObject(Json::Value root)
{
    if(root.isObject())
    {
        Json::Value::Members members = root.getMemberNames();
        for(int i = 0; i < members.size(); i++)
        {
            std::cout << 1 << members[i] << endl;
            Json::Value value = root[members[i]];
            parseObject(value);
        }
    }
    else if(root.isArray())
    {
        for(int i = 0; i < root.size(); i++)
        {
            Json::Value value = root[i];
            parseObject(value);
        }
    }
    else
    {
        if(root.isString())
            std::cout << 3 << root.asString() << endl;
        else if(root.isNumeric())
            std::cout << 3 << root.asFloat() << endl;
    }

}



int main(int argc, char **argv)
{
    ifstream file;
    file.open("test.json");
    if(!file.is_open())
    {
        std::cout << "File Not Opened!";
        return -1;
    }

    // Let's parse it
    Json::Value root;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(file, root, false);

    if(!parsedSuccess)
    {
        // Report failures and their locations in the document.
        cout<<"Failed to parse JSON" << endl << reader.getFormatedErrorMessages() << endl;
        return 1;
    }
    GeoJSONReader jsonReader;
    if(root.isObject())
    {
        //        parseObject(root);
        jsonReader.parseNow(root);
    }

    return 0;
}

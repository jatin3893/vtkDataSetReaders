#include "geoJSONReader.h"

GeoJSONReader::GeoJSONReader()
{
    featureCollection = vtkCollection::New();
}

vtkCollection *GeoJSONReader::parseNow(Json::Value root)
{
    Json::Value value = root.get("features", -1);

    if(value != -1)
    {
        if(value.isArray())
        {
            std::cout << "This is a feature Collection" << std::endl;
            for(int i = 0; i < value.size(); i++)
            {
                Json::Value child = value[i];
                geoJSONReaderFeatures *feature = new geoJSONReaderFeatures(child);
                /*
                 *Generate the feature for child using geoJSONReaderFeatures constructor.
                 *Then, add it to the vtkCollection list
                */
            }
        }
        else
        {
            /*
             *Generate the feature for child using geoJSONReaderFeatures constructor.
             *Then, add it to the vtkCollection list
            */
            geoJSONReaderFeatures *feature = new geoJSONReaderFeatures(value);

        }
    }
    else
    {
        std::cout << "Some error in format!";
        return NULL;
    }

    return featureCollection;
}

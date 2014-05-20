#ifndef VTK_GEOJSONREADER_H
#define VTK_GEOJSONREADER_H

#include <vtk_jsoncpp.h>
#include <vtkCollection.h>
#include "geoJSONReaderFeatures.h"

class GeoJSONReader
{
public:
	GeoJSONReader();
    vtkCollection *parseNow(Json::Value root);
    vtkCollection *featureCollection;

private:

};

#endif	//VTK_GEOJSONREADER_H

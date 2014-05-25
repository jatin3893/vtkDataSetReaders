#ifndef VTKGEOJSONREADER_H
#define VTKGEOJSONREADER_H

//Standard C++ Includes
#include <fstream>
#include <iostream>

//VTK Includes
#include <vtkStdString.h>
#include <vtkPolyData.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkSmartPointer.h>
#include <vtk_jsoncpp.h>
#include <vtkAlgorithm.h>
#include "vtkgeojsonfeature.h"

class vtkGeoJSONReader: public vtkAlgorithm
{
public:

    vtkGeoJSONReader();

    //Set filename for the geoJSON data source
    void SetFileName(const char *fileName);

    //Parse the data and update the outputData according to the geoJSON data in the source file
    void Update();

    //Deleting the current data. To Do.
    void Delete();

    //Get the outputData generated after Update() i.e. outputData containing vtkPolyData corresponding to the data in geoJSON fileName
    vtkPolyData *GetOutput();

protected:

    ifstream file;
    vtkStdString fileName;
    vtkPolyData *outputData;

    //Parse the Json Value corresponding to the root of the geoJSON data from the file
    void ParseRoot(Json::Value root);

    //Verify if file exists and can be read by the parser
    bool CanReadFile(const char *filename);

    void initialiseOutputData();

    //Destructor for the reader. To Do.
    ~vtkGeoJSONReader();

};

#endif // VTKGEOJSONREADER_H

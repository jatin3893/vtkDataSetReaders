#ifndef VTKGEOJSONREADER_H
#define VTKGEOJSONREADER_H

#include <vtkStdString.h>
#include <fstream>
#include <iostream>

#include <vtkPolyData.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkSmartPointer.h>
#include <vtk_jsoncpp.h>
#include <vtkAlgorithm.h>
#include "vtkgeojsonfeature.h"

using namespace std;

class vtkGeoJSONReader: public vtkAlgorithm
{
public:
    vtkGeoJSONReader();
    vtkPolyData *parseFile(vtkStdString filename);
    void SetFileName(const char *fileName);
    void Update();
    vtkPolyData *GetOutput();

protected:
    ifstream file;
    vtkStdString fileName;
    vtkPolyData *outputData;

    void ParseRoot(Json::Value root);
    bool CanReadFile(const char *filename);


};

#endif // VTKGEOJSONREADER_H

#ifndef __vtkLASReader_h
#define __vtkLASReader_h

// VTK Includes
#include <vtkPolyDataAlgorithm.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkObjectFactory.h>

//libLAS Includes
#include <liblas/liblas.hpp>

// C++ includes
#include <fstream>
#include <iostream>

class vtkLASReader: public vtkPolyDataAlgorithm
{
public:
  static vtkLASReader* New();
  vtkTypeMacro(vtkLASReader,vtkPolyDataAlgorithm)
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  // Decription:
  // All the Visualisation Types have been listed here
  enum VisualisationTypeConstants {
    None = 0,
    Color,
    Classification
  };

  // Description:
  // All the Classification Types according to LAS spec are listed here
  enum ClassificationTypeConstans {
    Created_NotClassified = 0,
    Unclassified,     // 1
    Ground,           // 2
    LowVegetation,    // 3
    MediumVegetation, // 4
    HighVegetation,   // 5
    Building,         // 6
    LowPoint,         // 7
    ModelKeyPoint,    // 8
    Water             // 9
  };

  // Decription:
  // Accessor for name of the file that will be opened
  vtkSetStringMacro(FileName)
  vtkGetStringMacro(FileName)

  // Decription:
  // Accessor for Visualisation Type
  vtkSetMacro(VisualisationType, VisualisationTypeConstants)
  vtkGetMacro(VisualisationType, VisualisationTypeConstants)

  // Decription:
  // Accessor for the LAS Header file
  vtkGetMacro(Header, liblas::Header *)

protected:
  vtkLASReader();
  virtual ~vtkLASReader();

  // Decription:
  // Core implementation of the data set reader
  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
                  vtkInformationVector* outputVector);

  // Description:
  // Read point record data i.e. position and visualisation data
  void ReadPointRecordData(liblas::Reader &reader, vtkPolyData* pointsPolyData);

  // Description:
  // Map from Class Number to Corresponding Color
  static unsigned char ClassificationColorMap[10][3];

  int pointRecordsCount;
  VisualisationTypeConstants VisualisationType;
  liblas::Header* Header;
  char* FileName;

private:
  vtkLASReader(const vtkLASReader&);  // Not implemented
  void operator=(const vtkLASReader&);    // Not implemented
};

// To Do:
// Option to change colouring scheme ( Colours in ClassificationColorMap )
// Look for better Visualisation Methods if possible?
// Ex: Converting it to a Polygon mesh?
//

#endif // __vtkLASReader_h

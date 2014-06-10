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
  // Constants
  enum VisualisationTypeConstants
  {
    NONE = 0,
    COLOR,
    CLASSIFICATION
  };

  enum ClassificationTypeConstans
  {
      UNCLASSIFIED = 0,
      GROUND,
      VEGETATION,
      WATER
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

  static unsigned char ClassificationColorMap[10][3];

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

  int pointRecordsCount;
  VisualisationTypeConstants VisualisationType;
  liblas::Header* Header;
  char* FileName;

private:
  vtkLASReader(const vtkLASReader&);  // Not implemented
  void operator=(const vtkLASReader&);    // Not implemented
};

#endif // __vtkLASReader_h

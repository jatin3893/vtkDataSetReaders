#ifndef __vtkLASReader_h
#define __vtkLASReader_h

// VTK Includes
#include <vtkPolyDataAlgorithm.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
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
  vtkTypeMacro(vtkLASReader,vtkPolyDataAlgorithm);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  // Decription:
  // Accessor for name of the file that will be opened
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  liblas::Header *GetHeader();

protected:
  vtkLASReader();
  virtual ~vtkLASReader();

  // Decription:
  // Core implementation of the data set reader
  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
                  vtkInformationVector* outputVector);

  int pointRecordsCount;
  liblas::Header *header;
  char *FileName;

private:
  vtkLASReader(const vtkLASReader&);  // Not implemented
  void operator=(const vtkLASReader&);    // Not implemented
};

#endif // __vtkLASReader_h

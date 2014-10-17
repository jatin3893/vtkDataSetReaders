/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkGeoJSONReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkGeoJSONReader - Convert Geo JSON format to vtkPolyData
// .SECTION Description
// Outputs a vtkPolyData from the input
// Geo JSON Data (http://www.geojson.org)

#ifndef __vtkGeoJSONReader_h
#define __vtkGeoJSONReader_h

// VTK Includes
#include "vtkPolyDataAlgorithm.h"
#include "vtk_jsoncpp.h" // For json parser

class vtkPolyData;

class vtkGeoJSONReader: public vtkPolyDataAlgorithm
{
public:
  static vtkGeoJSONReader* New();
  vtkTypeMacro(vtkGeoJSONReader,vtkPolyDataAlgorithm);
  virtual void PrintSelf(ostream &os, vtkIndent indent);

  // Decription:
  // Accessor for name of the file that will be opened on WriteData
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // String used as data input (instead of file) when StringInputMode is enabled
  vtkSetStringMacro(StringInput);
  vtkGetStringMacro(StringInput);

  // Description:
  // Set/get whether to use StringInput instead of reading input from file
  // The default is off
  vtkSetMacro(StringInputMode, bool);
  vtkGetMacro(StringInputMode, bool);
  vtkBooleanMacro(StringInputMode, bool);

protected:
  vtkGeoJSONReader();
  virtual ~vtkGeoJSONReader();

  // Decription:
  // Core implementation of the
  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
                  vtkInformationVector* outputVector);

  // Decription:
  // Parse the Json Value corresponding to the root of the geoJSON data from the file
  void ParseRoot(Json::Value root, vtkPolyData *output);

  // Decription:
  // Verify if file exists and can be read by the parser
  // If exists, parse into Jsoncpp data structure
  int CanParseFile(const char *filename, Json::Value &root);

  // Decription:
  // Verify if string can be read by the parser
  // If exists, parse into Jsoncpp data structure
  int CanParseString(char *input, Json::Value &root);

  char *FileName;
  char *StringInput;
  bool StringInputMode;

private:
  vtkGeoJSONReader(const vtkGeoJSONReader&);  // Not implemented
  void operator=(const vtkGeoJSONReader&);    // Not implemented
};

#endif // __vtkGeoJSONReader_h

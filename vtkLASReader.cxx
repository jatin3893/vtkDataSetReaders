#include "vtkLASReader.h"

vtkStandardNewMacro(vtkLASReader);

//----------------------------------------------------------------------------
vtkLASReader::vtkLASReader()
{
  this->FileName = NULL;
  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
}

//----------------------------------------------------------------------------
vtkLASReader::~vtkLASReader()
{
  delete[] FileName;
}

//----------------------------------------------------------------------------
int vtkLASReader::RequestData(vtkInformation* vtkNotUsed(request),
                                   vtkInformationVector** vtkNotUsed(request),
                                   vtkInformationVector* outputVector)
{
  // Get the info object
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  // Get the ouptut
  vtkPolyData* output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  // Open LAS File for reading
  std::ifstream ifs;
  ifs.open(FileName, std::ios_base::binary | std::ios_base::in);

  if (!ifs.is_open())
  {
  vtkErrorMacro (<< "Unable to open File for reading in binary mode");
  return VTK_ERROR;
  }

  // Read header data
  liblas::ReaderFactory readerFactory;
  liblas::Reader reader = readerFactory.CreateWithStream(ifs);
  header = new liblas::Header(reader.GetHeader());
  pointRecordsCount = header->GetPointRecordsCount();

  // Read point record data
  vtkPoints *points = vtkPoints::New();

  for ( int i= 0; i < pointRecordsCount && reader.ReadNextPoint(); i++)
  {
  liblas::Point const& p = reader.GetPoint();
  points->InsertNextPoint(p.GetX() * header->GetScaleX() * 2 + header->GetOffsetX(),
                          p.GetY() * header->GetScaleY() * 2 + header->GetOffsetY(),
                          p.GetZ() * header->GetScaleZ() * 2 + header->GetOffsetZ());
  }

  vtkPolyData *pointsPolyData = vtkPolyData::New();
  pointsPolyData->SetPoints(points);

  // Todo:
  // Add more options for reading based on properties, classification, intensity, etc.
  // as specified in the LAS specification.

  // Convert points to verts in output polydata
  vtkVertexGlyphFilter *vertexFilter = vtkVertexGlyphFilter::New();
  vertexFilter->SetInputData(pointsPolyData);
  vertexFilter->Update();
  output->ShallowCopy(vertexFilter->GetOutput());

  return VTK_OK;
}

//----------------------------------------------------------------------------
void vtkLASReader::PrintSelf(ostream &os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
  os << "vtkLASReader" << std::endl;
  os << "Filename: " << this->FileName << std::endl;
}

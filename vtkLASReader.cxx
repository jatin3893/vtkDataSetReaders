#include "vtkLASReader.h"

vtkStandardNewMacro(vtkLASReader)

//----------------------------------------------------------------------------
unsigned char vtkLASReader::ClassificationColorMap[][3] = {
    {  0,      0,      0},    //0     Created, Never Classified   Black
    {255,      0,      0},    //1     Unclassified                Red
    {145,    100,     45},    //2     Ground                      Brown
    {  0,    255,      0},    //3     Low Vegetation              Light Green
    {  0,    160,      0},    //4     Medium Vegetation           Medium Green
    {  0,     90,    255},    //5     High Vegetation             Dark Green
    {255,    255,      0},    //6     Building                    Yellow
    {255,    140,      0},    //7     Low Point                   Orange
    {255,      0,    255},    //8     Model Key-Point             Purple
    {  0,    255,    255},    //9     Water                       Blue
};

//----------------------------------------------------------------------------
vtkLASReader::vtkLASReader()
{
  this->FileName = NULL;
  this->pointRecordsCount = 0;
  this->VisualisationType = NONE;
  this->Header = NULL;

  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
}

//----------------------------------------------------------------------------
vtkLASReader::~vtkLASReader()
{
  if ( ! FileName )
    delete[] FileName;

  if ( ! Header )
    delete Header;
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

  if ( ! ifs.is_open() )
  {
  vtkErrorMacro (<< "Unable to open File for reading in binary mode");
  return VTK_ERROR;
  }

  // Read header data
  liblas::ReaderFactory readerFactory;
  liblas::Reader reader = readerFactory.CreateWithStream(ifs);
  Header = new liblas::Header(reader.GetHeader());
  pointRecordsCount = Header->GetPointRecordsCount();

  vtkPolyData* pointsPolyData = vtkPolyData::New();
  ReadPointRecordData(reader, pointsPolyData);

  // Convert points to verts in output polydata
  vtkVertexGlyphFilter* vertexFilter = vtkVertexGlyphFilter::New();
  vertexFilter->SetInputData(pointsPolyData);
  vertexFilter->Update();
  output->ShallowCopy(vertexFilter->GetOutput());

  return VTK_OK;
}

//----------------------------------------------------------------------------
void vtkLASReader::ReadPointRecordData(liblas::Reader &reader, vtkPolyData* pointsPolyData)
{
  vtkPoints* points = vtkPoints::New();
  vtkUnsignedCharArray* colors = vtkUnsignedCharArray::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");

  for ( int i= 0; i < pointRecordsCount && reader.ReadNextPoint(); i++)
  {
  liblas::Point const& p = reader.GetPoint();
  points->InsertNextPoint(p.GetX() * Header->GetScaleX() * 2 + Header->GetOffsetX(),
                        p.GetY() * Header->GetScaleY() * 2 + Header->GetOffsetY(),
                        p.GetZ() * Header->GetScaleZ() * 2 + Header->GetOffsetZ());

  // Todo:
  // Add more options for reading based on properties, classification, intensity, etc.
  // as specified in the LAS specification.

  unsigned char* color;
  switch(VisualisationType)
  {
  case NONE:
    break;

  case COLOR:
    color = new unsigned char[3];
    color[0] = p.GetColor().GetRed() / 256;
    color[1] = p.GetColor().GetGreen() / 256;
    color[2] = p.GetColor().GetBlue() / 256;
    colors->InsertNextTupleValue(color);
    break;

  case CLASSIFICATION:
    colors->InsertNextTupleValue( vtkLASReader::ClassificationColorMap[ p.GetClassification().GetClass() ] );
    break;

  default:
    break;
  }

  }

  pointsPolyData->SetPoints(points);

  if (VisualisationType)
  {
  pointsPolyData->GetPointData()->SetScalars(colors);
  }
}

//----------------------------------------------------------------------------
void vtkLASReader::PrintSelf(ostream &os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
  os << "vtkLASReader" << std::endl;
  os << "Filename: " << this->FileName << std::endl;
}

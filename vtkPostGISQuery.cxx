#include "vtkPostGISQuery.h"
#include <vtkObjectFactory.h>
#include "vtkPolyData.h"
#include "vtkGeoJSONReader.h"

vtkStandardNewMacro(vtkPostGISQuery);

//----------------------------------------------------------------------------
vtkPostGISQuery::vtkPostGISQuery()
{

}

//----------------------------------------------------------------------------
vtkPostGISQuery::~vtkPostGISQuery()
{

}

//----------------------------------------------------------------------------
void vtkPostGISQuery::PrintSelf(ostream &os, vtkIndent indent)
{

}

//----------------------------------------------------------------------------
vtkPolyData *vtkPostGISQuery::ToPolyData()
{
    int outputFormat = GetOutputDataFormat();

    switch(outputFormat)
    {
    case GeoJSON:
        GeoJSONToPolyData();
        break;
    default:
        break;
    }

    return outputPolyData;
}

//----------------------------------------------------------------------------
void vtkPostGISQuery::GeoJSONToPolyData()
{
  if(outputPolyData)
    outputPolyData->Delete();

  vtkGeoJSONReader *reader = vtkGeoJSONReader::New();
  reader->SetSource(vtkGeoJSONReader::ReadFromString);
  this->NextRow();
  reader->SetStringData(this->DataValue(0).ToString());
  reader->Update();

  outputPolyData = reader->GetOutput();
}

//----------------------------------------------------------------------------
int vtkPostGISQuery::GetOutputDataFormat()
{
    return GeoJSON;
}

//----------------------------------------------------------------------------
void vtkPostGISQuery::SetMyDatabase(vtkSQLDatabase *db)
{
    this->SetDatabase(db);
}

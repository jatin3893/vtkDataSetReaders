#ifndef __vtkPostGISQuery_h
#define __vtkPostGISQuery_h

#include <vtkPostgreSQLQuery.h>

#define GeoJSON 1

class vtkPolyData;

class vtkPostGISQuery : public vtkPostgreSQLQuery
{
public:
  static vtkPostGISQuery *New();
  virtual void PrintSelf(ostream &os, vtkIndent indent);
  vtkTypeMacro(vtkPostGISQuery,vtkPostgreSQLQuery)

  // Description:
  //
  vtkPolyData *ToPolyData();

  void SetMyDatabase(vtkSQLDatabase *db);

protected:
  vtkPostGISQuery();
  ~vtkPostGISQuery();

  // Description:
  //
  void GeoJSONToPolyData();

  // Description:
  //
  int GetOutputDataFormat();

  // Description:
  //
  vtkPolyData *outputPolyData;

private:
  vtkPostGISQuery(const vtkPostGISQuery&);  //Not implemented
  void operator=(const vtkPostGISQuery&); //Not implemented
};

#endif // __vtkPostGISQuery_h

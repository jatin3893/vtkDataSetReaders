#include "vtkgeojsonfeature.h"

vtkGeoJSONFeature::vtkGeoJSONFeature()
{
}

vtkPolyData *vtkGeoJSONFeature::GetOutput()
{
    //return the generated polyData after generating the combined polydata from the geoJSON features
    //Check if output data contains appropriate data and return values accordingly
    return outputData;
}

double *vtkGeoJSONFeature::createPoint(Json::Value coordinates)
{
    //Obtain the point in double[] format from its corresponding geoJSON format
    //Check if Coordinates corresponds to Point
    //Do isDouble before asDouble to prevent inconsistency
    //Probably check for float/int too

    double *point = new double[3];
    if(coordinates.size() == 1)
    {
        Json::Value x = coordinates[0];
        point[0] = x.asDouble();
    }
    else if(coordinates.size() == 2)
    {
        Json::Value x = coordinates[0];
        Json::Value y = coordinates[1];
        point[0] = x.asDouble();
        point[1] = y.asDouble();
    }
    else if(coordinates.size() == 3)
    {
        Json::Value x = coordinates[0];
        Json::Value y = coordinates[1];
        Json::Value z = coordinates[2];
        point[0] = x.asDouble();
        point[1] = y.asDouble();
        point[2] = z.asDouble();
    }
    return point;
}
vtkPolyData *vtkGeoJSONFeature::extractPoint(Json::Value coordinates)
{
    //Extract the point from geoJSON geometry and generate the corresponding vtkPolyData
    //Check if Coordinates corresponds to Single Point

    vtkPolyData *pointPolyData = vtkPolyData::New();
    double *point = createPoint(coordinates);

    const int PID_SIZE = 1;
    vtkIdType pid[PID_SIZE];

    vtkPoints *points = vtkPoints::New();
    pid[0] = points->InsertNextPoint(point);

    vtkCellArray *verts = vtkCellArray::New();
    verts->InsertNextCell(PID_SIZE, pid);

    pointPolyData->SetPoints(points);
    pointPolyData->SetVerts(verts);

    return pointPolyData;
}
vtkPolyData *vtkGeoJSONFeature::extractMultiPoint(Json::Value coordinates)
{
    //Extract multipple points from the geoJSON geometry and create the corresponding vtkPolyData
    //Check if Coordinates corresponds to Multi Points

    vtkPolyData *multiPointPolyData = vtkPolyData::New();

    if(coordinates.isArray())
    {
        vtkPoints *points = vtkPoints::New();
        vtkCellArray *verts = vtkCellArray::New();

        const int PID_SIZE = coordinates.size();
        vtkIdType pid[PID_SIZE];

        for(int i = 0; i < PID_SIZE; i++)
        {
            double *point = createPoint(coordinates[i]);
            pid[i] = points->InsertNextPoint(point);
        }
        verts->InsertNextCell(PID_SIZE, pid);

        multiPointPolyData->SetVerts(verts);
        multiPointPolyData->SetPoints(points);
    }
    return multiPointPolyData;
}
vtkPolyData *vtkGeoJSONFeature::extractLineString(Json::Value coordinates)
{
    //extract the line string from the geoJSON geometry and create the corresponding vtkPolyData
    //Check if Coordinates corresponds to Line String

    vtkPolyData *linesPolyData = vtkPolyData::New();
    vtkCellArray *lines = vtkCellArray::New();
    vtkPoints *points = vtkPoints::New();

    int LINE_COUNT = coordinates.size();

    double *start = createPoint(coordinates[0]);
    vtkIdType lineId[2];
    lineId[0] = points->InsertNextPoint(start);

    for(int i = 1; i < LINE_COUNT; i++)
    {
        double *end = createPoint(coordinates[i]);
        lineId[1] = points->InsertNextPoint(end);

        vtkLine *line = vtkLine::New();

        line->GetPointIds()->SetId(0, lineId[0]);
        line->GetPointIds()->SetId(1, lineId[1]);

        lines->InsertNextCell(line);

        start = end;
        lineId[0] = lineId[1];
    }

    linesPolyData->SetPoints(points);
    linesPolyData->SetLines(lines);

    return linesPolyData;
}
vtkPolyData *vtkGeoJSONFeature::extractMultiLineString(Json::Value coordinateArray)
{
    //Extract Multiple Line strings from the geoJSON Geometry and generate the corresponding vtkPolyData
    //Check if Coordinate Array corresponds to Multi Line String

    vtkAppendPolyData *appendPolyDataFilter = vtkAppendPolyData::New();
    int LINE_STRING_COUNT = coordinateArray.size();

    for(int i = 0; i < LINE_STRING_COUNT; i++)
    {
        vtkPolyData *lineStringPolyData = extractLineString(coordinateArray[i]);
        appendPolyDataFilter->AddInputData(lineStringPolyData);
    }

    vtkCleanPolyData *cleanPolyData = vtkCleanPolyData::New();
    cleanPolyData->SetInputConnection(appendPolyDataFilter->GetOutputPort());
    cleanPolyData->Update();

    return cleanPolyData->GetOutput();
}
vtkPolyData *vtkGeoJSONFeature::extractPolygon(Json::Value coordinate)
{
    //Extract the polygon from the geoJSON feature and generate the corresponding vtkPolyData
    //Check if Coordinate Array corresponds to Polygon

    bool POLYGON_WITH_HOLES = coordinate.size() > 1 ? true : false;

    vtkPolyData *exteriorPolygonPolyData = vtkPolyData::New();
    vtkPoints *points = vtkPoints::New();
    vtkPolygon *exteriorPoly = vtkPolygon::New();
    vtkCellArray *polys = vtkCellArray::New();

    //For exterior Polygon
    Json::Value exteriorPolygon = coordinate[0];

    int EXTERIOR_POLYGON_VERTEX_COUNT = exteriorPolygon.size() - 1;
    exteriorPoly->GetPointIds()->SetNumberOfIds(EXTERIOR_POLYGON_VERTEX_COUNT);

    for(int i = 0; i < EXTERIOR_POLYGON_VERTEX_COUNT; i++)
    {
        double *point = createPoint(exteriorPolygon[i]);
        vtkIdType id = points->InsertNextPoint(point);
        exteriorPoly->GetPointIds()->SetId(i, id);
    }
    polys->InsertNextCell(exteriorPoly);

    exteriorPolygonPolyData->SetPoints(points);
    exteriorPolygonPolyData->SetPolys(polys);

    if(!POLYGON_WITH_HOLES)
        return exteriorPolygonPolyData;

    //Modify polydata to support polygon with holes
    //Probably use delaunay triangulation to create polygon with holes

    return exteriorPolygonPolyData;
}
vtkPolyData *vtkGeoJSONFeature::extractMultiPolygon(Json::Value coordinateArray)
{
    //Extract the Multiple polygons from the geoJSON geometry and generate the vtkPolyData
    //Check if Coordinate Array corresponds to Multi Polygon

    vtkAppendPolyData *appendPolyDataFilter = vtkAppendPolyData::New();

    int POLYGON_COUNT = coordinateArray.size();

    for(int i = 0; i < POLYGON_COUNT; i++)
    {
        vtkPolyData *polygonPolyData = extractPolygon(coordinateArray[i]);
        appendPolyDataFilter->AddInputData(polygonPolyData);
    }

    vtkCleanPolyData *cleanPolyData = vtkCleanPolyData::New();
    cleanPolyData->SetInputConnection(appendPolyDataFilter->GetOutputPort());
    cleanPolyData->Update();

    return cleanPolyData->GetOutput();
}
vtkPolyData *vtkGeoJSONFeature::extractGeoJSONFeature(Json::Value root)
{
    //Extract the geometry and properties of a geoJSON feature and return the correspongsing vtkPolyData

    this->featureRoot = root;

    Json::Value type = root.get("type", -1);
    Json::Value geometry = root.get("geometry", -1);
    Json::Value properties = root.get("properties", -1);

    vtkPolyData *geometryPolyData = 0;

    if(isEqual(type.asString(), "feature"))
    {
        geometryPolyData = extractGeoJSONFeatureGeometry(geometry);
    }
    /*
     *Apply geometrical properties from "properties" on the polydata geometry.
    */
    return geometryPolyData;
}
vtkPolyData *vtkGeoJSONFeature::extractGeoJSONFeatureGeometry(Json::Value root)
{
    //Extract Geometry for a geoJSON Feature

    Json::Value type = root.get("type", -1);
    Json::Value coordinates = root.get("coordinates", -1);
    outputData = vtkPolyData::New();

    if(type.isString())
    {
        vtkStdString typeString = vtkStdString(type.asString());

        if(isEqual(typeString, POINT))
        {
            std::cout << "This is a Point!" << std::endl;
            outputData = extractPoint(coordinates);
        }
        else if(isEqual(typeString, MULTI_POINT))
        {
            std::cout << "This is a Multi Point!" << std::endl;
            outputData = extractMultiPoint(coordinates);
        }
        else if(isEqual(typeString, LINE_STRING))
        {
            std::cout << "This is a Line String!" << std::endl;
            outputData = extractLineString(coordinates);
        }
        else if(isEqual(typeString, MULTI_LINE_STRING))
        {
            std::cout << "This is a Multi Line String!" << std::endl;
            outputData = extractMultiLineString(coordinates);
        }
        else if(isEqual(typeString, POLYGON))
        {
            std::cout << "This is a Polygon!" << std::endl;
            outputData = extractPolygon(coordinates);
        }
        else if(isEqual(typeString, MULTI_POLYGON))
        {
            std::cout << "This is a Multi Polygon";
            outputData = extractMultiPolygon(coordinates);
        }
        else if(isEqual(typeString, GEOMETRY_COLLECTION))
        {
            std::cout << "This is a Geometry Collection!" << std::endl;
            outputData = vtkPolyData::New();
        }
        else
        {
            std::cout << "This geometry ("<< typeString << ") has not been implemented yet";
            outputData = vtkPolyData::New();
        }
    }

}

bool vtkGeoJSONFeature::isEqual(vtkStdString str1, vtkStdString str2)
{
    //Case Insensitive string comparison
    if(str1.length() != str2.length())
        return false;

    int len = str1.length();
    for(int i = 0; i < len; i++)
    {
        //Exact Match of characters or Capital - Small match or Small Capital match of alphabets
        if(str1[i] != str2[i] && str1[i] - 32 != str2[i] && str1[i] != str2[i] - 32)
            return false;
    }
    return true;
}

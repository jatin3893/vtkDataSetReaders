#include "vtkgeojsonreader.h"

vtkGeoJSONReader::vtkGeoJSONReader()
{
    outputData = NULL;
}
bool vtkGeoJSONReader::CanReadFile(const char *filename)
{
    //Check if file can be opened for reading
    file.open(filename);

    if(!file.is_open())
    {
        std::cout << "File Not Opened!";
        return false;
    }
    return true;
}
void vtkGeoJSONReader::SetFileName(const char *fileName)
{
    //Set filename for the source of the geoJSON data
    this->fileName = vtkStdString(fileName);
}
void vtkGeoJSONReader::Update()
{
    //Read data from the geoJSON file and update outputData with appropriate vtkPolyData generated according to the data in the source file

    if(!CanReadFile(this->fileName))
    {
        std::cout << "Unable to Open File in parseFile " << this->fileName << std::endl;
        return;
    }

    Json::Value root;
    Json::Reader reader;

    //parse the entire geoJSON data into the Json::Value root
    bool parsedSuccess = reader.parse(file, root, false);

    if(!parsedSuccess)
    {
        // Report failures and their locations in the document.
        cout<<"Failed to parse JSON" << endl << reader.getFormatedErrorMessages() << endl;
        return;
    }

    //If parsed successfully into Json parser Values and Arrays, then convert it into appropriate vtkPolyData
    if(root.isObject())
    {
        ParseRoot(root);
    }
}
void vtkGeoJSONReader::ParseRoot(Json::Value root)
{
    Json::Value rootType = root.get("type", -1);
    Json::Value rootFeatures = root.get("features", -1);

    if(rootFeatures == -1)
    {
        std::cout << "Parse Root :: Features :: -1" << std::endl;
        return;
    }

    //Initialising polyData to which data will be appended
    initialiseOutputData();

    if(rootFeatures.isArray())
    {
        //If it is a collection of features
        for(int i = 0; i < rootFeatures.size(); i++)
        {
            //Append extracted geometry to existing outputData
            Json::Value child = rootFeatures[i];
            vtkGeoJSONFeature *feature = new vtkGeoJSONFeature();
            feature->extractGeoJSONFeature(child, outputData);
        }
    }
    else
    {
        //Single feature in the geoJSON data
        vtkGeoJSONFeature *feature = new vtkGeoJSONFeature();
        feature->extractGeoJSONFeature(rootFeatures, outputData);
    }

}
void vtkGeoJSONReader::initialiseOutputData()
{
    if(outputData != NULL)
        outputData->Delete();//Cleaning previous data

    outputData = vtkPolyData::New();

    outputData->SetPoints(vtkPoints::New());//Initialising containers for points,
    outputData->SetVerts(vtkCellArray::New());//Vertices,
    outputData->SetLines(vtkCellArray::New());//Lines and
    outputData->SetPolys(vtkCellArray::New());//Polygons
}
vtkGeoJSONReader::~vtkGeoJSONReader()
{
    //To Do.
}
void vtkGeoJSONReader::Delete()
{
    //To Do.
    delete this;
}
vtkPolyData *vtkGeoJSONReader::GetOutput()
{
    //Return the outputData generated after parsing the data from the geoJSON source file
    return outputData;
}

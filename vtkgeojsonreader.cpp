#include "vtkgeojsonreader.h"

vtkGeoJSONReader::vtkGeoJSONReader()
{
}

bool vtkGeoJSONReader::CanReadFile(const char *filename)
{
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
    //Possible Memory problems
    this->fileName = fileName;
}

void vtkGeoJSONReader::Update()
{
    if(!CanReadFile(this->fileName))
    {
        std::cout << "Unable to Open File in parseFile " << this->fileName << std::endl;
    }

    Json::Value root;
    Json::Reader reader;

    bool parsedSuccess = reader.parse(file, root, false);

    if(!parsedSuccess)
    {
        // Report failures and their locations in the document.
        cout<<"Failed to parse JSON" << endl << reader.getFormatedErrorMessages() << endl;
        return;
    }

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

    if(rootFeatures.isArray())
    {
        vtkAppendPolyData *appendPolyDataFilter = vtkAppendPolyData::New();
        for(int i = 0; i < rootFeatures.size(); i++)
        {
            Json::Value child = rootFeatures[i];
            vtkGeoJSONFeature *feature = new vtkGeoJSONFeature();
            feature->extractGeoJSONFeature(child);
            appendPolyDataFilter->AddInputData(feature->GetOutput());
        }
        vtkCleanPolyData *cleanPolyData = vtkCleanPolyData::New();
        cleanPolyData->SetInputConnection(appendPolyDataFilter->GetOutputPort());
        cleanPolyData->Update();

        this->outputData = cleanPolyData->GetOutput();
    }
    else
    {
        vtkGeoJSONFeature *feature = new vtkGeoJSONFeature();
        feature->extractGeoJSONFeature(rootFeatures);
        outputData = feature->GetOutput();
    }
}

vtkPolyData *vtkGeoJSONReader::GetOutput()
{
    return outputData;
}

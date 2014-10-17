//VTK includes
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>

//Reader includes
#include "vtkGeoJSONReader.h"

#include <fstream>
#include <iostream>

int TestGeoJSON(int argc, char **argv);

int main(int argc, char **argv)
{
   return TestGeoJSON(argc, argv);
}

int TestGeoJSON(int argc, char **argv)
{
  if (argc < 2)
    {
    std::cout << "\n"
              << "Test vtkGeoJSONReader" << "\n"
              << "Usage  TestGeoJSON  input_file.json  [StringInputMode=0]"
              << std::endl;
    return -1;
    }

  //Reader
  vtkGeoJSONReader *reader = vtkGeoJSONReader::New();

  bool useStringInputMode = (argc > 2) && (argv[2] != "0");
  if (useStringInputMode)
    {
    std::cout << "Setting StringInputMode true" << std::endl;
    reader->StringInputModeOn();
    // Load source file
    std::ifstream in(argv[1], std::ios::in | std::ios::binary);
    if (in)
      {
      std::string content(std::istreambuf_iterator<char>(in.rdbuf()),
                          std::istreambuf_iterator<char>());
      in.close();
      reader->SetStringInput(content.c_str());
      }
    else
      {
      std::cerr << "Unable to open file " << argv[1] << std::endl;
      return -1;
      }
    }
  else
    {
    // Set source file
    reader->SetFileName(argv[1]);
    }

  //Read the output
  reader->Update();

  vtkPolyData *outputData = reader->GetOutput();

  //Visualise in a render window
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(outputData);

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

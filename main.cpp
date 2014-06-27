//VTK includes
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>

//Reader includes
#include "vtkGeoJSONReader.h"
#include "vtkLASReader.h"

int TestGeoJSON(int argc, char **argv);
int TestLASLidar(int argc, char **argv);

int main(int argc, char **argv)
{
//  return TestLASLidar(argc, argv);
   return TestGeoJSON(argc, argv);
}

int TestGeoJSON(int argc, char **argv)
{
  //Reader
  vtkGeoJSONReader *reader = vtkGeoJSONReader::New();

  //Select source file
  reader->SetFileName("JSONSample/india_outline.json");

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

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
int TestLASLidar(int argc, char **argv)
{
  //Reader
  vtkLASReader *reader = vtkLASReader::New();

  //Select source file
  reader->SetFileName("LASSample/test_1.las");
  reader->SetVisualisationType(vtkLASReader::Classification);

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

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

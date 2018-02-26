#include "stdafx.h"
//using namespace libZPlay;//Se declara que se usara la libreria de libZPlay para reproductor de musica

GameManager::GameManager(){
	hwnd = 0;
	CurrentScene = new Scene;
	Niveles.insert(std::pair<int, Scene>(0, *CurrentScene));
	CurrentSceneIndex = 0;
	RS = CurrentScene->CreateScene();
	if (RS != "S_OK")
		_RPT0(0,"No fue posible crear la escena");
	else
		_RPT0(0, "Scene Created!\n");
}

GameManager::~GameManager(){
}

string GameManager::FrameProcess()
{
	RS = CurrentScene->ProcessScene();
	if (RS != "S_OK")
		return ErrorFnc("Las actualizaciones y procesos de la escena tuvieron un error\n");
	else
		_RPT0(0, "Scene Calculated!\n");
	return "S_OK";
}

string GameManager::FrameRender()
{
	RS = CurrentScene->RenderScene();
	if (RS != "S_OK")
		return ErrorFnc("No fue poisble renderizar el frame\n");
	else
		_RPT0(0, "Scene Rendered!\n");
	return "S_OK";
}

string GameManager::AddScene(Scene newScene, int indexScene)
{
	if (Niveles.size() == 0)
		CurrentSceneIndex = 0;
	Niveles.insert(std::pair<int, Scene>(indexScene, newScene));
	return "S_OK";
}

Scene GameManager::GetCurrentScene()
{
	Scene Current = Niveles.find(CurrentSceneIndex)->second;
	return Current;
}

void GameManager::ChangeScene(int index)
{
	CurrentSceneIndex = index;
	Scene newCurrentScene = Niveles.find(index)->second;
	CurrentScene->DestroyScene();
	CurrentScene = &newCurrentScene;
	CurrentScene->CreateScene();
}

//Every object call  it's shutdown process
void GameManager::Shutdown()
{
	CurrentScene->DestroyScene();
	Niveles.clear();
	delete CurrentScene;
}

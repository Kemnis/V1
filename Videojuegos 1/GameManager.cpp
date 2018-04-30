#include "stdafx.h"
//using namespace libZPlay;//Se declara que se usara la libreria de libZPlay para reproductor de musica

GameManager::GameManager(){
	hwnd = 0;
	CurrentScene = new Scene("Escena #0: Prueba");
	Niveles.insert(std::pair<int, Scene*>(0, CurrentScene));
	CurrentSceneIndex = 0;
	RS = CurrentScene->CreateScene();
	RS = DefineNumberOfLevels();
	if (RS != "S_OK")
		_RPT0(0,"No fue posible crear la escena");
	else
		_RPT0(0, "Scene Template Created!\n");
}

GameManager::~GameManager(){
}

string GameManager::DefineNumberOfLevels()
{
	RS = AddScene(new SceneMenu("Escena #1: Menu"), 1);
	RS = AddScene(new SceneGameLevel1("Escena #2: Nivel 1"), 2);
	if (RS != "S_OK")
		_RPT0(0, "No fue posible crear los niveles");
	else
		_RPT0(0, "Game Levels Created!\n");
	return RS;
}

string GameManager::FrameProcess(double dt)
{
	RS = CurrentScene->ProcessScene(dt);
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

string GameManager::AddScene(Scene*newScene, int indexScene)
{
	if (Niveles.size() == 0)
		CurrentSceneIndex = 0;
	Niveles.insert(std::pair<int, Scene*>(indexScene, newScene));
	return "S_OK";
}

Scene* GameManager::GetCurrentScene()
{
	Scene*Current = Niveles.find(CurrentSceneIndex)->second;
	return Current;
}

int GameManager::GetCurrentIdScene()
{
	return CurrentSceneIndex;
}

void GameManager::ChangeScene(int index)
{
	CurrentSceneIndex = index;
	Scene* newCurrentScene = Niveles.find(index)->second;
	CurrentScene->DestroyScene();
	CurrentScene = newCurrentScene;
	CurrentScene->CreateScene();
}

bool GameManager::OnChangeScene(int oldScene, int newScene)
{

	return true;
}

void GameManager::Shutdown()
{
	CurrentScene->DestroyScene();
	Niveles.clear();
	delete CurrentScene;
}

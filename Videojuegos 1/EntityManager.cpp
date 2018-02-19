#include "stdafx.h"

EntityManager::EntityManager(SpecsDx* From, HWND hWnd) {
	CurrentScene = new Scene(From, hWnd);
	Niveles.insert(std::pair<int, Scene>(0, *CurrentScene));
	CurrentSceneIndex = 0;
}

EntityManager::~EntityManager() {}

string EntityManager::AddScene(Scene newScene, int indexScene)
{
	if (Niveles.size() == 0)
		CurrentSceneIndex = 0;
	Niveles.insert(std::pair<int, Scene>(indexScene, newScene));
	return "S_OK";
}

Scene EntityManager::GetCurrentScene()
{
	Scene Current= Niveles.find(CurrentSceneIndex)->second;
	return Current;
}

void EntityManager::ChangeScene(int index)
{
	CurrentSceneIndex = index;
	Scene newCurrentScene = Niveles.find(index)->second;
	CurrentScene->DestroyScene();
	CurrentScene = &newCurrentScene;
	CurrentScene->CreateScene();
}

string EntityManager::Start()
{
	RS = CurrentScene->CreateScene();
	if (RS != "S_OK")
		return Error("No fue posible crear la escena");
	else
		_RPT0(0, "Scene Created!\n");
	return "S_OK";
}

string EntityManager::Calculate()
{
	RS = CurrentScene->ProcessScene();
	if (RS != "S_OK")
		return Error("Las actualizaciones y procesos de la escena tuvieron un error\n");
	else
		_RPT0(0, "Scene Calculated!\n");
	return "S_OK";
}

string EntityManager::Run()
{
	RS = CurrentScene->RenderScene();
	if (RS != "S_OK")
		return Error("No fue poisble renderizar el frame\n");
	else
		_RPT0(0, "Scene Rendered!\n");
	return "S_OK";
}

void EntityManager::Shutdown()
{
	CurrentScene->DestroyScene();
	Niveles.clear();
	delete CurrentScene;
}
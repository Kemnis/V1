#pragma once
#ifndef _GameManager_H_
#define _GameManager_H_
#include <map>
#include "Camera3D.h"
#include "Mesh3D.h"
#include "ShaderClass.h"
#include "EntityManager.h"
#include "SpecsDx.h"
#include "Scene.h"
class GameManager
{
public:
	
	GameManager();
	~GameManager();
	virtual string Initialize();
	virtual string FrameProcess();
	virtual string FrameRender();
	string AddScene(Scene newScene, int indexScene);
	Scene GetCurrentScene();
	void ChangeScene(int index);
	virtual void Shutdown();

protected:
	//Variables de respuesta
	bool RB;
	string RS;
	// Variables de respuesta
		
	HWND hwnd;
	//Escenas
	std::map<int, Scene> Niveles;
	Scene* CurrentScene;
	int CurrentSceneIndex;

private:
};

#endif
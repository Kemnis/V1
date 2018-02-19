#pragma once
#ifndef _EntityManager_H_
#define _EntityManager_H_
#include <map>
#include "Camera3D.h"
#include "Mesh3D.h"
#include "Scene.h"
#include "SpecsDx.h"
#include "colorshaderclass.h"
class EntityManager
{
public:
	EntityManager(SpecsDx* From, HWND hWnd);
	~EntityManager();

	virtual string Start();
	virtual string Calculate();
	virtual string Run();
	void Shutdown();
	string AddScene(Scene newScene, int indexScene);
	Scene GetCurrentScene();
	void ChangeScene(int index);

protected:
	//Variables de respuesta
	bool RB;
	string RS;
	// Variables de respuesta

	std::map<int, Scene> Niveles;
	Scene* CurrentScene;
	int CurrentSceneIndex;
private:
};

#endif
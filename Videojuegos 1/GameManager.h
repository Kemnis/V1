#pragma once
#ifndef _GameManager_H_
#define _GameManager_H_
#include <map>
#include "Camera3D.h"
#include "Mesh3D.h"
#include "BasicShader.h"
#include "GameObject.h"
#include "SpecsDx.h"
#include "Scene.h"
class GameManager
{
public:
	
	GameManager();
	~GameManager();
	virtual string FrameProcess(double);
	virtual string FrameRender();
	string AddScene(Scene, int);
	Scene GetCurrentScene();
	void ChangeScene(int);
	virtual void Shutdown();
	string Name;
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
#pragma once
#ifndef _GameManager_H_
#define _GameManager_H_
#include "EntityManager.h"
#include "SpecsDx.h"
#include "Scene.h"
class GameManager
{
public:
	
	GameManager();
	~GameManager();
	virtual string StartEngine(int screenWidth, int screenHeight, HWND hWnd, char Mode);
	virtual string FrameProcess();
	virtual string FrameRender();
	virtual string InitEntity();
	virtual void Shutdown();

protected:
	//Variables de respuesta
	bool RB;
	string RS;
	// Variables de respuesta
		
	HWND hwnd;
	SpecsDx* Dx11 = 0;
	EntityManager* Entity;


private:
	

	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;
};

#endif
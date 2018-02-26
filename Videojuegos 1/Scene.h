#pragma once
#ifndef _Scene_H_
#define _Scene_H_
#include "Camera3D.h"
#include "Mesh3D.h"
#include "ShaderClass.h"
class Scene : DxComponent<Scene>
{
public:
	Scene();
	~Scene();

	virtual string CreateScene();
	virtual string ProcessScene();
	virtual string RenderScene();
	
	string NewGameObject(int , int , string );
	GameObject* GetGameObject(string);
	virtual void DestroyScene();

public:				//Descripci�n: Variables Globales
	Camera3D * SceneCamera;

protected:
	//Variables de respuesta
	bool RB;
	string RS;
	// Variables de respuesta
	
private:
	XMMATRIX CameraMatrix;
	

	Mesh3D* TestMesh3D;
	ShaderClass* TestShader;
};

#endif
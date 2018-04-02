#pragma once
#include "Camera3D.h"
#include "Mesh3D.h"
#include "Terrain.h"
class Scene : DxComponent<Scene>
{
public:
	Scene();
	~Scene();
	virtual string CreateScene();
	virtual string ProcessScene(double);
	virtual string RenderScene();
	
	virtual void DestroyScene();

public:				//Descripción: Variables Globales
	Camera3D * SceneCamera;
	Terrain* Stage1;
protected:
	//Variables de respuesta
	bool RB;
	string RS;
	// Variables de respuesta
	
private:
	XMMATRIX CameraMatrix;
	
};
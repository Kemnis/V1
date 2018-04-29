#pragma once
#include "Camera3D.h"
#include "Mesh3D.h"


class Scene :public DxComponent<Scene>
{
public:
	Scene();
	~Scene();
	virtual string CreateScene();
	virtual string ProcessScene(double dt);
	virtual string RenderScene();
	virtual string Start();
	virtual void DestroyScene();

public:				//Descripción: Variables Globales
	Camera3D * SceneCamera;
protected:
	//Variables de respuesta
	bool RB;
	string RS;
	// Variables de respuesta
	bool created;
	//vector<GameObject*> ListGameObjects;
private:
	XMMATRIX CameraMatrix;

	
};
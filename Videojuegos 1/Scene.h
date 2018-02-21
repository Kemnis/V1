#pragma once
#ifndef _Scene_H_
#define _Scene_H_
#include "Camera3D.h"
#include "Mesh3D.h"
#include "colorshaderclass.h"
class Scene : DxComponent<Scene>
{
public:
	Scene();
	~Scene();

	virtual void DefineCommonShader();
	virtual void AwakeObjects();
	virtual string CreateScene();
	virtual string ProcessScene();
	virtual string RenderScene();
	virtual void DestroyScene();

public:				//Descripción: Variables Globales
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
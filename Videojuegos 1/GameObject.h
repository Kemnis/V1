#pragma once
#ifndef _GameObject_H_
#define _GameObject_H_
#include "Model.h"
#include "Mesh3D.h"
#include "Texture.h"
#include "BasicShader.h"
class GameObject
{
public:
	GameObject(string);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model*);
	bool AssignMesh(Mesh3D*);
	bool AssignShader(BasicShader*);
	bool AssignTexture(Texture*);
	Mesh3D* GetMesh();
	Model* GetModel();
	Texture* GetTexture();
	BasicShader* GetShader();
	void Shutdown();	
	
	Transforms* Transform;
protected:
	
	string Name, Status;
	Model* Modelo;
	Mesh3D* Mesh;
	Texture* Tex;
	BasicShader* Shader;
private:
};

#endif
#pragma once
#ifndef _GameObject_H_
#define _GameObject_H_
#include "Model.h"
#include "Mesh3D.h"
#include "Texture.h"
#include "ShaderClass.h"
class GameObject
{
public:
	GameObject(string);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model*);
	bool AssignMesh(Mesh3D*);
	bool AssignShader(ShaderClass*);
	bool AssignTexture(Texture*);

	void Shutdown();	
	
protected:
	string Name;
	Model* Modelo;
	Mesh3D* Mesh;
	Texture* Tex;
	ShaderClass* Shader;
private:
};

#endif
#pragma once
#ifndef _GameObject_H_
#define _GameObject_H_
#include "Model.h"
#include "Texture.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
class GameObject
{
public:
	GameObject(string);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model*);
	bool AssignShader(BasicShader*);
	bool AssignMaterialShader();
	bool AssignMaterial(Material* mat);
	bool AssignTexture(Texture*);
	Model* GetModel();
	Texture* GetTexture();
	BasicShader* GetShader();
	Material* GetMaterial();
	void Shutdown();	
	
	Transforms* Transform;
protected:
	
	string Name, Status;
	Model* Modelo;
	Texture* Tex;
	BasicShader* Shader;
	MaterialShader* materialShader;
	Material* material;
private:
};

#endif
#pragma once
#ifndef _GameObject_H_
#define _GameObject_H_
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
class GameObject
{
public:
	GameObject(string);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model* model);
	bool AssignShader(Shader* shader);
	bool AssignMaterial(Material* mat);
	bool AssignTexture(Texture* texture);
	Model* GetModel();
	Texture* GetTexture();
	bool ExistShader();
	Material* GetMaterial();
	void Draw(XMMATRIX world, XMMATRIX view, XMMATRIX projection);
	void Shutdown();	
	
	Transforms* Transform;
protected:
	
	string Name, Status;
	Model* Modelo;
	Texture* Tex;
	Shader* shader;
	Material* material;
private:
};

#endif
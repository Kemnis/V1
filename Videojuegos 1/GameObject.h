#pragma once
#ifndef _GameObject_H_
#define _GameObject_H_
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
#include "Light.h"
class GameObject
{
public:
	GameObject(string);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model* model);
	bool AssignShader(Shader* shader);
	bool AssignMaterial(Material* mat);
	bool AssignLight(Light* light);
	bool AddTexture(Texture* texture);
	Model* GetModel();
	Light* GetLight();
	//Texture* GetTexture();
	bool ExistShader();
	Material* GetMaterial();
	void Draw(XMMATRIX world, XMMATRIX view, XMMATRIX projection);
	Shader* GetShader();
	void Shutdown();	
	
	Transforms* Transform;
protected:
	
	string Name, Status;
	Model* Modelo;
	std::vector<Texture*> Tex;
	Shader* shader;
	Material* material;
	Light* light;
private:
};

#endif
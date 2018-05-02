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
	GameObject(string Name);
	~GameObject();
	
	string GetName();
	bool AssignModel(Model* model);
	bool AssignShader(Shader* shader);
	bool AssignMaterial(Material* mat);
	bool AssignLight(Light* light);
	bool AddTexture(Texture* texture);
	void SetPosBitmap(vec2 Position);
	void SetEscBitmap(vec2 Escale);
	void SetPosBitmap(float PosX, float PosY);
	void SetEscBitmap(float EscX, float EscY);
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
	Model* Modelo;//Mesh
	std::vector<Texture*> Tex;
	Shader* shader;
	Material* material;
	Light* light;
private:
	
};

#endif
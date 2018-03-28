#include "stdafx.h"

GameObject::GameObject(string name)
{
	Transform = new Transforms();
	Name = name;
}

GameObject::~GameObject()
{
}

string GameObject::GetName()
{
	return Name;
}

bool GameObject::AssignModel(Model* model)
{
	Modelo = model;
	return true;
}

bool GameObject::AssignShader(BasicShader* shader)
{
	Shader = shader;
	return true;
}

bool GameObject::AssignMaterialShader()
{
	//Temporalmente no se usa la variable de referencia
	materialShader = ResourceManager::MatShader;
	return true;
}

bool GameObject::AssignMaterial(Material * mat)
{
	material = mat;
	return true;
}

bool GameObject::AssignTexture(Texture * texture)
{
	Tex = texture;
	return true;
}

void GameObject::Shutdown()
{
	delete Modelo;
	delete Tex;
	delete Shader;
	delete Transform;
}

Model* GameObject::GetModel()
{
	return Modelo;
}

Texture* GameObject::GetTexture()
{
	return Tex;
}

BasicShader* GameObject::GetShader()
{
	return Shader;
}

Material* GameObject::GetMaterial()
{
	return material;
}
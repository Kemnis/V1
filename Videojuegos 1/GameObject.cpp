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

bool GameObject::AssignMesh(Mesh3D* mesh)
{
	Mesh = mesh;
	return true;
}

bool GameObject::AssignShader(ShaderClass* shader)
{
	Shader = shader;
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
	delete Mesh;
	delete Tex;
	delete Shader;
	delete Transform;
}

Mesh3D* GameObject::GetMesh()
{
	return Mesh;
}

Model* GameObject::GetModel()
{
	return Modelo;
}

Texture* GameObject::GetTexture()
{
	return Tex;
}

ShaderClass* GameObject::GetShader()
{
	return Shader;
}

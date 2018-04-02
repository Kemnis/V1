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

bool GameObject::AssignBasicShader(BasicShader* basicshader)
{
	BShader = basicshader;
	return true;
}

bool GameObject::AssignMaterialShader(MaterialShader* materialshader)
{
	MShader = materialshader;
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
	delete BShader;
	delete MShader;
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

bool GameObject::ExistShader()
{
	if (BShader == nullptr && MShader == nullptr)
		return false;
	else
		return true;
}

Material* GameObject::GetMaterial()
{
	return material;
}

void GameObject::Draw(XMMATRIX world, XMMATRIX view, XMMATRIX projection)
{
	if (BShader != nullptr)
	{
		BShader->SetShaderParameters(world, view, projection, material);
		ResourceManager::bindBasicShader(BShader);
	}
	else if (MShader != nullptr)
	{
		MShader->SetShaderParameters(world, view, projection, Tex->GetTexture(), material);
		ResourceManager::bindMaterialShader(MShader);
	}
	ResourceManager::bindModel(Modelo);
	Modelo->Draw();
}
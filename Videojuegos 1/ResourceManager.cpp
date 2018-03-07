#include "ResourceManager.h"
#include "stdafx.h"
#include "GameObject.h"
#include "Model.h"
#include "Mesh3D.h"
#include "Texture.h"
#include "ShaderClass.h"
//Variables de respuesta
bool ResourceManager::RB = false;
string ResourceManager::RS = "";
// Variables de respuesta
ShaderClass* ResourceManager::ShaderActual = nullptr;
Mesh3D* ResourceManager::MeshActual = nullptr;
Model* ResourceManager::ModeloActual = nullptr;

ResourceManager::GameObjectMap ResourceManager::GameObjectIdentifier;
ResourceManager::ModelMap ResourceManager::ModelIdentifier;
ResourceManager::MeshMap ResourceManager::MeshIdentifier;
ResourceManager::TextureMap ResourceManager::TextureIdentifier;
ResourceManager::ShaderMap ResourceManager::ShaderIdentifier;
int ResourceManager::GameObjectIndex = 0;
int ResourceManager::ModelIndex = 0;
int ResourceManager::MeshIndex = 0;
int ResourceManager::TextureIndex = 0;
int ResourceManager::ShaderIndex = 0;
char ResourceManager::ChangeBinder = 0;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}
bool ResourceManager::AddGameObject(GameObject Gameobject)
{
	GameObjectIdentifier.insert(std::pair<string, GameObject>(Gameobject.GetName(), Gameobject));
	GameObjectIndex++;
	return true;
}

bool ResourceManager::AddModel(string path, string name)
{
	Model nuevo(path);
	nuevo.Name = name;
	ModelIdentifier.insert(std::pair<string, Model>(name, nuevo));
	ModelIndex++;
	return true;
}

void ResourceManager::AddMesh(string primitive, string name)
{
	Mesh3D nuevo;
	nuevo.Name = name;
	nuevo.Initialize(primitive);
	MeshIdentifier.insert(std::pair<string, Mesh3D>(name, nuevo));
	MeshIndex++;
}

bool ResourceManager::AddTexture(string path, string name)
{
	Texture nuevo;
	nuevo.Name = name;
	nuevo.Initialize(path);
	TextureIdentifier.insert(std::pair<string, Texture>(name, nuevo));
	TextureIndex++;
	return true;
}

string ResourceManager::BuildGameObject(string nameGameObject, string modelname, string meshname , string texturename , string shadername )
{
	GameObject nuevo(nameGameObject);
	if (modelname != "")
	{
		nuevo.AssignModel(&ModelIdentifier.find(modelname)->second);
		if (nuevo.GetModel() == nullptr)
			return "E_Fail";
	}
	if (meshname != "")
	{
		nuevo.AssignMesh(&MeshIdentifier.find(meshname)->second);
		if (nuevo.GetMesh() == nullptr)
			return "E_Fail";
	}
	if (texturename != "")
	{
		nuevo.AssignTexture(&TextureIdentifier.find(texturename)->second);
		if (nuevo.GetTexture() == nullptr)
			return "E_Fail";
	}
	if (shadername != "")
	{
		nuevo.AssignShader(&ShaderIdentifier.find(shadername)->second);
		if (nuevo.GetShader() == nullptr)
			return "E_Fail";
	}
	AddGameObject(nuevo);
	return "S_OK";
}

GameObject* ResourceManager::GetObjectByName(string nameSearch)
{
	return &GameObjectIdentifier.find(nameSearch)->second;
}

bool ResourceManager::AddShader()
{
	ShaderClass nuevo;
	nuevo.Name = "Shader";
	nuevo.Initialize();
	ShaderIdentifier.insert(std::pair<string, ShaderClass>("Shader", nuevo));
	TextureIndex++;
	return true;
}

bool ResourceManager::bindShader(GameObject * GO)
{
	if (ShaderActual != GO->GetShader())
	{
		GO->GetShader()->BindShader();
		ShaderActual = GO->GetShader();
		return true;
	}
	return false;
}

bool ResourceManager::bindMesh(Mesh3D * mesh)
{
	if (ChangeBinder == 0 || ChangeBinder == 'M')
	{
		if (MeshActual != mesh)
		{
			mesh->BindMesh();
			MeshActual = mesh;
			ChangeBinder = 'm';
			return true;
		}
		else
		{
			MeshActual->BindMesh();
			ChangeBinder = 'm';
			return true;
		}
	}
	return false;
}

bool ResourceManager::bindModel(GameObject * GO)
{
	if (ChangeBinder == 0 || ChangeBinder == 'm')
	{
		if (ModeloActual != GO->GetModel())
		{
			ModeloActual = GO->GetModel();
			ModeloActual->BindMesh();
			ChangeBinder = 'M';
			return true;
		}
		else
		{
			ModeloActual->BindMesh();
			ChangeBinder = 'M';
			return true;
		}
	}
	return false;
}

void ResourceManager::Shutdown()
{
	GameObjectIdentifier.clear();
	ModelIdentifier.clear();
	MeshIdentifier.clear();
	TextureIdentifier.clear();
	ShaderIdentifier.clear();
	ShaderActual = nullptr;
	MeshActual = nullptr;
	GameObjectIndex = 0;
	ModelIndex = 0;
	MeshIndex = 0;
	TextureIndex = 0;
	ShaderIndex = 0;
}
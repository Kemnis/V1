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
std::map<int, GameObject> ResourceManager::GameObjectIdentifier;
std::map<string, int> ResourceManager::GameObjectSearcher;
std::map<int, Model> ResourceManager::ModelIdentifier;
std::map<int, Mesh3D> ResourceManager::MeshIdentifier;
std::map<string, int> ResourceManager::MeshSearcher;
std::map<int, Texture> ResourceManager::TextureIdentifier;
std::map<int, ShaderClass> ResourceManager::ShaderIdentifier;
int ResourceManager::GameObjectIndex = 0;
int ResourceManager::ModelIndex = 0;
int ResourceManager::MeshIndex = 0;
int ResourceManager::TextureIndex = 0;
int ResourceManager::ShaderIndex = 0;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}
bool ResourceManager::AddGameObject(GameObject Gameobject)
{
	GameObjectIdentifier.insert(std::pair<int, GameObject>(GameObjectIndex, Gameobject));
	GameObjectSearcher.insert(std::pair<string, int>(Gameobject.GetName(), GameObjectIndex));
	GameObjectIndex++;
	return true;
}

bool ResourceManager::AddModel(string path, string name)
{
	Model nuevo(path);
	nuevo.Name = name;
	ModelIdentifier.insert(std::pair<int, Model>(ModelIndex, nuevo));
	ModelIndex++;
	return true;
}

void ResourceManager::AddMesh(string primitive, string name)
{
	Mesh3D nuevo;
	nuevo.Name = name;
	nuevo.Initialize(primitive);
	MeshIdentifier.insert(std::pair<int, Mesh3D>(MeshIndex, nuevo));
	MeshSearcher.insert(std::pair<string, int>(name, MeshIndex));
	MeshIndex++;
}

bool ResourceManager::AddTexture(string path, string name)
{
	Texture nuevo;
	nuevo.Name = name;
	//TextureIdentifier.insert(std::pair<int, Texture>(TextureIndex, texture));
	TextureIndex++;
	return true;
}

string ResourceManager::BuildGameObject(string nameGameObject, int modelindex=-1, int meshindex=-1, int textureindex=-1, int shaderindex=-1)
{
	GameObject nuevo(nameGameObject);
	if (modelindex != -1)
	{
		if (ModelIdentifier.size() >= modelindex)
		{
			nuevo.AssignModel(&ModelIdentifier.find(modelindex)->second);
		}
		else
			return "E_Fail";
	}
	if (meshindex != -1)
	{
		if (MeshIdentifier.size() >= meshindex)
		{
			nuevo.AssignMesh(&MeshIdentifier.find(meshindex)->second);
		}
		else
			return "E_Fail";
	}
	if (textureindex != -1)
	{
		if (TextureIdentifier.size() >= textureindex)
		{
			nuevo.AssignTexture(&TextureIdentifier.find(textureindex)->second);
		}
		else
			return "E_Fail";
	}
	if (shaderindex != -1)
	{
		if (ShaderIdentifier.size() >= shaderindex)
		{
			nuevo.AssignModel(&ModelIdentifier.find(modelindex)->second);
		}
		else
			return "E_Fail";
	}
	AddGameObject(nuevo);
	return "S_OK";
}

GameObject* ResourceManager::GetObjectByName(string nameSearch)
{
	int GOIndex = GameObjectSearcher.find(nameSearch)->second;
	return &GameObjectIdentifier.find(GOIndex)->second;
}

bool ResourceManager::AddShader()
{
	return false;
}

bool ResourceManager::bindShader(ShaderClass * shader)
{
	if (ShaderActual != shader)
	{
		shader->BindShader();
		ShaderActual = shader;
		return true;
	}
	return false;
}

bool ResourceManager::bindMesh(Mesh3D * mesh)
{
	if (MeshActual != mesh)
	{
		mesh->BindMesh();
		MeshActual = mesh;
		return true;
	}
	return false;
}

bool ResourceManager::bindMesh(GameObject * GO)
{
	if (MeshActual != GO->GetMesh())
	{
		Mesh3D* mesh = GO->GetMesh();
		mesh->BindMesh();
		MeshActual = mesh;
		return true;
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
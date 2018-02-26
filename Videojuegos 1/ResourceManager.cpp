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
	GameObjectIndex++;
	return true;
}

bool ResourceManager::AddModel(Model model)
{
	ModelIdentifier.insert(std::pair<int, Model>(ModelIndex, model));
	ModelIndex++;
	return true;
}

bool ResourceManager::AddMesh(Mesh3D mesh)
{
	MeshIdentifier.insert(std::pair<int, Mesh3D>(MeshIndex, mesh));
	MeshIndex++;
	return true;
}

bool ResourceManager::AddTexture(Texture texture)
{
	TextureIdentifier.insert(std::pair<int, Texture>(TextureIndex, texture));
	TextureIndex++;
	return true;
}

string ResourceManager::BuildGameObject(int modelindex, int textureindex, int shaderindex, string nameGameObject)
{
	GameObject nuevo(nameGameObject);
	if (ModelIdentifier.size() >= modelindex)
	{
		nuevo.AssignModel(&ModelIdentifier.find(modelindex)->second);
	}
	else
		return "E_Fail";
	if (TextureIdentifier.size() >= textureindex)
	{
		nuevo.AssignTexture(&TextureIdentifier.find(textureindex)->second);
	}
	else
		return "E_Fail";
	if (ShaderIdentifier.size() >= shaderindex)
	{
		nuevo.AssignModel(&ModelIdentifier.find(modelindex)->second);
	}
	else
		return "E_Fail";
	AddGameObject(nuevo);
	return "S_OK";
}

GameObject ResourceManager::GetObjectByName(string nameSearch)
{
	int GOIndex = GameObjectSearcher.find(nameSearch)->second;
	return GameObject(GameObjectIdentifier.find(GOIndex)->second);
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
	if (MeshActual = mesh)
	{
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
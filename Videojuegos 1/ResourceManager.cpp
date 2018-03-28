#include "ResourceManager.h"
#include "stdafx.h"
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
//Variables de respuesta
bool ResourceManager::RB = false;
string ResourceManager::RS = "";
// Variables de respuesta
BasicShader* ResourceManager::ShaderActual = nullptr;
Model* ResourceManager::ModeloActual = nullptr;

ResourceManager::GameObjectMap ResourceManager::GameObjectIdentifier;
ResourceManager::ModelMap ResourceManager::ModelIdentifier;
ResourceManager::TextureMap ResourceManager::TextureIdentifier;
ResourceManager::ShaderMap ResourceManager::ShaderIdentifier;
ResourceManager::MaterialMap ResourceManager::MaterialIdentifier;
int ResourceManager::GameObjectIndex = 0;
int ResourceManager::ModelIndex = 0;
int ResourceManager::TextureIndex = 0;
int ResourceManager::ShaderIndex = 0;
int ResourceManager::MaterialIndex = 0;
MaterialShader* ResourceManager::MatShader = 0;

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

bool ResourceManager::AddTexture(string path, string name)
{
	Texture nuevo;
	nuevo.Name = name;
	nuevo.Initialize(path);
	TextureIdentifier.insert(std::pair<string, Texture>(name, nuevo));
	TextureIndex++;
	return true;
}

string ResourceManager::BuildGameObject(string nameGameObject, string modelname, string texturename , string shadername, string materialname)
{
	GameObject nuevo(nameGameObject);
	if (modelname != "")
	{
		nuevo.AssignModel(&ModelIdentifier.find(modelname)->second);
		if (nuevo.GetModel() == nullptr)
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
		if (shadername == "Material")
		{
			nuevo.AssignMaterialShader();
		}
		else
		{
			nuevo.AssignShader(&ShaderIdentifier.find(shadername)->second);
			if (nuevo.GetShader() == nullptr)
				return "E_Fail";
		}
	}
	if (materialname != "")
	{
		nuevo.AssignMaterial(&MaterialIdentifier.find(materialname)->second);
		if(nuevo.GetMaterial() == nullptr)
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
	BasicShader nuevo;
	nuevo.Name = "Shader";
	nuevo.Initialize();
	ShaderIdentifier.insert(std::pair<string, BasicShader>("Shader", nuevo));
	ShaderIndex++;
	return true;
}

bool ResourceManager::AddMaterial(string Nombre, vec3 Color)
{
	Material nuevo;
	nuevo.Name = Nombre;
	nuevo.color = Color;
	MaterialIdentifier.insert(std::pair<string, Material>(Nombre, nuevo));
	MaterialIndex++;
	return true;
}

bool ResourceManager::InitMaterialshader()
{
	MatShader->Name = "MaterialShader";
	MatShader->Initialize();
	ShaderIndex++;
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

bool ResourceManager::bindModel(GameObject * GO)
{
	if (ModeloActual != GO->GetModel())
	{
		ModeloActual = GO->GetModel();
		return true;
	}
	return false;
}

void ResourceManager::Shutdown()
{
	GameObjectIdentifier.clear();
	ModelIdentifier.clear();
	TextureIdentifier.clear();
	ShaderIdentifier.clear();
	ShaderActual = nullptr;
	GameObjectIndex = 0;
	ModelIndex = 0;
	TextureIndex = 0;
	ShaderIndex = 0;
}
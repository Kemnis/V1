#include "ResourceManager.h"
#include "stdafx.h"
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
#include "KeyHandler.h"
//Variables de respuesta
bool ResourceManager::RB = false;
string ResourceManager::RS = "";
// Variables de respuesta
Shader* ResourceManager::ShaderActual = nullptr;
Model* ResourceManager::ModeloActual = nullptr;

ResourceManager::GameObjectMap ResourceManager::GameObjectIdentifier;
ResourceManager::ModelMap ResourceManager::ModelIdentifier;
ResourceManager::TextureMap ResourceManager::TextureIdentifier;
ResourceManager::ShaderMap ResourceManager::ShaderIdentifier;
ResourceManager::MaterialMap ResourceManager::MaterialIdentifier;
int ResourceManager::GameObjectIndex = 0;
int ResourceManager::ModelIndex = 0;
int ResourceManager::TextureIndex = 0;
int ResourceManager::MaterialIndex = 0;

//Informacion de la pantalla
int ResourceManager::ScreenWidthF = GetSystemMetrics(SM_CXSCREEN);
int ResourceManager::ScreenHeightF = GetSystemMetrics(SM_CYSCREEN);
int ResourceManager::ScreenWidth = 800;
int ResourceManager::ScreenHeight = 600;
KeyHandler* ResourceManager::Player1 = nullptr;

//Player1


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

bool ResourceManager::AddShader(string name, Shader* shader) {
	shader->Name = name;
	ShaderIdentifier.insert(std::pair<string, Shader*>(name, shader));
	return true;
}

bool ResourceManager::AddStage(string name, float Cells, float CellSize)
{
	Model nuevo(Cells, CellSize);
	nuevo.Name = name;
	ModelIdentifier.insert(std::pair<string, Model>(name, nuevo));
	ModelIndex++;
	return true;
}

string ResourceManager::BuildGameObject(string nameGameObject, string meshname, string texturename , string shadername, string materialname)
{
	GameObject nuevo(nameGameObject);
	if (meshname != "")
	{
		nuevo.AssignModel(&ModelIdentifier.find(meshname)->second);
		if (nuevo.GetModel() == nullptr)
			return "E_Fail";
	}
	if (texturename != "")
	{
		Texture* texture = &TextureIdentifier.find(texturename)->second;
		if (texture != nullptr) {
			nuevo.AddTexture(texture);
		}
	}
	if (shadername != "")
	{
		Shader* shader = ShaderIdentifier.find(shadername)->second;
		if (shader != nullptr) {
			nuevo.AssignShader(shader);
			if (nuevo.ExistShader() == false)
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

bool ResourceManager::AddMaterial(string Nombre, vec3 Color)
{
	Material nuevo;
	nuevo.Name = Nombre;
	nuevo.color = Color;
	MaterialIdentifier.insert(std::pair<string, Material>(Nombre, nuevo));
	MaterialIndex++;
	return true;
}

bool ResourceManager::bindShader(Shader * shader) {
	if (ShaderActual != shader)
	{
		shader->BindShader();
		ShaderActual = shader;
		return true;
	}
	return false;
}

bool ResourceManager::bindModel(Model * model)
{
	if (ModeloActual != model)
	{
		ModeloActual = model;
		ModeloActual->BindMesh(/*(ModeloActual->Type =="Terrain") ? D3D10_PRIMITIVE_TOPOLOGY_LINELIST :*/ D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
	GameObjectIndex = 0;
	ModelIndex = 0;
	TextureIndex = 0;
}

#include "ResourceManager.h"
#include "stdafx.h"
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
#include "Light.h"
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
ResourceManager::LightMap ResourceManager::LightIdentifier;
int ResourceManager::GameObjectIndex = 0;
int ResourceManager::ModelIndex = 0;
int ResourceManager::TextureIndex = 0;
int ResourceManager::MaterialIndex = 0;
int ResourceManager::LightIndex = 0;

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

//Add Objects
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

bool ResourceManager::AddStage(string HeightmapFile, string name, float Cells, float Width, float Height)
{
	Model nuevo(HeightmapFile,Cells, Width, Height);
	nuevo.Name = name;
	ModelIdentifier.insert(std::pair<string, Model>(name, nuevo));
	ModelIndex++;
	return true;
}

bool ResourceManager::AddBillboard(string Nombre, vec2 coordPositivo, vec2 coordNegativo)
{
	Model nuevo(coordPositivo, coordNegativo);
	nuevo.Name = Nombre;
	ModelIdentifier.insert(std::pair<string, Model>(Nombre, nuevo));
	ModelIndex++;
	return true;
}

bool ResourceManager::AddBitmap(string Nombre, vec4 rectBimap)
{
	Model nuevo(rectBimap,800,600);
	nuevo.Name = Nombre;
	ModelIdentifier.insert(std::pair<string, Model>(Nombre, nuevo));
	ModelIndex++;
	return true;
}

string ResourceManager::BuildGameObject(string nameGameObject, string meshname, string texturename , string shadername, string materialname, string lightname)
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

	if (lightname != "" || nuevo.GetShader()->flagLight == 1)
	{
		nuevo.AssignLight(&LightIdentifier.find(lightname)->second);
		if (nuevo.GetLight() == nullptr)
			return "E_Fail";
	}
	AddGameObject(nuevo);
	return "S_OK";
}

bool ResourceManager::AddMaterial(string Nombre, vec3 Color)
{
	Material nuevo;
	nuevo.Name = Nombre;
	nuevo.color = Color;
	nuevo.escalar = 0.0f;
	MaterialIdentifier.insert(std::pair<string, Material>(Nombre, nuevo));
	MaterialIndex++;
	return true;
}

bool ResourceManager::AddLight(string Nombre, vec4 ambient, vec4 diffuse, vec3 direction)
{
	Light nuevo;
	nuevo.Name = Nombre;
	nuevo.Ambient = ambient;
	nuevo.Diffuse = diffuse;
	//nuevo.Diffuse = diffuse;
	nuevo.Direction = direction;
	LightIdentifier.insert(std::pair<string, Light>(Nombre, nuevo));
	LightIndex++;
	return true;
}

string ResourceManager::AsingTextureToGameObject(string nameGameObject, string nameTexture)
{
	if (nameGameObject != "" && nameTexture != "")
	{
		Texture* texture = &TextureIdentifier.find(nameTexture)->second;
		GameObject* gameObject = ResourceManager::GetObjectByName(nameGameObject);
		if (texture == nullptr || gameObject == nullptr)
		{
			return "E_Fail";
		}
		gameObject->AddTexture(texture);
	}

	return "S_OK";
}

//Destory Objects

bool ResourceManager::DestroyAllModels() 
{
	for (ModelMap::iterator it = ModelIdentifier.begin(); it!= ModelIdentifier.end();++it)
	{

		it->second.ShutdownModel();
	}
	ModelIdentifier.clear();

	return true;
}

bool ResourceManager::DestoryAllMaterial()
{
	MaterialIdentifier.clear();
	return true;
}

bool ResourceManager::DestroyAllSahders()
{
	for (ShaderMap::iterator it = ShaderIdentifier.begin(); it != ShaderIdentifier.end(); ++it)
	{
		it->second->Shutdown();
	}
	ShaderIdentifier.clear();
	return true;
}
bool ResourceManager::DestroyAllGameObjects()
{
	GameObjectIdentifier.clear();
	return true;
}

bool ResourceManager::DestroyAllLight()
{
	LightIdentifier.clear();
	return true;
}

bool ResourceManager::DestroyAllTexture()
{
	for (TextureMap::iterator it = TextureIdentifier.begin(); it!=TextureIdentifier.end();++it)
	{
		it->second.Shutdown();
	}
	TextureIdentifier.clear();
	return true;
}

// Get Objects

GameObject* ResourceManager::GetObjectByName(string nameSearch)
{
	return &GameObjectIdentifier.find(nameSearch)->second;
}


Material*ResourceManager::GetMaterial(string nameMaterial)
{
	Material * material = &MaterialIdentifier.find(nameMaterial)->second;

	return material;
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
		ModeloActual->BindMesh(/*(ModeloActual->Type =="Terrain") ? D3D10_PRIMITIVE_TOPOLOGY_LINELIST : */D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

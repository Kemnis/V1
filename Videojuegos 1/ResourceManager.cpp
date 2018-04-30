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
Shader* ResourceManager::ShaderActual = nullptr;
Model* ResourceManager::ModeloActual = nullptr;

ResourceManager::GameObjectMap ResourceManager::GameObjectIdentifier;
ResourceManager::ModelMap ResourceManager::ModelIdentifier;
ResourceManager::TextureMap ResourceManager::TextureIdentifier;
ResourceManager::ShaderMap ResourceManager::ShaderIdentifier;
ResourceManager::MaterialMap ResourceManager::MaterialIdentifier;
ResourceManager::LightMap ResourceManager::LightIdentifier;
ResourceManager::GlobalResourcesMap ResourceManager::GlobalObjectsIdentifier;
int ResourceManager::GameObjectIndex = 0;
int ResourceManager::ModelIndex = 0;
int ResourceManager::TextureIndex = 0;
int ResourceManager::MaterialIndex = 0;
int ResourceManager::LightIndex = 0;
int ResourceManager::GlobalObjectsCounter = 0;

//Informacion de la pantalla
int ResourceManager::ScreenWidthF = GetSystemMetrics(SM_CXSCREEN);
int ResourceManager::ScreenHeightF = GetSystemMetrics(SM_CYSCREEN);
int ResourceManager::ScreenWidth = 800;
int ResourceManager::ScreenHeight = 600;
char ResourceManager::GraphicMode = 'W';

KeyHandler* ResourceManager::Player1 = nullptr;

//Player1


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

//Add Block
bool ResourceManager::AddGameObject(GameObject Gameobject, string idFrom)
{
	GameObjectIdentifier.insert(std::pair<string, GameObject>(Gameobject.GetName(), Gameobject));
	GameObjectIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = Gameobject.GetName();
	Info.Type = "GameObject";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddModel(string idFrom, string path, string name)
{
	Model nuevo(path);
	nuevo.Name = name;
	ModelIdentifier.insert(std::pair<string, Model>(name, nuevo));
	ModelIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = name;
	Info.Type = "Model";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddTexture(string idFrom, string path, string name)
{
	Texture nuevo;
	nuevo.Name = name;
	nuevo.Initialize(path);
	TextureIdentifier.insert(std::pair<string, Texture>(name, nuevo));
	TextureIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = name;
	Info.Type = "Texture";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddShader(string idFrom, string name, Shader* shader) {
	shader->Name = name;
	ShaderIdentifier.insert(std::pair<string, Shader*>(name, shader));
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = name;
	Info.Type = "Shader";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddStage(string idFrom, string HeightmapFile, string name, float Cells, float Width, float Height)
{
	Model nuevo(HeightmapFile,Cells, Width, Height);
	nuevo.Name = name;
	ModelIdentifier.insert(std::pair<string, Model>(name, nuevo));
	ModelIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = name;
	Info.Type = "Model";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddBillboard(string idFrom, string Nombre, vec2 coordPositivo, vec2 coordNegativo)
{
	Model nuevo(coordPositivo, coordNegativo);
	nuevo.Name = Nombre;
	ModelIdentifier.insert(std::pair<string, Model>(Nombre, nuevo));
	ModelIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = Nombre;
	Info.Type = "Model";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddBitmap(string idFrom, string Nombre, vec4 rectBimap)
{
	Model* nuevo;
	if (ResourceManager::GraphicMode == 'W')
		nuevo = new Model(rectBimap, ResourceManager::ScreenWidth, ResourceManager::ScreenHeight);
	else
		nuevo = new Model(rectBimap, ResourceManager::ScreenWidthF, ResourceManager::ScreenHeightF);
	nuevo->Name = Nombre;
	ModelIdentifier.insert(std::pair<string, Model>(Nombre, *nuevo));
	ModelIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = Nombre;
	Info.Type = "Model";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddMaterial(string idFrom, string Nombre, vec3 Color)
{
	Material nuevo;
	nuevo.Name = Nombre;
	nuevo.color = Color;
	nuevo.escalar = 0.0f;
	MaterialIdentifier.insert(std::pair<string, Material>(Nombre, nuevo));
	MaterialIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = Nombre;
	Info.Type = "Material";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

bool ResourceManager::AddLight(string idFrom, string Nombre, vec4 ambient, vec4 diffuse, vec3 direction)
{
	Light nuevo;
	nuevo.Name = Nombre;
	nuevo.Ambient = ambient;
	nuevo.Diffuse = diffuse;
	//nuevo.Diffuse = diffuse;
	nuevo.Direction = direction;
	LightIdentifier.insert(std::pair<string, Light>(Nombre, nuevo));
	LightIndex++;
	//Identify if the resource is from Scene
	ObjectInformation Info;
	Info.CreatedBy = idFrom;
	Info.Name = Nombre;
	Info.Type = "Light";
	GlobalObjectsIdentifier.insert(std::pair<string, ObjectInformation>(to_string(GlobalObjectsCounter), Info));
	GlobalObjectsCounter++;
	return true;
}

string ResourceManager::BuildGameObject(string idFrom,string nameGameObject, string meshname, string texturename, string shadername, string materialname, string lightname)
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
		if (nuevo.GetMaterial() == nullptr)
			return "E_Fail";
	}

	if (lightname != "" || nuevo.GetShader()->flagLight == 1)
	{
		nuevo.AssignLight(&LightIdentifier.find(lightname)->second);
		if (nuevo.GetLight() == nullptr)
			return "E_Fail";
	}
	AddGameObject(nuevo,idFrom);
	return "S_OK";
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

bool ResourceManager::DestroyItemsFromScene(string idFrom)
{
	string PosAnt = "";
	for (GlobalResourcesMap::iterator it = GlobalObjectsIdentifier.begin(); it != GlobalObjectsIdentifier.end(); ++it)
	{
		if (PosAnt !="")
		{
			if (GlobalObjectsIdentifier.find(PosAnt)->second.CreatedBy == idFrom)
				GlobalObjectsIdentifier.erase(PosAnt);
		}
		if (it->second.CreatedBy == idFrom)
		{
			ObjectInformation identifier = it->second;

			if (identifier.Type == "Model")
			{
				Model* aObject = &ModelIdentifier.find(identifier.Name)->second;
				aObject->ShutdownModel();
				ModelIdentifier.erase(ModelIdentifier.find(identifier.Name)->first);
			}
			else if (identifier.Type == "GameObject")
			{
				GameObject* aObject = &GameObjectIdentifier.find(identifier.Name)->second;
				aObject->Shutdown();
				GameObjectIdentifier.erase(GameObjectIdentifier.find(identifier.Name)->first);
			}
			else if (identifier.Type == "Texture")
			{
				Texture* aObject = &TextureIdentifier.find(identifier.Name)->second;
				aObject->Shutdown();
				TextureIdentifier.erase(TextureIdentifier.find(identifier.Name)->first);
			}
			else if (identifier.Type == "Shader")
			{
				Shader* aObject = ShaderIdentifier.find(identifier.Name)->second;
				aObject->Shutdown();
				ShaderIdentifier.erase(ShaderIdentifier.find(identifier.Name)->first);
			}
			else if (identifier.Type == "Material")
			{
				Material* aObject = &MaterialIdentifier.find(identifier.Name)->second;
				MaterialIdentifier.erase(MaterialIdentifier.find(identifier.Name)->first);
			}
			else if (identifier.Type == "Light")
			{
				Light* aObject = &LightIdentifier.find(identifier.Name)->second;
				LightIdentifier.erase(LightIdentifier.find(identifier.Name)->first);
			}
			PosAnt = it->first;
		}
		else
			PosAnt = "";
	}
	if (GlobalObjectsIdentifier.find(PosAnt)->second.CreatedBy == idFrom)
		GlobalObjectsIdentifier.erase(PosAnt);
	return true;
}

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

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
BasicShader* ResourceManager::BShaderActual = nullptr;
MaterialShader* ResourceManager::MShaderActual = nullptr;
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
BasicShader* ResourceManager::BasShader = 0;
MaterialShader* ResourceManager::MatShader = 0;

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

bool ResourceManager::AddStage(string name, int Cells, int CellSize)
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
		nuevo.AssignTexture(&TextureIdentifier.find(texturename)->second);
		if (nuevo.GetTexture() == nullptr)
			return "E_Fail";
	}
	if (shadername != "")
	{
		int shadernumber = ShaderIdentifier.find(shadername)->second;
		if (shadernumber == 0)
			nuevo.AssignBasicShader(BasShader);
		else if (shadernumber == 1)
			nuevo.AssignMaterialShader(MatShader);
		if (nuevo.ExistShader() == false)
			return "E_Fail";
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

bool ResourceManager::LoadShaders()
{
	BasShader = new BasicShader;
	MatShader = new MaterialShader;
	BasShader->Name = "Basic";
	BasShader->Initialize();
	ShaderIdentifier.insert(std::pair<string, int>("Basic", 0));
	MatShader->Name = "Material";
	MatShader->Initialize();
	ShaderIdentifier.insert(std::pair<string, int>("Material", 1));
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
	return true;
}

bool ResourceManager::bindBasicShader(BasicShader * basicshader)
{
	if (BShaderActual != basicshader)
	{
		basicshader->BindShader();
		BShaderActual = basicshader;
		return true;
	}
	return false;
}

bool ResourceManager::bindMaterialShader(MaterialShader * materialshader)
{
	if (MShaderActual != materialshader)
	{
		materialshader->BindShader();
		MShaderActual = materialshader;
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
	BShaderActual = nullptr;
	MShaderActual = nullptr;
	GameObjectIndex = 0;
	ModelIndex = 0;
	TextureIndex = 0;
}

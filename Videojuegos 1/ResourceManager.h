#pragma once
//#ifndef _ResourceManager_H_
//#define _ResourceManager_H_
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static bool AddModel(string path, string name);
	static bool AddTexture(string path, string name);
	static string BuildGameObject(string nameGameObject, string modelname, string texturename, string shadername, string materialname);
	static GameObject* GetObjectByName(string);
	static bool AddShader();
	static bool AddMaterial(string Nombre, vec3 Color);
	static bool InitMaterialshader();

	static bool bindShader(GameObject* GO);
	static bool bindModel(GameObject * GO);

	static void Shutdown();

	using GameObjectMap = std::map<string, GameObject>;
	using ModelMap = std::map<string, Model>;
	using TextureMap = std::map<string, Texture>;
	using ShaderMap = std::map<string, BasicShader>;
	using MaterialMap = std::map<string, Material>;

	static MaterialShader* MatShader;


protected:
	static bool AddGameObject(GameObject);
	//Variables de respuesta
	static bool RB;
	static string RS;
	// Variables de respuesta
	//Actuales
	static BasicShader* ShaderActual;
	static Model* ModeloActual;
	//Objetos
	static GameObjectMap GameObjectIdentifier;
	//static std::map<string, int> GameObjectSearcher;
	static int GameObjectIndex;
	//Modelos
	static ModelMap ModelIdentifier;
	static int ModelIndex;
	//Texture
	static TextureMap TextureIdentifier;
	static int TextureIndex;
	//Shader
	static ShaderMap ShaderIdentifier;
	static int ShaderIndex;
	//Material
	static MaterialMap MaterialIdentifier;
	static int MaterialIndex;
};

//#endif
#pragma once
//#ifndef _ResourceManager_H_
//#define _ResourceManager_H_
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
#include "Light.h"
#include "KeyHandler.h"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static bool AddModel(string path, string name);
	static bool AddTexture(string path, string name);
	static bool AddStage(string name, float Cells, float CellSize);
	static bool AddShader(string name, Shader* shader);
	static string BuildGameObject(string nameGameObject, string meshname, string texturename, string shadername, string materialname, string lightname);
	static GameObject* GetObjectByName(string);
	static bool AddMaterial(string Nombre, vec3 Color);
	static bool AddLight(string Nombre, vec4 ambient, vec4 diffuse, vec3 direction);

	static bool bindShader(Shader* basicshader);
	static bool bindModel(Model * model);

	static void Shutdown();

	using GameObjectMap = std::map<string, GameObject>;
	using ModelMap = std::map<string, Model>;
	using TextureMap = std::map<string, Texture>;
	using ShaderMap = std::map<string, Shader*>;
	using MaterialMap = std::map<string, Material>;
	using LightMap = std::map<string, Light>;

	//Informacion de pantalla
	static int ScreenWidthF;
	static int ScreenHeightF;
	static int ScreenWidth;
	static int ScreenHeight;

	//Player 1
	static KeyHandler* Player1;


protected:
	static bool AddGameObject(GameObject);
	//Variables de respuesta
	static bool RB;
	static string RS;
	// Variables de respuesta
	//Actuales
	static Shader* ShaderActual;
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
	//Material
	static MaterialMap MaterialIdentifier;
	static int MaterialIndex;
	//Material
	static LightMap LightIdentifier;
	static int LightIndex;
};

//#endif
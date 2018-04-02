#pragma once
//#ifndef _ResourceManager_H_
//#define _ResourceManager_H_
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "BasicShader.h"
#include "MaterialShader.h"
#include "Material.h"
#include "KeyHandler.h"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static bool AddModel(string path, string name);
	static bool AddTexture(string path, string name);
	static string BuildGameObject(string nameGameObject, string modelname, string texturename, string shadername, string materialname);
	static GameObject* GetObjectByName(string);
	static bool LoadShaders();
	static bool AddMaterial(string Nombre, vec3 Color);
	static bool InitMaterialshader();

	static bool bindBasicShader(BasicShader* basicshader);
	static bool bindMaterialShader(MaterialShader* materialshader);
	static bool bindModel(Model * model);

	static void Shutdown();

	using GameObjectMap = std::map<string, GameObject>;
	using ModelMap = std::map<string, Model>;
	using TextureMap = std::map<string, Texture>;
	using ShaderMap = std::map<string, int>;
	using MaterialMap = std::map<string, Material>;

	static BasicShader* BasShader;
	static MaterialShader* MatShader;

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
	static BasicShader* BShaderActual;
	static MaterialShader* MShaderActual;
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
};

//#endif
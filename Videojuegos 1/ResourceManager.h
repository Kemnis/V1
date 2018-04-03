#pragma once
//#ifndef _ResourceManager_H_
//#define _ResourceManager_H_
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include "Terrain.h"
#include "Shader.h"
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
	static bool AddStage(string name, int Cells, int CellSize, int Size);
	static bool AddShader(string name, Shader* shader);
	static string BuildGameObject(string nameGameObject, string meshname, string texturename, string shadername, string materialname);
	static GameObject* GetObjectByName(string);
	static bool AddMaterial(string Nombre, vec3 Color);

	static bool bindShader(Shader* basicshader);
	static bool bindModel(Model * model);

	static void Shutdown();

	using GameObjectMap = std::map<string, GameObject>;
	using ModelMap = std::map<string, Model>;
	using TextureMap = std::map<string, Texture>;
	using ShaderMap = std::map<string, Shader*>;
	using MaterialMap = std::map<string, Material>;
	using TerrainMap = std::map<string, Terrain>;

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
	//Terrain
	static TerrainMap TerrainIdentifier;
	static int TerrainIndex;
	//Shader
	static ShaderMap ShaderIdentifier;
	//Material
	static MaterialMap MaterialIdentifier;
	static int MaterialIndex;
};

//#endif
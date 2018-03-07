#pragma once
//#ifndef _ResourceManager_H_
//#define _ResourceManager_H_
#include "GameObject.h"
#include "Model.h"
#include "Mesh3D.h"
#include "Texture.h"
#include "ShaderClass.h"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static bool AddModel(string path, string name);
	static void AddMesh(string primitive, string name);
	static bool AddTexture(string path, string name);
	static string BuildGameObject(string nameGameObject, string modelname, string meshname, string texturename, string shadername);
	static GameObject* GetObjectByName(string);
	static bool AddShader();

	static bool bindShader(ShaderClass* shader);
	static bool bindMesh(Mesh3D* mesh);
	static bool bindModel(GameObject * GO);

	static void Shutdown();

	using GameObjectMap = std::map<string, GameObject>;
	using ModelMap = std::map<string, Model>;
	using MeshMap = std::map<string, Mesh3D>;
	using TextureMap = std::map<string, Texture>;
	using ShaderMap = std::map<string, ShaderClass>;

protected:
	static bool AddGameObject(GameObject);
	//Considerar quitarlo si se unifica el modelo y el mesh
	static char ChangeBinder;
	//Variables de respuesta
	static bool RB;
	static string RS;
	// Variables de respuesta
	//Actuales
	static ShaderClass* ShaderActual;
	static Mesh3D* MeshActual;
	static Model* ModeloActual;
	//Objetos
	static GameObjectMap GameObjectIdentifier;
	//static std::map<string, int> GameObjectSearcher;
	static int GameObjectIndex;
	//Modelos
	static ModelMap ModelIdentifier;
	static int ModelIndex;
	//Meshes
	static MeshMap MeshIdentifier;
	static int MeshIndex;
	//Texture
	static TextureMap TextureIdentifier;
	static int TextureIndex;
	//Shader
	static ShaderMap ShaderIdentifier;
	static int ShaderIndex;
};

//#endif
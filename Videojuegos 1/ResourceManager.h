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
	static string BuildGameObject(string nameGameObject, int modelindex, int meshindex, int textureindex, int shaderindex);
	static GameObject* GetObjectByName(string);
	static bool AddShader();

	static bool bindShader(ShaderClass* shader);
	static bool bindMesh(Mesh3D* mesh);
	static bool bindMesh(GameObject * GO);

	static void Shutdown();

protected:
	static bool AddGameObject(GameObject);
	//Variables de respuesta
	static bool RB;
	static string RS;
	// Variables de respuesta
	//Actuales
	static ShaderClass* ShaderActual;
	static Mesh3D* MeshActual;
	//Objetos
	static std::map<int, GameObject> GameObjectIdentifier;
	static std::map<string, int> GameObjectSearcher;
	static int GameObjectIndex;
	//Modelos
	static std::map<int, Model> ModelIdentifier;
	static int ModelIndex;
	//Meshes
	static std::map<int, Mesh3D> MeshIdentifier;
	static std::map<string, int> MeshSearcher;
	static int MeshIndex;
	//Texture
	static std::map<int, Texture> TextureIdentifier;
	static int TextureIndex;
	//Shader
	static std::map<int, ShaderClass> ShaderIdentifier;
	static int ShaderIndex;
};

//#endif
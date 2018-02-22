#include "ResourceManager.h"
#include "stdafx.h"

//Variables de respuesta
bool ResourceManager::RB = false;
string ResourceManager::RS = "";
// Variables de respuesta
ShaderClass* ResourceManager::ShaderActual = nullptr;
Mesh3D* ResourceManager::MeshActual = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::AddMesh3D()
{
	return false;
}

bool ResourceManager::AddShader()
{
	return false;
}

bool ResourceManager::AddTexture()
{
	return false;
}

bool ResourceManager::bindShader(ShaderClass * shader)
{
	if (ShaderActual != shader)
	{
		shader->BindShader();
		ShaderActual = shader;
		return true;
	}
	return false;
}

bool ResourceManager::bindMesh(Mesh3D * mesh)
{
	if (MeshActual = mesh)
	{
		mesh->BindMesh();
		MeshActual = mesh;
		return true;
	}
	return false;
}

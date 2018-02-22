#pragma once
#ifndef _ResourceManager_H_
#define _ResourceManager_H_
#include "ShaderClass.h"
#include "Mesh3D.h"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static bool AddMesh3D();
	static bool AddShader();
	static bool AddTexture();

	static bool bindShader(ShaderClass* shader);
	static bool bindMesh(Mesh3D* mesh);

protected:
	//Variables de respuesta
	static bool RB;
	static string RS;
	// Variables de respuesta

private:

	static ShaderClass * ShaderActual;
	static Mesh3D * MeshActual;
};

#endif
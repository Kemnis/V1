#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "Shader.h"
#include "Material.h"
using namespace DirectX;
using namespace std;
class BasicShader : public Shader
{
public:
	struct MaterialBufferType
	{
		vec4 ColorMaterial;
	};
	BasicShader(std::string, std::string);
	bool Initialize (const std::string& vsSource, const std::string& psSource) override;
};


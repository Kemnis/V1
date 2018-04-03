#ifndef _MaterialShader_H_
#define _MaterialShader_H_
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "Texture.h"
#include "Shader.h"
using namespace DirectX;
using namespace std;
class MaterialShader : public Shader
{
	
public:
	struct MaterialBufferType
	{
		vec4 ColorMaterial;
	};
	MaterialShader(std::string, std::string);

	bool Initialize(const std::string& vsSource, const std::string& psSource) override;
};

#endif
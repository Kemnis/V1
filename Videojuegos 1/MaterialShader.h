#ifndef _MaterialShader_H_
#define _MaterialShader_H_
#include "Shader.h"

using namespace DirectX;
using namespace std;
class MaterialShader : public Shader
{
	
public:
	MaterialShader(std::string, std::string);

	bool Initialize(const std::string& vsSource, const std::string& psSource) override;
};

#endif
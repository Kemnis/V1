#pragma once
#include <directxmath.h>
#include "glm\glm.hpp"

namespace ConstantBufferTypes {
	struct MatrixBuffer
	{
		XMMATRIX projectionViewWorld;
	};

	struct MaterialBuffer
	{
		glm::vec4 ColorMaterial;
	};

	struct LightBuffer
	{
		glm::vec4 ambientColor;
		glm::vec4 diffuseColor;
		glm::vec3 lightDirection;
		float padding;
	};
}
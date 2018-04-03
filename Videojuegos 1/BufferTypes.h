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

}
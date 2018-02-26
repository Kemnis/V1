#pragma once
#ifndef _Mesh3D_H_
#define _Mesh3D_H_
#include "ShaderClass.h"
#include <d3d11.h>
#include <directxmath.h>
#include "Transforms.h"
using namespace DirectX;
class Mesh3D : DxComponent<Mesh3D>, Transforms
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	Mesh3D();
	~Mesh3D();

	bool Initialize();
	void Shutdown();
	void Draw();
	void BindMesh();

	Transforms* transform;
private:
	int m_vertexCount, m_indexCount;

private:
	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
};

#endif
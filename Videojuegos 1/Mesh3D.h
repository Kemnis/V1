#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: Mesh3D.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Mesh3D_H_
#define _Mesh3D_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: Mesh3D
////////////////////////////////////////////////////////////////////////////////
class Mesh3D
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	Mesh3D();
	Mesh3D(const Mesh3D&);
	~Mesh3D();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif
#include "Mesh3D.h"
#include "stdafx.h"


Mesh3D::Mesh3D()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	transform= new Transforms();
}

Mesh3D::~Mesh3D()
{
}

Mesh3D::InfoPrimitive Mesh3D::DefineTriangle()
{
	InfoPrimitive Info;

	MeshVertex.VertexCount = 3;
	MeshVertex.IndexCount = 3;

	Info.vertices = new VertexType[MeshVertex.VertexCount];

	Info.indices = new unsigned long[MeshVertex.IndexCount];

	Info.vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	Info.vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	Info.vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
	Info.vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	Info.vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	Info.vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	Info.indices[0] = 0;  // Bottom left.
	Info.indices[1] = 1;  // Top middle.
	Info.indices[2] = 2;  // Bottom right.
	return Info;
}

Mesh3D::InfoPrimitive Mesh3D::DefineSquare()
{
	InfoPrimitive Info;

	MeshVertex.VertexCount = 4;
	MeshVertex.IndexCount = 6;

	Info.vertices = new VertexType[MeshVertex.VertexCount];

	Info.indices = new unsigned long[MeshVertex.IndexCount];

	Info.vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // Top left.
	Info.vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	Info.vertices[1].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // Top right.
	Info.vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	Info.vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	Info.vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	Info.vertices[3].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	Info.vertices[3].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	Info.indices[0] = 0;  // Top left.
	Info.indices[1] = 1;  // Top right.
	Info.indices[2] = 3;  // Bottom left.

	Info.indices[3] = 3;  // Bottom left.
	Info.indices[4] = 1;  // Top right.
	Info.indices[5] = 2;  // Bottom right.
	return Info;
}

bool Mesh3D::Initialize()
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	
	InfoPrimitive Primitive=DefineTriangle();

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * MeshVertex.VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = Primitive.vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * MeshVertex.IndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = Primitive.indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] Primitive.vertices;
	Primitive.vertices = 0;

	delete[] Primitive.indices;
	Primitive.indices = 0;

	return true;
}

void Mesh3D::BindMesh()
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Mesh3D::Draw()
{
	deviceContext->DrawIndexed(MeshVertex.VertexCount, 0, 0);
	return;
}

void Mesh3D::Shutdown()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}
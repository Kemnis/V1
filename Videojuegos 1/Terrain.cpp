#include "Texture.h"
#include "stdafx.h"

Terrain::Terrain()
{

}

Terrain::~Terrain() {}

bool Terrain::Initialize(int Cells, int CellSize, int TotalSize)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	// Calculate the number of vertices in the terrain.
	Mesh.VertexCount = (Cells + 1);

	for (int i = 0; i < Mesh.VertexCount; i++)
	{
		for (int j = 0; j < Mesh.VertexCount; j++)
		{
			Mesh.AddVertex(j*CellSize,0,i*CellSize);
			Mesh.AddNormals(0, 1, 0);
		}
	}

	// Set the index count to the same as the vertex count.
	Mesh.IndexCount = Mesh.VertexCount * Mesh.VertexCount;
	for (int i = 0; i < ((Mesh.VertexCount-1)*(Mesh.VertexCount-1)); i++)
	{
		Mesh.AddIndex(i);
		Mesh.AddIndex(i * Mesh.VertexCount);
		Mesh.AddIndex(i + 1);
		Mesh.AddIndex(i);
		Mesh.AddIndex(i);
		Mesh.AddIndex(i);
	}
	Mesh.DoFinalMesh();

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex::VertexType) * Mesh.VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = &Mesh.FinalMesh[0];;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &VertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * Mesh.IndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	vector<unsigned long> indices = Mesh.GetIndex();
	indexData.pSysMem = &indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &IndexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void Terrain::Draw()
{
	deviceContext->DrawIndexed(Mesh.IndexCount, 0, 0);
	return;
}

void Terrain::BindMesh()
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex::VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Vertex Terrain::GetMesh()
{
	return Mesh;
}

void Terrain::Shutdown()
{
	if (IndexBuffer)
	{
		IndexBuffer->Release();
		IndexBuffer = 0;
	}

	if (VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = 0;
	}

	return;
}

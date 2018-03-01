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

void Mesh3D::DefineTriangle()
{

	MeshVertex.AddNewVertex(-1.0f, -1.0f, 0.0f);  // Bottom left.
	MeshVertex.AddColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));

	MeshVertex.AddNewVertex(0.0f, 1.0f, 0.0f);  // Top middle.
	MeshVertex.AddColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));

	MeshVertex.AddNewVertex(1.0f, -1.0f, 0.0f);  // Bottom right.
	MeshVertex.AddColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));

	MeshVertex.AddNewIndex(0); // Bottom left.
	MeshVertex.AddNewIndex(1);  // Top middle.
	MeshVertex.AddNewIndex(2);  // Bottom right.
}

void Mesh3D::DefineSquare()
{
	MeshVertex.AddNewVertex(-1.0f, -1.0f, 0.0f);  // Top left.
	MeshVertex.AddColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));

	MeshVertex.AddNewVertex(-1.0f, 1.0f, 0.0f);  // Top right.
	MeshVertex.AddColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));

	MeshVertex.AddNewVertex(1.0f, 1.0f, 0.0f);  // Bottom right.
	MeshVertex.AddColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));

	MeshVertex.AddNewVertex(1.0f, -1.0f, 0.0f);  // Bottom left.
	MeshVertex.AddColor(vec4(0.0f, 1.0f, 0.0f, 1.0f));

	MeshVertex.AddNewIndex(0); // Bottom left.
	MeshVertex.AddNewIndex(1);  // Top middle.
	MeshVertex.AddNewIndex(2);  // Bottom right.

	MeshVertex.AddNewIndex(0);  // Bottom left.
	MeshVertex.AddNewIndex(2);  // Top right.
	MeshVertex.AddNewIndex(3);  // Bottom right.
}
//void Mesh3D::DefineSphere()
//{
//	InfoPrimitive Info;
//	int slices = 36;
//	int stacks = 36;
//	float ratio = 2.0;
//	float inicio = 0;
//	float final = 1;
//
//	MeshVertex.VertexCount = slices * stacks;
//	MeshVertex.IndexCount = (slices - 1)*(stacks - 1) * 6;
//
//	//Create the vertex array
//	vertices = new VertexType[MeshVertex.VertexCount];
//	//Create the index array
//	indices = new unsigned long[MeshVertex.IndexCount];
//
//
//	for (int i = 0; i < slices; i++)
//	{
//		for (int j = 0; j < stacks; j++)
//		{
//			int indice = (i * stacks + j);
//
//			vertices[indice].position.x = ratio * cos(((double)j / (stacks - 1))*(XM_PI*(final - inicio)) + XM_PI * inicio - XM_PI / 2.0)*cos(2.0*XM_PI*(double)i / (slices - 1));
//			vertices[indice].position.y = ratio * sin(((double)j / (stacks - 1))*(XM_PI*(final - inicio)) + XM_PI * inicio - XM_PI / 2.0);
//			vertices[indice].position.z = ratio * cos(((double)j / (stacks - 1))*(XM_PI*(final - inicio)) + XM_PI * inicio - XM_PI / 2.0)*sin(2.0*XM_PI*(double)i / (slices - 1));
//
//			vertices[indice].normal.x = cos(((double)j / (stacks - 1))*(XM_PI*(final - inicio)) + XM_PI * inicio - XM_PI / 2.0)* cos(2.0*XM_PI*(double)i / (slices - 1));
//			vertices[indice].normal.y = sin(((double)j / (stacks - 1))*(XM_PI*(final - inicio)) + XM_PI * inicio - XM_PI / 2.0);
//			vertices[indice].normal.z = cos(((double)j / (stacks - 1))*(XM_PI*(final - inicio)) + XM_PI * inicio - XM_PI / 2.0)* sin(2.0*XM_PI*(double)i / (slices - 1));
//
//			vertices[indice].texture.x = (1 - (double)i / (stacks - 1));
//			vertices[indice].texture.y = (1 - (double)j / (slices - 1));
//		}
//	}
//
//	int index = 0, index1 = 0, index2 = 0, index3 = 0, index4 = 0;
//
//	for (int i = 0; i < slices - 1; i++)
//	{
//		for (int j = 0; j < stacks - 1; j++)
//		{
//			index1 = (stacks *   i) + j;    // Bottom left.
//			index2 = (stacks *   i) + (j + 1);  // Bottom right.
//			index3 = (stacks * (i + 1)) + j;    // Upper left.
//			index4 = (stacks * (i + 1)) + (j + 1);  // Upper right.
//
//			indices[index++] = index1;
//			indices[index++] = index2;
//			indices[index++] = index4;
//
//			indices[index++] = index1;
//			indices[index++] = index4;
//			indices[index++] = index3;
//		}
//	}
//	return Info;
//}

//void Mesh3D::DefineSphere(float diameter,size_t tessellation)
//{
//	float radius = diameter / 2;
//	if (tessellation < 3)
//		throw std::out_of_range("tesselation parameter out of range");
//
//	size_t verticalSegments = tessellation;
//	size_t horizontalSegments = tessellation * 2;
//	// Create rings of vertices at progressively higher latitudes.
//	for (size_t i = 0; i <= verticalSegments; i++)
//	{
//		float v = 1 - (float)i / verticalSegments;
//
//		float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
//		float dy, dxz;
//
//		XMScalarSinCos(&dy, &dxz, latitude);
//
//		// Create a single ring of vertices at this latitude.
//		for (size_t j = 0; j <= horizontalSegments; j++)
//		{
//			float u = (float)j / horizontalSegments;
//
//			float longitude = j * XM_2PI / horizontalSegments;
//			float dx, dz;
//
//			XMScalarSinCos(&dx, &dz, longitude);
//
//			dx *= dxz;
//			dz *= dxz;
//
//			XMVECTOR normal = XMVectorSet(dx, dy, dz, 0);
//			XMVECTOR result = normal*radius;
//			XMFLOAT4 res;
//			XMStoreFloat4(&res, result);
//			XMVECTOR textureCoordinate = XMVectorSet(u, v, 0, 0);
//			MeshVertex.AddNewVertex(res);
//			XMStoreFloat4(&res, normal);
//			MeshVertex.AddNewNormals(res);
//			XMStoreFloat4(&res, textureCoordinate);
//			MeshVertex.AddNewNormals(res);
//		}
//	}
//
//	// Fill the index buffer with triangles joining each pair of latitude rings.
//	size_t stride = horizontalSegments + 1;
//
//	for (size_t i = 0; i < verticalSegments; i++)
//	{
//		for (size_t j = 0; j <= horizontalSegments; j++)
//		{
//			size_t nextI = i + 1;
//			size_t nextJ = (j + 1) % stride;
//			
//			MeshVertex.AddNewIndex(i * stride + j);
//			MeshVertex.AddNewIndex(nextI * stride + j);
//			MeshVertex.AddNewIndex(i * stride + nextJ);
//
//			MeshVertex.AddNewIndex(i * stride + nextJ);
//			MeshVertex.AddNewIndex(nextI * stride + j);
//			MeshVertex.AddNewIndex(nextI * stride + nextJ);
//		}
//	}
//	return InfoPrimitive();
//}

bool Mesh3D::Initialize(string NameOfFigure)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	//if (NameOfFigure == "Triangle")
	//DefineTriangle();
	DefineSquare();
	/*else if (NameOfFigure == "Square")
	else if (NameOfFigure == "Sphere")
		Primitive = DefineSphere();*/

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex::VertexType) * MeshVertex.VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vector<Vertex::VertexType> vertices = MeshVertex.VertexResult();
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = &vertices[0];
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

	vector<unsigned long> indices = MeshVertex.GetIndex();
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = &indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Mesh3D::BindMesh()
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex::VertexType);
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
	deviceContext->DrawIndexed(MeshVertex.IndexCount, 0, 0);
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
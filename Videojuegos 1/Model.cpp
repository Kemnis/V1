#include "stdafx.h"

Model::Model(string path)
{
	VertexBuffer = 0;
	IndexBuffer = 0;
	if (!LoadModel(path))
		ErrorFnc("No se pudo cargar el modelo");
	else
		Initialize();
}

Model::~Model()
{
}

bool Model::Initialize()
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	//Create the vertex array
	vertices = new VertexType[MeshVertex.VertexCount];
	if (!vertices)
		ErrorFnc("No se pudo crear el arreglo de vertices");

	//Create the index array
	indices = new unsigned long[MeshVertex.IndexCount];
	if (!indices)
		ErrorFnc("No se pudo crear el arreglo de indices");

	//Load the vertex and index array with data
	for (i = 0; i < (MeshVertex.IndexCount); i++) {
		vertices[i].position = XMFLOAT3(MeshVertex.GetVertex(i).x, MeshVertex.GetVertex(i).y, MeshVertex.GetVertex(i).z);
		vertices[i].texture = XMFLOAT2(MeshVertex.GetTexture(i).x, MeshVertex.GetTexture(i).y);
		vertices[i].normal = XMFLOAT3(MeshVertex.GetNormal(i).x, MeshVertex.GetNormal(i).y, MeshVertex.GetNormal(i).z);

		indices[i] = i;
	}

	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)* MeshVertex.IndexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Now create the vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &VertexBuffer);
	if (FAILED(result))
		ErrorFnc("No se pudo crear el buffer de vertices");

	//Set up the description of the static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* MeshVertex.IndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the index data
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create the index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &IndexBuffer);
	if (FAILED(result))
		ErrorFnc("No se pudo crear el buffer de indices");

	//Release the arrays now that the vertex and index buffers have been created and loaded
	delete[]vertices;
	vertices = 0;

	delete[]indices;
	indices = 0;

	return true;
}

void Model::Draw()
{
	deviceContext->DrawIndexed(MeshVertex.IndexCount, 0, 0);
	return;
}

void Model::BindMesh()
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool Model::LoadModel(string path)
{
	string result = "";

	std::string fn = path;
	if (fn.substr(fn.find_last_of(".") + 1) != "obj")
		ErrorFnc("Compruebe la extension del archivo, debe ser .obj");

	ifstream fin;
	char input, in;
	Vertex Array;
	vec3 FaceIndex;

	try {
		fin.open(path);

		if (fin.fail() == true)
			ErrorFnc("No se pudo abrir el archivo antes de cargarlo en ram");

		fin.get(input);
		while (!fin.eof())
		{
			/*if (input == 'm')
			{
			fin.get(input);
			if (input == 't')
			fin.get(input);
			if (input == 'l')
			fin.get(input);
			if (input == 'l')
			fin.get(input);
			if (input == 'i')
			fin.get(input);
			if (input == 'b')
			fin.get(input);
			MtlFile.assign((std::istreambuf_iterator<char>(fin)),
			(std::istreambuf_iterator<char>()));;
			}*/
			if (input == 'v')
			{
				fin.get(input);
				if (input == ' ')
				{
					vec3 temp;
					fin >> temp.x >> temp.y >> temp.z;
					temp.z = -1.0f *temp.z;
					Array.AddNewVertex(temp);
				}
				if (input == 't')
				{
					vec2 temp;
					fin >> temp.x >> temp.y;
					temp.y = 1.0f - temp.y;
					Array.AddNewTexture(temp);
				}
				if (input == 'n')
				{
					vec3 temp;
					fin >> temp.x >> temp.y >> temp.z;
					temp.z = -1.0f * temp.z;
					Array.AddNewNormals(temp);
				}
			}

			if (input == 'f')
			{
				fin.get(input);
				if (input == ' ')
				{
					vec3 Vertice, Tex, Normal;
					fin >> Vertice.z >> in >> Tex.z >> in >> Normal.z
						>> Vertice.y >> in >> Tex.y >> in >> Normal.y
						>> Vertice.x >> in >> Tex.x >> in >> Normal.x;
					Array.AddNewTriangle(Vertice, Tex, Normal);
				}
			}


			while (input != '\n')
			{
				fin.get(input);
			}
			fin.get(input);
		}

		//Solo para fines de debugeo en caso de errores... Este codigo puede decir cosas relevantes
		_RPT3(0, "First Vertex: %f,%f,%f\n", Array.GetFirstVertex().x, Array.GetFirstVertex().y, Array.GetFirstVertex().z);
		_RPT2(0, "First UVs: %f, %f\n", Array.GetFirstTexture().x, Array.GetFirstTexture().y);
		_RPT3(0, "First Normals: %f,%f,%f\n", Array.GetFirstNormal().x, Array.GetFirstNormal().y, Array.GetFirstNormal().z);

		_RPT3(0, "Last Vertex: %f,%f,%f\n", Array.GetLastVertex().x, Array.GetLastVertex().y, Array.GetLastVertex().z);
		_RPT2(0, "Last UVs: %f, %f\n", Array.GetFirstTexture().x, Array.GetFirstTexture().y);
		_RPT3(0, "Last Normals: %f,%f,%f\n", Array.GetLastNormal().x, Array.GetLastNormal().y, Array.GetLastNormal().z);

		_RPT4(0, "#V: %f   #T: %f   #N: %f   #F: %f\n", Array.Count().x, Array.Count().y, Array.Count().z, Array.Count().w);
		//------------------------------------------------------------------------------------------

		fin.close();

		int i;
		for (i = 0; i < Array.IndexCount; i++)
		{
			//_RPT1(0, "i %d\n", i);
			FaceIndex.x = Array.GetTriangleFV(i).x;
			FaceIndex.y = Array.GetTriangleFT(i).x;
			FaceIndex.z = Array.GetTriangleFN(i).x;
			MeshVertex.AddPack(Array.GetVertex(FaceIndex.x), Array.GetTexture(FaceIndex.y), Array.GetNormal(FaceIndex.z));

			FaceIndex.x = Array.GetTriangleFV(i).y;
			FaceIndex.y = Array.GetTriangleFT(i).y;
			FaceIndex.z = Array.GetTriangleFN(i).y;
			MeshVertex.AddPack(Array.GetVertex(FaceIndex.x), Array.GetTexture(FaceIndex.y), Array.GetNormal(FaceIndex.z));

			FaceIndex.x = Array.GetTriangleFV(i).z;
			FaceIndex.y = Array.GetTriangleFT(i).z;
			FaceIndex.z = Array.GetTriangleFN(i).z;
			MeshVertex.AddPack(Array.GetVertex(FaceIndex.x), Array.GetTexture(FaceIndex.y), Array.GetNormal(FaceIndex.z));
		}
	}
	catch (std::exception& e)
	{
		result = string("\nError exception: ") + e.what();
	}


	if (result != "")
		ErrorFnc("no se logro cargar en ram.");

	_RPT1(0, "Vertices: %f\n", MeshVertex.Count().x);
	_RPT1(0, "UVs: %f\n", MeshVertex.Count().y);
	_RPT1(0, "Normals: %f\n", MeshVertex.Count().z);
	_RPT1(0, "Faces: %f\n", MeshVertex.Count().w);
	return true;
}

void Model::ShutdownModel()
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

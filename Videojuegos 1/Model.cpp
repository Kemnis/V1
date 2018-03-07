#include "stdafx.h"

Model::Model(string path)
{
	VertexBuffer = 0;
	IndexBuffer = 0;
	transform = new Transforms();
	if (path.substr(path.find_last_of(".") + 1) == "obj")
	{
		if (!LoadModel(path))
			ErrorFnc("No se pudo cargar el modelo");
		else
			Initialize("");
	}
	else
		Initialize(path);
}

Model::~Model()
{
}

bool Model::Initialize(string primitive)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex::VertexType)* MeshVertex.IndexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	
	// Give the subresource structure a pointer to the vertex data.
	if (primitive != "")
	{
		vector<Vertex::VertexType> vertices = MeshVertex.VertexResult();
		vertexData.pSysMem = &vertices[0];
	}
	else
	{
		vertexData.pSysMem = &MeshVertex.FinalMesh[0];
	}
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

	vector<unsigned long> indices = MeshVertex.IndexResult();
	//Give the subresource structure a pointer to the index data
	indexData.pSysMem = &indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create the index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &IndexBuffer);
	if (FAILED(result))
		ErrorFnc("No se pudo crear el buffer de indices");


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
	stride = sizeof(Vertex::VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Vertex Model::GetMesh()
{
	return MeshVertex;
}

bool Model::LoadModel(string path)
{
	string result = "";

	std::string fn = path;
	if (fn.substr(fn.find_last_of(".") + 1) != "obj")
		ErrorFnc("Compruebe la extension del archivo, debe ser .obj");

	ifstream fin;
	char input, in;
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
					MeshVertex.AddVertex(temp);
				}
				if (input == 't')
				{
					vec2 temp;
					fin >> temp.x >> temp.y;
					temp.y = 1.0f - temp.y;
					MeshVertex.AddUV(temp);
				}
				if (input == 'n')
				{
					vec3 temp;
					fin >> temp.x >> temp.y >> temp.z;
					temp.z = -1.0f * temp.z;
					MeshVertex.AddNormals(temp);
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
					MeshVertex.AddTriangleFaces(Vertice, Tex, Normal);
				}
			}


			while (input != '\n')
			{
				fin.get(input);
			}
			fin.get(input);
		}

		//Solo para fines de debugeo en caso de errores... Este codigo puede decir cosas relevantes
		_RPT3(0, "First Vertex: %f,%f,%f\n", MeshVertex.GetFirstVertex().x, MeshVertex.GetFirstVertex().y, MeshVertex.GetFirstVertex().z);
		_RPT2(0, "First UVs: %f, %f\n", MeshVertex.GetFirstTexture().x, MeshVertex.GetFirstTexture().y);
		_RPT3(0, "First Normals: %f,%f,%f\n", MeshVertex.GetFirstNormal().x, MeshVertex.GetFirstNormal().y, MeshVertex.GetFirstNormal().z);

		_RPT3(0, "Last Vertex: %f,%f,%f\n", MeshVertex.GetLastVertex().x, MeshVertex.GetLastVertex().y, MeshVertex.GetLastVertex().z);
		_RPT2(0, "Last UVs: %f, %f\n", MeshVertex.GetFirstTexture().x, MeshVertex.GetFirstTexture().y);
		_RPT3(0, "Last Normals: %f,%f,%f\n", MeshVertex.GetLastNormal().x, MeshVertex.GetLastNormal().y, MeshVertex.GetLastNormal().z);

		//_RPT4(0, "#V: %f   #T: %f   #N: %f   #F: %f\n", MeshVertex.GetVertex(), MeshVertex.GetTexture(), MeshVertex.GetNormal(), MeshVertex.GetTriangleFN());
		//------------------------------------------------------------------------------------------

		fin.close();

		int i;
		for (i = 0; i < MeshVertex.VertexCount; i++)
		{
			//_RPT1(0, "i %d\n", i);
			FaceIndex.x = MeshVertex.GetTriangleFV(i).x-1;
			FaceIndex.y = MeshVertex.GetTriangleFT(i).x-1;
			FaceIndex.z = MeshVertex.GetTriangleFN(i).x-1;
			MeshVertex.ConstructIndexFromTriangles(MeshVertex.GetVertex(FaceIndex.x), vec4(1.0f, 1.0f, 1.0f, 1.0f), MeshVertex.GetTexture(FaceIndex.y), MeshVertex.GetNormal(FaceIndex.z));

			FaceIndex.x = MeshVertex.GetTriangleFV(i).y-1;
			FaceIndex.y = MeshVertex.GetTriangleFT(i).y-1;
			FaceIndex.z = MeshVertex.GetTriangleFN(i).y-1;
			MeshVertex.ConstructIndexFromTriangles(MeshVertex.GetVertex(FaceIndex.x), vec4(1.0f, 1.0f, 1.0f, 1.0f), MeshVertex.GetTexture(FaceIndex.y), MeshVertex.GetNormal(FaceIndex.z));

			FaceIndex.x = MeshVertex.GetTriangleFV(i).z-1;
			FaceIndex.y = MeshVertex.GetTriangleFT(i).z-1;
			FaceIndex.z = MeshVertex.GetTriangleFN(i).z-1;
			MeshVertex.ConstructIndexFromTriangles(MeshVertex.GetVertex(FaceIndex.x), vec4(1.0f, 1.0f, 1.0f, 1.0f), MeshVertex.GetTexture(FaceIndex.y), MeshVertex.GetNormal(FaceIndex.z));
		}
	}
	catch (std::exception& e)
	{
		result = string("\nError exception: ") + e.what();
	}


	if (result != "")
		ErrorFnc("no se logro cargar en ram.");

	_RPT1(0, "Vertices: %f\n", MeshVertex.GetAllIndex().x);
	_RPT1(0, "UVs: %f\n", MeshVertex.GetAllIndex().y);
	_RPT1(0, "Normals: %f\n", MeshVertex.GetAllIndex().z);
	_RPT1(0, "Faces: %f\n", MeshVertex.GetAllIndex().w);
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

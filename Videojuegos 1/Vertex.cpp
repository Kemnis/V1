#include "stdafx.h"

Vertex::Vertex()
{
	Color.clear();
	VertexCount = 0;
	indexNormals = 0;
	indexUv = 0;
	indexTriangles = 0;
	vertices.clear();
	indices.clear();
	normal.clear();
	uv.clear();
	IndexCount = 0;
	VertexCount = 0;
	indices.clear();
	TriangleFaceVertex.clear();
	TriangleFaceTexture.clear();
	TriangleFaceNormal.clear();
	Nullable3 = { 0,0,0 };
	Nullable2 = { 0,0 };
}

vector<unsigned long> Vertex::IndexResult() {
	vector<unsigned long> resulti;
	resulti.reserve(IndexCount);

	for (int i = 0; i < (IndexCount); i++) {
		resulti.push_back(i);
	}
	return resulti;
}

vector<unsigned long> Vertex::GetIndex() {
	return indices;
}

vector<Vertex::VertexType> Vertex::VertexResult()
{
	vector<Vertex::VertexType> result;
		
	result.reserve(VertexCount);
	
	for (int i = 0; i < (VertexCount); i++) {
		VertexType nuevo;
		nuevo.position = XMFLOAT3(GetVertex(i).x, GetVertex(i).y, GetVertex(i).z);
		nuevo.color = XMFLOAT4(GetColor(i).x, GetColor(i).y, GetColor(i).z, GetColor(i).w);
		nuevo.texture = XMFLOAT2(GetTexture(i).x, GetTexture(i).y);
		nuevo.normal = XMFLOAT3(GetNormal(i).x, GetNormal(i).y, GetNormal(i).z);
		result.push_back(nuevo);
	}
	return result;
}

vec4 Vertex::GetColor(int index)
{
	if (VertexCount == 0)
		return vec4();
	else
		return Color[index];
}

void Vertex::AddVertex(vec3 InfoVertex)
{
	VertexCount++;
	vertices.push_back(InfoVertex);
}

void Vertex::AddIndex(int InfoIndex)
{
	IndexCount++;
	indices.push_back(InfoIndex);
}

void Vertex::AddNormals(vec3 InfoNormal)
{
	indexNormals++;
	normal.push_back(InfoNormal);
}

void Vertex::AddUV(vec2 InfoUv)
{
	indexUv++;
	uv.push_back(InfoUv);
}

void Vertex::AddColor(vec4 InfoColor)
{
	Color.push_back(InfoColor);
}

void Vertex::AddTriangleFaces(vec3 InfoTriangleFaceVertex, vec3 InfoTriangleFaceTexture, vec3 InfoTriangleFaceNormal)
{
	indexTriangles++;
	TriangleFaceVertex.resize(indexTriangles);
	TriangleFaceTexture.resize(indexTriangles);
	TriangleFaceNormal.resize(indexTriangles);
	TriangleFaceVertex.at(indexTriangles - 1) = InfoTriangleFaceVertex;
	TriangleFaceVertex.at(indexTriangles - 1) = InfoTriangleFaceTexture;
	TriangleFaceVertex.at(indexTriangles - 1) = InfoTriangleFaceNormal;
}

void Vertex::AddNew(vec3 Vertice, vec3 Normals, vec2 UV, vec3 TriangleFaceV, vec3 TriangleFaceT, vec3 TriangleFaceN)
{
	if (Vertice != Nullable3)
		AddVertex(Vertice);
	if (Normals != Nullable3)
		AddNormals(Normals);
	if (UV != Nullable2)
		AddUV(UV);
	if (TriangleFaceV != Nullable3 && TriangleFaceT != Nullable3 && TriangleFaceN != Nullable3)
		AddTriangleFaces(TriangleFaceV, TriangleFaceT, TriangleFaceN);
}

void Vertex::AddNew(float x, float y, float z, float nx, float ny, float nz, float u, float v, vec3 TriangleFaceV, vec3 TriangleFaceT, vec3 TriangleFaceN)
{
	vec3 Vertice = { x, y, z };
	vec3 Normales = { nx, ny, nz };
	vec2 Uvs = { u, v };
	AddNew(Vertice, Normales, Uvs, TriangleFaceV, TriangleFaceT, TriangleFaceN);
}





void Vertex::AddNewTriangle(float tv1, float tv2, float tv3, float tt1, float tt2, float tt3, float tn1, float tn2, float tn3)
{
	vec3 TriangleFaceV = { tv1, tv2, tv3 };
	vec3 TriangleFaceT = { tt1, tt2, tt3 };
	vec3 TriangleFaceN = { tn1, tn2, tn3 };
	AddNew(Nullable3, Nullable3, Nullable2, TriangleFaceV, TriangleFaceT, TriangleFaceN);
}

void Vertex::AddNewTriangle(vec3 TriangleFaceV, vec3 TriangleFaceT, vec3 TriangleFaceN)
{
	AddNew(Nullable3, Nullable3, Nullable2, TriangleFaceV, TriangleFaceT, TriangleFaceN);
}

void Vertex::AddNewVertex(float x, float y, float z)
{
	vec3 Vertice = { x, y, z };
	AddNew(Vertice, Nullable3, Nullable2, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewIndex(int value)
{
	AddIndex(value);
}

void Vertex::AddNewVertex(vec3 Vertice)
{
	AddNew(Vertice, Nullable3, Nullable2, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewVertex(XMFLOAT4 Vertice)
{
	AddNew(vec3(Vertice.x,Vertice.y,Vertice.z), Nullable3, Nullable2, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewColor(float r, float g, float b, float a)
{
	vec4 Texture = { r, g, b,a };
	AddNew(Nullable3, Nullable3, Texture, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewTexture(float x, float y, float z)
{
	vec3 Texture = { x, y, z };
	AddNew(Nullable3, Nullable3, Texture, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewTexture(vec2 Texture)
{
	AddNew(Nullable3, Nullable3, Texture, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewTexture(XMFLOAT4 Texture)
{
	AddNew(Nullable3, Nullable3, vec2(Texture.x,Texture.y), Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewNormals(float x, float y, float z)
{
	vec3 Normals = { x, y, z };
	AddNew(Nullable3, Normals, Nullable2, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewNormals(vec3 Normals)
{
	AddNew(Nullable3, Normals, Nullable2, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewNormals(XMFLOAT4 Normals)
{
	AddNew(Nullable3, vec3(Normals.x,Normals.y,Normals.z), Nullable2, Nullable3, Nullable3, Nullable3);
}



void Vertex::AddPack(float x, float y, float z, float nx, float ny, float nz, float tx, float ty, float tz, float u, float v)
{
	vec3 Vertice = { x, y, z };
	vec3 Normales = { nx, ny, nz };
	vec2 Uvs = { u, v };
	vec3 Triangles = { tx, ty, tz };
	AddNew(Vertice, Normales, Uvs, Triangles, Triangles, Triangles);
}

void Vertex::AddPack(float x, float y, float z, float nx, float ny, float nz, float u, float v)
{
	vec3 Vertice = { x, y, z };
	vec3 Normales = { nx, ny, nz };
	vec2 Uvs = { u, v };
	AddNew(Vertice, Normales, Uvs, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddPack(vec3 Vertice, vec3 Normales, vec3 Triangles, vec2 Uvs)
{
	AddNew(Vertice, Normales, Uvs, Triangles, Triangles, Triangles);
}

void Vertex::AddPack(vec3 Vertice, vec2 Uvs, vec3 Normales)
{
	AddNew(Vertice, Normales, Uvs, Nullable3, Nullable3, Nullable3);
}



vec3 Vertex::GetVertex(int index)
{
	if (VertexCount == 0)
		return Nullable3;
	else
		return vertices[index];
}

vec3 Vertex::GetFirstVertex()
{
	if (VertexCount == 0)
		return Nullable3;
	else
		return vertices[0];
}

vec3 Vertex::GetLastVertex()
{
	if (VertexCount == 0)
		return Nullable3;
	else
		return vertices.at(VertexCount - 1);
}

vec2 Vertex::GetTexture(int index)
{
	if (indexUv == 0)
		return Nullable2;
	else
		return uv[index];
}

vec2 Vertex::GetFirstTexture()
{
	if (indexUv == 0)
		return Nullable2;
	else
		return uv[0];
}

vec2 Vertex::GetLastTexture()
{
	if (indexUv == 0)
		return Nullable2;
	else
		return uv.at(indexUv - 1);
}

vec3 Vertex::GetNormal(int index)
{
	if (indexNormals == 0)
		return Nullable3;
	else
		return normal.at(index);
}

vec3 Vertex::GetFirstNormal()
{
	if (indexNormals == 0)
		return Nullable3;
	else
		return normal[0];
}

vec3 Vertex::GetLastNormal()
{
	if (indexNormals == 0)
		return Nullable3;
	else
		return normal.at(indexNormals - 1);
}




vec3 Vertex::GetTriangleFV(int index)
{
	return TriangleFaceVertex.at(index);
}

vec3 Vertex::GetTriangleFT(int index)
{
	return TriangleFaceTexture.at(index);
}

vec3 Vertex::GetTriangleFN(int index)
{
	return TriangleFaceNormal.at(index);
}





vec4 Vertex::Count()
{
	vec4 indices;
	indices.x = VertexCount;
	indices.y = indexUv;
	indices.z = indexNormals;
	indices.w = indexTriangles;
	return indices;
}

vec4 Vertex::Count(int Index)
{
	vec4 indices;
	indices.x = Index;
	indices.y = Index;
	indices.z = Index;
	indices.w = Index;
	return indices;
}

int Vertex::GetSizeComponents()
{
	return (sizeof(vertices) + sizeof(uv) + sizeof(normal) + sizeof(TriangleFaceVertex) + sizeof(TriangleFaceTexture) + sizeof(TriangleFaceNormal));
}

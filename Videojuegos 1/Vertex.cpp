#include "stdafx.h"

Vertex::Vertex()
{
	indexVertex = 0;
	indexNormals = 0;
	indexUv = 0;
	indexTriangles = 0;
	vertices.clear();
	normal.clear();
	uv.clear();
	TriangleFaceVertex.clear();
	TriangleFaceTexture.clear();
	TriangleFaceNormal.clear();
	Nullable3 = { 0,0,0 };
	Nullable2 = { 0,0 };
}

void Vertex::AddVertex(vec3 InfoVertex)
{
	indexVertex++;
	vertices.resize(indexVertex);
	vertices.at(indexVertex - 1) = InfoVertex;
}

void Vertex::AddNormals(vec3 InfoNormal)
{
	indexNormals++;
	normal.resize(indexNormals);
	normal.at(indexNormals - 1) = InfoNormal;
}

void Vertex::AddUV(vec2 InfoUv)
{
	indexUv++;
	uv.resize(indexUv);
	uv.at(indexUv - 1) = InfoUv;
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

void Vertex::AddNewVertex(vec3 Vertice)
{
	AddNew(Vertice, Nullable3, Nullable2, Nullable3, Nullable3, Nullable3);
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

void Vertex::AddNewNormals(float x, float y, float z)
{
	vec3 Normals = { x, y, z };
	AddNew(Nullable3, Normals, Nullable2, Nullable3, Nullable3, Nullable3);
}

void Vertex::AddNewNormals(vec3 Normals)
{
	AddNew(Nullable3, Normals, Nullable2, Nullable3, Nullable3, Nullable3);
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
	if (indexVertex == 0)
		return Nullable3;
	else
		return vertices[index];
}

vec3 Vertex::GetFirstVertex()
{
	if (indexVertex == 0)
		return Nullable3;
	else
		return vertices[0];
}

vec3 Vertex::GetLastVertex()
{
	if (indexVertex == 0)
		return Nullable3;
	else
		return vertices.at(indexVertex - 1);
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
	indices.x = indexVertex;
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

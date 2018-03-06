#pragma once
#ifndef _Vertex_H_
#define _Vertex_H_
#include "glm/glm.hpp"
#include <vector>
using std::vector;
using namespace glm;
class Vertex {
protected:
	vector<vec3> vertices, normal, TriangleFaceVertex, TriangleFaceTexture, TriangleFaceNormal;
	vector<unsigned long> indices;
	vector<vec2> uv;
	vector<vec4> color;
	int indexNormals, indexUv, indexTriangles;
public:
	Vertex();
	unsigned long IndexCount, VertexCount;
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};
	vector<VertexType> FinalMesh;
	vector<VertexType> VertexResult();
	vector<unsigned long> IndexResult();
	vector<unsigned long> GetIndex();

	vec3 GetVertex(int indexArray);

	vec4 GetColor(int indexArray);

	vec2 GetTexture(int indexArray);

	vec3 GetNormal(int indexArray);

	vec3 GetFirstVertex();

	vec2 GetFirstTexture();

	vec3 GetFirstNormal();

	vec3 GetLastVertex();

	vec2 GetLastTexture();

	vec3 GetLastNormal();


	void SetVertexTextureNormalColor(int index, vec3 vertex, vec2 uv, vec3 normal, vec4 col);

	vec4 GetAllIndex();

	vec3 GetTriangleFV(int);

	vec3 GetTriangleFT(int);

	vec3 GetTriangleFN(int);

	void AddVertex(float x, float y, float z);

	void AddVertex(vec3 VertexVec);

	void AddVertex(XMFLOAT3 VertexVec);

	void AddVertex(XMFLOAT4 VertexVec);

	void AddColor(float r, float g, float b, float a);

	void AddColor(vec4 ColorVec);

	void AddColor(XMFLOAT4 ColorVec);

	void AddUV(float u, float v);

	void AddUV(vec2 UvVec);

	void AddUV(XMFLOAT2 UvVec);

	void AddNormals(float x, float y, float z);

	void AddNormals(vec3 NormalVec);

	void AddNormals(XMFLOAT3 NormalVec);

	void AddNormals(XMFLOAT4 NormalVec);
	
	void AddIndex(int value);

	void AddTriangleFaces(float TIndex1, float TIndex2, float TIndex3,
		float TTextures1, float TTextures2, float TTextures3,
		float TNormal1, float TNormal2, float TNormal3);

	void AddTriangleFaces(vec3 TriangleVertex, vec3 TriangleTexture, vec3 TriangleNormal);

	void ConstructIndexFromTriangles(vec3 Vertex, vec4 color, vec2 Uv, vec3 Normal);

	int sizeClass();

	void SpecialIndexVector();

	vector<vec3> SpecialGetVertex();

	vector<vec2> SpecialGetUV();

	vector<unsigned long>* SpecialGetIndexVector();

};
#endif
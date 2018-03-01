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
	vector<vec4> Color;
	vec3 Nullable3;
	vec2 Nullable2;
	int indexNormals, indexUv, indexTriangles;
	
private:

	void AddVertex(vec3);

	void AddIndex(int);

	void AddNormals(vec3);

	void AddUV(vec2);

	void AddTriangleFaces(vec3, vec3, vec3);

	void AddNew(vec3, vec3, vec2, vec3, vec3, vec3);

	void AddNew(float, float, float, float, float, float, float, float, vec3, vec3, vec3);


public:
	Vertex();
	int IndexCount, VertexCount;
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};
	vector<VertexType> VertexResult();
	vector<unsigned long> IndexResult();
	vector<unsigned long> GetIndex();

	void AddColor(vec4);

	void AddNewTriangle(float, float, float, float, float, float, float, float, float);

	void AddNewTriangle(vec3, vec3, vec3);

	void AddNewVertex(float, float, float);

	void AddNewIndex(int);

	void AddNewVertex(vec3);

	void AddNewVertex(XMFLOAT4);

	void AddNewColor(float, float, float, float);

	void AddNewTexture(float, float, float);

	void AddNewTexture(vec2);

	void AddNewTexture(XMFLOAT4);

	void AddNewNormals(float, float, float);

	void AddNewNormals(vec3);

	void AddNewNormals(XMFLOAT4);

	void AddPack(float, float, float, float, float, float, float, float, float, float, float);

	void AddPack(float, float, float, float, float, float, float, float);

	void AddPack(vec3, vec2, vec3);

	void AddPack(vec3, vec3, vec3, vec2);


	vec3 GetVertex(int);

	vec3 GetFirstVertex();

	vec3 GetLastVertex();

	vec2 GetTexture(int);

	vec4 GetColor(int);

	vec2 GetFirstTexture();

	vec2 GetLastTexture();

	vec3 GetNormal(int);

	vec3 GetFirstNormal();

	vec3 GetLastNormal();



	vec3 GetTriangleFV(int);

	vec3 GetTriangleFT(int);

	vec3 GetTriangleFN(int);

	vec4 Count();


	vec4 Count(int Index);



	int GetSizeComponents();


};
#endif
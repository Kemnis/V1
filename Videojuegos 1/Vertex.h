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
	vector<vec2> uv;
	vec3 Nullable3;
	vec2 Nullable2;
	int indexVertex, indexNormals, indexUv, indexTriangles;
private:

	void AddVertex(vec3);

	void AddNormals(vec3);

	void AddUV(vec2);

	void AddTriangleFaces(vec3, vec3, vec3);

	void AddNew(vec3, vec3, vec2, vec3, vec3, vec3);

	void AddNew(float, float, float, float, float, float, float, float, vec3, vec3, vec3);


public:
	Vertex();
	void AddNewTriangle(float, float, float, float, float, float, float, float, float);

	void AddNewTriangle(vec3, vec3, vec3);

	void AddNewVertex(float, float, float);

	void AddNewVertex(vec3);

	void AddNewTexture(float, float, float);

	void AddNewTexture(vec2);

	void AddNewNormals(float, float, float);

	void AddNewNormals(vec3);

	void AddPack(float, float, float, float, float, float, float, float, float, float, float);

	void AddPack(float, float, float, float, float, float, float, float);

	void AddPack(vec3, vec2, vec3);

	void AddPack(vec3, vec3, vec3, vec2);


	vec3 GetVertex(int);

	vec3 GetFirstVertex();

	vec3 GetLastVertex();

	vec2 GetTexture(int);

	vec2 GetFirstTexture();

	vec2 GetLastTexture();

	vec3 GetNormal(int);

	vec3 GetFirstNormal();

	vec3 GetLastNormal();



	vec3 GetTriangleFV(int);

	vec3 GetTriangleFT(int);

	vec3 GetTriangleFN(int);

	vec4 Count();

	int IndexCount();

	vec4 Count(int Index);



	int GetSizeComponents();


};
#endif
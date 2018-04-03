#pragma once
#ifndef _Model_H_
#define _Model_H_
#include "Vertex.h"
#include "Transforms.h"
class Model : DxComponent<Model>, Transforms
{
public:
	Model(int Cells, int CellSize);
	Model(string path);
	~Model();
	bool Initialize(string primitive);
	void Draw();
	void BindMesh(D3D_PRIMITIVE_TOPOLOGY TOPOLOGY);
	void ShutdownModel();
	Vertex GetMesh();
	string Name;
	string Type;
protected:

	Vertex Mesh;
	ID3D11Buffer *VertexBuffer, *IndexBuffer;
private:
	bool LoadModel(string);
	void DefineTerrain(int Cells, int CellSize);
	void DefineTriangle();
	void DefineSquare();
	void DefineCube(XMFLOAT3 size);
	void DefineSphere(float diameter, size_t tessellation);
	void DefineGeoSphere(float diameter, size_t tessellation);
};


#endif
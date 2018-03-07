#pragma once
#ifndef _Model_H_
#define _Model_H_
#include "Vertex.h"
#include "Transforms.h"
class Model : DxComponent<Model>, Transforms
{
public:
	Model(string path);
	~Model();
	bool Initialize(string primitive);
	void Draw();
	void BindMesh();
	void ShutdownModel();
	Vertex GetMesh();
	string Name;
protected:

	Vertex MeshVertex;
	ID3D11Buffer *VertexBuffer, *IndexBuffer;
private:
	bool LoadModel(string);
};


#endif
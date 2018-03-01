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
	bool Initialize();
	void Draw();
	void BindMesh();
	void ShutdownModel();
	string Name;
	Transforms* transform;
protected:

	ID3D11Buffer *VertexBuffer, *IndexBuffer;
private:
	Vertex MeshVertex;
	bool LoadModel(string);
};


#endif
#pragma once
#include "Vertex.h"
#include "Transforms.h"
#include "RawImage.h"
class Model : DxComponent<Model>, Transforms
{
public:
	Model(string HeightmapFile,float Cells, float Width,float Height);
	Model(string path);
	Model(vec2 coordPositivo, vec2 coordNegativo);//<-Widt and Height my Billboard
	~Model();
	bool Initialize(string primitive);
	void Draw();
	void BindMesh(D3D_PRIMITIVE_TOPOLOGY TOPOLOGY);
	void ShutdownModel();
	float GetPositionHeightMap(vec2 pos);
	bool isIntoTerrain(vec3 pos);
	Vertex GetMesh();
	string Name;
	string Type;
	RawImage Heightmap;
	vec2 SizeXZ;
	vec2 coordPositivo, coordNegativo;
protected:

	Vertex Mesh;
	ID3D11Buffer *VertexBuffer, *IndexBuffer;
private:
	bool LoadModel(string);
	void DefineTerrain(float Cells, float Width, float Height, string HeightmapFile);
	void DefineTriangle();
	void DefineSquare();
	void DefineCube(XMFLOAT3 size);
	void DefineSphere(float diameter, size_t tessellation);
	void DefineGeoSphere(float diameter, size_t tessellation);
	void DefineBillboard();
	bool CalculateNormalsTerrain(float CellSize);
};



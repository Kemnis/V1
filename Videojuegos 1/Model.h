#pragma once
#include "Vertex.h"
#include "Transforms.h"
#include "RawImage.h"
class Model : DxComponent<Model>, Transforms
{
public:
	Model(string HeightmapFile,float Cells, float Width,float Height);
	Model(string path);
	Model(vec2 coordPositivo, vec2 coordNegativo);//<-Width and Height my Billboard
	Model(vec4 rectBitmap, int widthScreen, int heightScreen);
	~Model();
	bool Initialize(string primitive);
	void Draw();
	void BindMesh(D3D_PRIMITIVE_TOPOLOGY TOPOLOGY);
	void ShutdownModel();
	float GetPositionHeightMap(vec3 pos);
	bool isIntoTerrain(vec3 pos);
	bool UpdateBufferBitmap(vec4 rectBitmap, int widthScreen, int heightScreen);
	Vertex GetMesh();
	string Name;
	string Type;
	RawImage Heightmap;
	vec2 SizeXZ;
	vec2 coordPositivo, coordNegativo;
	vec4 rectBitmap;
protected:
	bool dynamicVertexBuffer;//<- For re-position bitmap2D
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
	void DefineBitmap(vec4 rectBitmap, int widthScreen, int heightScreen);
};



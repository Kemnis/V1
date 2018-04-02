#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;
class Terrain: public DxComponent<Terrain>
{
public:
	Terrain();
	~Terrain();

	string Name;
	bool Initialize(int Cells, int CellSize, int Size);
	void Shutdown();
	void Draw();
	void BindMesh();
	Vertex GetMesh();
private:

protected:
	Vertex Mesh;
	ID3D11Buffer *VertexBuffer, *IndexBuffer;
};
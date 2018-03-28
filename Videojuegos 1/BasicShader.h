#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "Material.h"
using namespace DirectX;
using namespace std;
class BasicShader : public DxComponent<BasicShader>
{
private:
	struct InfoBufferType
	{
		XMMATRIX projectionViewWorld;
		Material* material;
	};

public:
	BasicShader();
	~BasicShader();

	bool Initialize();
	void Shutdown();
	void BindShader();

	bool SetShaderParameters(XMMATRIX, XMMATRIX, XMMATRIX, Material* material);
	string Name;
private:
	void OutputShaderErrorMessage(ID3D10Blob*, LPCTSTR);
	std::wstring s2ws(const std::string& s);

private:
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* Layout;
	ID3D11Buffer* m_matrixBuffer;
};


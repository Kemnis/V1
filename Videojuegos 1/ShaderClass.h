#ifndef _ShaderClass_H_
#define _ShaderClass_H_
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "Texture.h"
using namespace DirectX;
using namespace std;
class ShaderClass : public DxComponent<ShaderClass>
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX projectionView;
		XMMATRIX projectionViewWorld;
	};
	struct LightBufferType {
		XMFLOAT4 ambientColor;//Nueva variable para poner en el shader
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		/*float ColorDifR;
		float ColorDifG;
		float ColorDifB;
		float ColorDifA;*/
		float padding; //Added extra padding so structur is a multiple of 16 for createbuffer function requirements
	};

public:
	ShaderClass();
	~ShaderClass();

	bool Initialize();
	void Shutdown();
	void BindShader();

	bool SetShaderParameters(XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView* texture);
	string Name;
private:
	void OutputShaderErrorMessage(ID3D10Blob*, LPCTSTR);
	std::wstring s2ws(const std::string& s);

private:
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* Layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* Sampler;
	ID3D11Buffer* lightBuffer;
};

#endif
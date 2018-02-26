#ifndef _ShaderClass_H_
#define _ShaderClass_H_
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
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

public:
	ShaderClass();
	~ShaderClass();

	bool Initialize();
	void Shutdown();
	void BindShader();
	
	bool SetShaderParameters(XMMATRIX, XMMATRIX, XMMATRIX);

private:
	void OutputShaderErrorMessage(ID3D10Blob*, LPCTSTR);
	std::wstring s2ws(const std::string& s);

private:
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* Layout;
	ID3D11Buffer* m_matrixBuffer;
};

#endif
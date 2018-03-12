#ifndef _BasicShader_H_
#define _BasicShader_H_
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;
class BasicShader : public DxComponent<BasicShader>
{
private:
	struct MatrixBufferType
	{
		XMMATRIX projectionViewWorld;
	};

public:
	BasicShader();
	~BasicShader();

	bool Initialize();
	void Shutdown();
	void BindShader();

	bool SetShaderParameters(XMMATRIX, XMMATRIX, XMMATRIX);
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

#endif
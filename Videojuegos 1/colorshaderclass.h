#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_
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
	ShaderClass(const ShaderClass&);
	~ShaderClass();

	bool Initialize();
	void Shutdown();
	bool Render(int, const XMMATRIX*, const XMMATRIX*, const XMMATRIX*);

private:
	bool InitializeShader(string, string);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, LPCWSTR);

	bool SetShaderParameters(XMMATRIX, XMMATRIX, XMMATRIX);
	void RenderShader(int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};

#endif
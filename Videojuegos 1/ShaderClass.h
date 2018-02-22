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
	ShaderClass(const ShaderClass&);
	~ShaderClass();

	bool Initialize();
	void Shutdown();
	bool Render(const XMMATRIX*, const XMMATRIX*, const XMMATRIX*);
	void BindShader();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
	ID3D11InputLayout* GetLayout();

private:
	void OutputShaderErrorMessage(ID3D10Blob*, LPCTSTR);
	std::wstring s2ws(const std::string& s);
	bool SetShaderParameters(XMMATRIX, XMMATRIX, XMMATRIX);
	//void RenderShader(int);

private:
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* Layout;
	ID3D11Buffer* m_matrixBuffer;
};

#endif
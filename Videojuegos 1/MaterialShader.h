#ifndef _MaterialShader_H_
#define _MaterialShader_H_
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "Texture.h"
using namespace DirectX;
using namespace std;
class MaterialShader : public DxComponent<MaterialShader>
{
private:
	struct MatrixBufferType
	{
		XMMATRIX projectionViewWorld;
	};
	struct MaterialBuffer
	{
		vec3 color;
		float padding;
	};
public:
	MaterialShader();
	~MaterialShader();

	bool Initialize();
	void Shutdown();
	void BindShader();

	bool SetShaderParameters(XMMATRIX world, XMMATRIX view, XMMATRIX projection, ID3D11ShaderResourceView* texture, Material* material);
	string Name;
private:
	void OutputShaderErrorMessage(ID3D10Blob*, LPCTSTR);
	std::wstring s2ws(const std::string& s);

private:
	ID3D11VertexShader * VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* Layout;
	ID3D11Buffer* MatrixBuf;
	ID3D11Buffer* MaterialBuf;
	ID3D11SamplerState* Sampler;
};

#endif
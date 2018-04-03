#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "Material.h"
using namespace DirectX;
using namespace std;

class ConstantBufferBase : public DxComponent<ConstantBufferBase> {
private:

	
public:
	ConstantBufferBase() {

	}
	~ConstantBufferBase(){
		buffer->Release();
	}


	HRESULT CreateBuffer(unsigned int bufferSize) {
		D3D11_BUFFER_DESC matrixBufferDesc = {};
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = bufferSize;
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		return device->CreateBuffer(&matrixBufferDesc, NULL, &buffer);
	}

	ID3D11Buffer* buffer;

	virtual void Update(const void *) = 0;
};

template<typename T>
class ConstantBuffer : public ConstantBufferBase {
private:
	unsigned int structSize;

	bool Initialize() {
		HRESULT result = this->CreateBuffer(structSize);
		// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		if (FAILED(result))
		{
			return false;
		}
		return true;
	}
public:
	ConstantBuffer() {
		this->structSize = sizeof(T);
		this->Initialize();
	}

	void Update(const void* source) {
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		deviceContext->Map(this->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		T* dataPtr = (T*)mappedResource.pData;
		memcpy(dataPtr, source, sizeof(T));
		deviceContext->Unmap(this->buffer, 0);
	}
};

class Shader : public DxComponent<Shader>
{
private:
	struct MatrixConstantBuffer
	{
		XMMATRIX projectionViewWorld;
	};

public:
	Shader(std::string, std::string);
	~Shader();

	bool Initialize(std::string, std::string);
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
	std::vector<ConstantBufferBase*> constantBuffers;
};


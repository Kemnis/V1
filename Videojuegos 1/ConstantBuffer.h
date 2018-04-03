#pragma once

enum class ConstantBufferLocation {
	VertexShader = 1,
	PixelShader = 2
};

class ConstantBuffer : public DxComponent<ConstantBuffer> {
private:
	unsigned int structSize;

	HRESULT CreateBuffer(unsigned int bufferSize);

	bool Initialize();
public:
	unsigned int id;
	ConstantBufferLocation location;
	ConstantBuffer(unsigned int id, ConstantBufferLocation location, unsigned int bufferSize);
	~ConstantBuffer();

	void Update(const void* source);

	ID3D11Buffer* buffer;
};
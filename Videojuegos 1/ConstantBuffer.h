#pragma once

class ConstantBuffer : public DxComponent<ConstantBuffer> {
private:
	unsigned int structSize;

	HRESULT CreateBuffer(unsigned int bufferSize);

	bool Initialize();
public:
	unsigned int id;
	ConstantBuffer(unsigned int id, unsigned int bufferSize);
	~ConstantBuffer();

	void Update(const void* source);

	ID3D11Buffer* buffer;
};
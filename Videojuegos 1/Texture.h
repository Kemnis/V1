#pragma once
#ifndef _Texture_H_
#define _Texture_H_
#include "WICTextureLoader.h"
#include <vector>
using std::vector;
using namespace std;
using namespace DirectX;

class Texture : DxComponent<Texture>
{
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	Texture();
	~Texture();

	bool Initialize(WCHAR*);
	void Shutdown();

	string Name;
	ID3D11ShaderResourceView* GetTexture();

private:
	string LoadTarga(WCHAR*, int&, int&);
	string LoadTextureTarga(WCHAR*);
	string LoadTextureWic(WCHAR*);
private:
	unsigned char* m_targaData;
	ID3D11Texture2D* m_texture;
	ID3D11ShaderResourceView* m_textureView;

};

#endif
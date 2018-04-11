#include "stdafx.h"

RawImage::RawImage() {}
RawImage::RawImage(std::string fileName) {
	this->LoadBitmapFromFile(fileName);
}

bool RawImage::LoadBitmapFromFile(std::string fileName) {

	std::fstream file(fileName, std::ios::binary);
	if (!file) {
		return false;
	}
	void* headerPointer[2] = { nullptr, nullptr };
	headerPointer[0] = new byte[sizeof(BITMAPFILEHEADER)];
	headerPointer[1] = new byte[sizeof(BITMAPINFOHEADER)];

	BITMAPFILEHEADER* bmpHeader = (BITMAPFILEHEADER*)headerPointer[0];
	BITMAPINFOHEADER* bmpInfoHeader = (BITMAPINFOHEADER*)headerPointer[1];;

	if (bmpHeader->bfType != 0x4D42)
	{
		// Esto no es un bitmap!
		return false;
	}

	this->pixels.reserve(bmpInfoHeader->biSizeImage);
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)pixels[0], bmpInfoHeader->biSizeImage);

	byte tempPixel;
	for (int i = 0; i < bmpInfoHeader->biSizeImage; i += 3) {
		tempPixel = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = tempPixel;
	}

	this->width = bmpInfoHeader->biWidth;
	this->height = bmpInfoHeader->biHeight;

	delete headerPointer[0];
	delete headerPointer[1];

	return true;
}
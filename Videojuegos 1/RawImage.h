#pragma once

#include<vector>
#include<string>

typedef unsigned char ubyte;
typedef char byte;

class RawImage {
	typedef unsigned int uint;
	uint width;
	uint height;
	std::vector<byte> pixels;

public:
	RawImage();
	RawImage(std::string fileName);
	bool LoadBitmapFromFile(std::string fileName);
};

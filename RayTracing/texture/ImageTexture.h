#pragma once
#include "Texture.h"
class ImageTexture :
	public Texture
{
public:
	ImageTexture();
	ImageTexture(unsigned char* pixels, int a, int b);
	Vector3 Value(float u, float v, const Vector3& p)const override;
private:
	unsigned char* data;
	int nx, ny;
};


#include "ImageTexture.h"

ImageTexture::ImageTexture():data(nullptr),nx(0),ny(0)
{
}

ImageTexture::ImageTexture(unsigned char* pixels, int a, int b):data(pixels),nx(a),ny(b)
{
}

Vector3 ImageTexture::Value(float u, float v, const Vector3& p) const
{
	int i = u * nx;
	int j = (1 - v) * ny - 0.001;
	i = Clamp(i, 0, nx - 1);
	j = Clamp(j, 0, ny - 1);
	float r = int(data[3 * i + 3 * nx * j]) / 255.f;
	float g = int(data[3 * i + 3 * nx * j + 1]) / 255.f;
	float b = int(data[3 * i + 3 * nx * j + 2]) / 255.f;

	return Vector3(r, g, b);
}

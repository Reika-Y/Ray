#include "ConstantTexture.h"

ConstantTexture::ConstantTexture()
{
	color = { 1.f,1.f,1.f };
}

ConstantTexture::ConstantTexture(Vector3 c)
{
	color = c;
}

Vector3 ConstantTexture::Value(float u, float v, const Vector3& p) const
{
	return color;
}

#pragma once
#include "Texture.h"

class ConstantTexture :
	public Texture
{
public:
	ConstantTexture();
	ConstantTexture(Vector3 c);
	Vector3 Value(float u, float v, const Vector3& p)const;
private:
	Vector3 color;
};


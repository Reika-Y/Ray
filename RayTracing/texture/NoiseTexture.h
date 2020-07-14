#pragma once
#include "Texture.h"
#include "Perlin.h"

class NoiseTexture :
	public Texture
{
public:
	NoiseTexture();
	NoiseTexture(float sc);
	Vector3 Value(float u, float v, const Vector3& p)const;
private:
	Perlin noise;
	float scale;
};


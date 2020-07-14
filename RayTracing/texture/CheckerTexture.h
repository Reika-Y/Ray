#pragma once
#include "Texture.h"

class CheckerTexture :
	public Texture
{
public:
	CheckerTexture();
	CheckerTexture(Texture* t0, Texture* t1);
	Vector3 Value(float u, float v, const Vector3& p)const;
private:
	Texture* odd;
	Texture* even;
};


#pragma once
#include "common/Geometry.h"

class Texture
{
public:
	virtual Vector3 Value(float u, float v, const Vector3& p)const = 0;
};


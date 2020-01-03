#include "CheckerTexture.h"
#include <math.h>

CheckerTexture::CheckerTexture()
{
}

CheckerTexture::CheckerTexture(Texture* t0, Texture* t1)
{
	even = t0;
	odd = t1;
}

Vector3 CheckerTexture::Value(float u, float v, const Vector3& p) const
{
	float sines = sinf(10 * p.x) * sinf(10 * p.y) * sinf(10 * p.z);
	if (sines < 0)
	{
		return odd->Value(u, v, p);
	}
	return even->Value(u, v, p);
}

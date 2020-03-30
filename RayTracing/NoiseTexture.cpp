#include "NoiseTexture.h"

NoiseTexture::NoiseTexture()
{
}

NoiseTexture::NoiseTexture(float sc)
{
	scale = sc;
}

Vector3 NoiseTexture::Value(float u, float v, const Vector3& p) const
{
	return Vector3(1.f, 1.f, 1.f) * 0.5f * (1 + sin(scale * p.z + 10 * noise.Turb(p)));
}

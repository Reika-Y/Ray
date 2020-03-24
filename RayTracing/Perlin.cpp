#include "Perlin.h"
#include <cmath>

Perlin::Perlin()
{
	ranfloat = PerlinGenerate();
	perm_x = PerlinGeneratePerm();
	perm_y = PerlinGeneratePerm();
	perm_z = PerlinGeneratePerm();
}

float Perlin::Noise(const Vector3& p) const
{
	float u = p.x - floor(p.x);
	float v = p.y - floor(p.y);
	float w = p.z - floor(p.z);
	int i = int(4 * p.x) & 255;
	int j = int(4 * p.y) & 255;
	int k = int(4 * p.z) & 255;
	return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}

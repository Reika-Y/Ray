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
	int i = int(floor(p.x));
	int j = int(floor(p.y));
	int k = int(floor(p.z));
	float c[2][2][2];
	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
			{
				c[di][dj][dk] = ranfloat[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
			}
		}
	}
	return TrilinearInterp(c, u, v, w);
}

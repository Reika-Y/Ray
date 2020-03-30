#include "Perlin.h"

Vector3* Perlin::ranvec = PerlinGenerate();
int* Perlin::perm_x = PerlinGeneratePerm();
int* Perlin::perm_y = PerlinGeneratePerm();
int* Perlin::perm_z = PerlinGeneratePerm();

float Perlin::Noise(const Vector3& p) const
{
	float u = p.x - floor(p.x);
	float v = p.y - floor(p.y);
	float w = p.z - floor(p.z);
	int i = int(floor(p.x));
	int j = int(floor(p.y));
	int k = int(floor(p.z));
	Vector3 c[2][2][2];
	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
			{
				c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
			}
		}
	}
	return PerlinInterp(c, u, v, w);
}

float Perlin::Turb(const Vector3& p, int depth)const
{
	float accum = 0.f;
	Vector3 temp_p = p;
	float weight = 1.f;
	for (int i = 0; i < depth; i++)
	{
		accum += weight * Noise(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}
	accum = fabs(accum);
	accum = Clamp(accum, 0, 1);
	return accum;
}

#include "Perlin.h"
#include <cmath>

Perlin::Perlin()
{
	ranvec = PerlinGenerate();
	perm_x = PerlinGeneratePerm();
	perm_y = PerlinGeneratePerm();
	perm_z = PerlinGeneratePerm();
}

float Perlin::Noise(const Vector3& p) const
{
	float u = p.x - floor(p.x);
	float v = p.y - floor(p.y);
	float w = p.z - floor(p.z);
	int i = floor(p.x);
	int j = floor(p.y);
	int k = floor(p.z);
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
	return TrilinearInterp(c, u, v, w);
}

Vector3* PerlinGenerate(void)
{
	Vector3* p = new Vector3[256];
	for (int i = 0; i < 256; i++)
	{
		p[i] = { -1 + 2 * DRand(),-1 + 2 * DRand(),-1 + 2 * DRand() };
		p[i].Normalize();
	}
	return p;
}

void Permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = static_cast<int>(DRand() * (i + 1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
	return;
}

int* PerlinGeneratePerm(void)
{
	int* p = new int[256];
	for (int i = 0; i < 256; i++)
	{
		p[i] = i;
	}
	Permute(p, 256);
	return p;
}

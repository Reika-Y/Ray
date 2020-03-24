#pragma once
#include <stdlib.h>
#include "common/Geometry.h"

inline float TrilinearInterp(float c[2][2][2], float u, float v, float w)
{
	float accum = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				accum += (i * u + (1 - i) * (1 - u)) *
						 (j * v + (1 - j) * (1 - v)) *
						 (k * w + (1 - k) * (1 - w)) * c[i][j][k];
			}
		}
	}
	return accum;
}

class Perlin
{
public:
	Perlin();
	float Noise(const Vector3& p)const;

private:
	float* ranfloat;
	int* perm_x;
	int* perm_y;
	int* perm_z;
};

static float* PerlinGenerate()
{
	float* p = new float[256];
	for (int i = 0; i < 256; i++)
	{
		p[i] = DRand();
	}
	return p;
}

static void Permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = int(DRand() * (i + 1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
	return;
}

static int* PerlinGeneratePerm()
{
	int* p = new int[256];
	for (int i = 0; i < 256; i++)
	{
		p[i] = i;
	}
	Permute(p, 256);
	return p;
}

#pragma once
#include <math.h>
#include "../common/Geometry.h"

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

inline float PerlinInterp(Vector3 c[2][2][2], float u, float v, float w)
{
	float uu = u * u * (3 - 2 * u);
	float vv = v * v * (3 - 2 * v);
	float ww = w * w * (3 - 2 * w);
	float accum = 0.f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Vector3 weight_v(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu)) *
						 (j * vv + (1 - j) * (1 - vv)) *
						 (k * ww + (1 - k) * (1 - ww)) * Dot(c[i][j][k], weight_v);
			}
		}
	}

	return accum;
}

class Perlin
{
public:
	float Noise(const Vector3& p)const;
	float Turb(const Vector3& p, int depth = 7)const;

	static Vector3* ranvec;
	static int* perm_x;
	static int* perm_y;
	static int* perm_z;
};

static Vector3* PerlinGenerate()
{
	Vector3* p = new Vector3[256];
	for (int i = 0; i < 256; i++)
	{
		p[i] = Vector3(-1 + 2 * DRand(), -1 + 2 * DRand(), -1 + 2 * DRand());
		p[i].Normalize();
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


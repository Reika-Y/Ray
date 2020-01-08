#pragma once
#include "common/Geometry.h"

inline float TrilinearInterp(Vector3 c[2][2][2], float u, float v, float w)
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
				Vector3 weight(u - i,v - j,w - k );
				accum += (i * uu + (1 - i) * (1 - uu)) *
						 (j * vv + (1 - j) * (1 - vv)) *
						 (k * ww + (1 - k) * (1 - ww)) * Dot(c[i][j][k], weight);
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
	Vector3* ranvec;
	int* perm_x;
	int* perm_y;
	int* perm_z;
};

Vector3* PerlinGenerate(void);
void Permute(int* p, int n);
int* PerlinGeneratePerm(void);


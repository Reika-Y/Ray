#pragma once
#include "common/Geometry.h"

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

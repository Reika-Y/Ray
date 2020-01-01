#pragma once
#include "common/Geometry.h"

class Ray;

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class AABB
{
public:
	AABB();
	AABB(const Vector3& a, const Vector3& b);

	Vector3 Min(void);
	Vector3 Max(void);

	bool Hit(const Ray& r, float tmin, float tmax)const;

private:
	Vector3 _min;
	Vector3 _max;
};

AABB SurroudingBox(AABB box0, AABB box1);

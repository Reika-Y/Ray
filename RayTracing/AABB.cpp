#include <math.h>
#include "AABB.h"
#include "Ray.h"

AABB::AABB()
{
	_min = Vector3{ 0.f,0.f,0.f };
	_max = Vector3{ 0.f,0.f,0.f };
}

AABB::AABB(const Vector3& a, const Vector3& b)
{
	_min = a;
	_max = b;
}

Vector3 AABB::Min(void)
{
	return _min;
}

Vector3 AABB::Max(void)
{
	return _max;
}

bool AABB::Hit(const Ray& r, float tmin, float tmax)const
{
	for (int a = 0; a < 3; a++)
	{
		float t0 = ffmin((_min.x - r.Origin().x) / r.Direction().x,
						 (_max.x - r.Origin().x) / r.Direction().x);
		float t1 = ffmax((_min.x - r.Origin().x) / r.Direction().x,
						 (_max.x - r.Origin().x) / r.Direction().x);
		tmin = ffmax(t0, tmin);
		tmax = ffmin(t1, tmax);
		if (tmax <= tmin)
		{
			return false;
		}
	}
	return true;
}

AABB SurroudingBox(AABB box0, AABB box1)
{
	Vector3 small{
		fminf(box0.Min().x,box1.Min().x),
		fminf(box0.Min().y,box1.Min().y),
		fminf(box0.Min().z,box1.Min().z)
	};
	Vector3 big{
		fmaxf(box0.Max().x,box1.Max().x),
		fmaxf(box0.Max().y,box1.Max().y),
		fmaxf(box0.Max().z,box1.Max().z)
	};
	return AABB(small, big);
}

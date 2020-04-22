#include "FlipNormals.h"

bool FlipNormals::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	if (_ptr->Hit(ray, t_min, t_max, rec))
	{
		rec.normal = -rec.normal;
		return true;
	}
	return false;
}

bool FlipNormals::BoundingBox(float t0, float t1, AABB& box) const
{
	return _ptr->BoundingBox(t0, t1, box);
}

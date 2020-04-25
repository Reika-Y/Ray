#include "Translate.h"
#include "../AABB.h"

Translate::Translate(ShapePtr p, const Vector3& displacement)
{
	_ptr = p;
	_offset = displacement;
}

bool Translate::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	Ray moved_r(ray.Origin() - _offset, ray.Direction(), ray.Time());
	if ((*_ptr).Hit(moved_r, t_min, t_max, rec))
	{
		rec.p += _offset;
		return true;
	}
	return false;
}

bool Translate::BoundingBox(float t0, float t1, AABB& box) const
{
	if ((*_ptr).BoundingBox(t0, t1, box))
	{
		box = AABB(box.Min() + _offset, box.Max() + _offset);
		return true;
	}
	return false;
}

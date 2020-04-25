#pragma once
#include "HitRecord.h"

class Translate :
	public Shape
{
public:
	Translate(ShapePtr p, const Vector3& displacement);
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	ShapePtr _ptr;
	Vector3 _offset;
};
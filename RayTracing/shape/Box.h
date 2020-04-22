#pragma once
#include "HitRecord.h"

class ShapeList;

class Box :
	public Shape
{
public:
	Box();
	Box(const Vector3& p0, const Vector3& p1, const std::shared_ptr<Material>& mat);
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	Vector3 _pmin, _pmax;
	ShapeList *list;
};
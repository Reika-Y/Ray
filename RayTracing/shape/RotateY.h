#pragma once
#include "HitRecord.h"
#include "../AABB.h"

// Y軸回転した物体
class RotateY :
	public Shape
{
public:
	RotateY(ShapePtr p, float angle);
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	ShapePtr _ptr;
	float _sin;
	float _cos;
	bool _isbox;
	AABB _bbox;
};
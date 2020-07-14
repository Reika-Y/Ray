#pragma once
#include "HitRecord.h"
#include "../texture/Texture.h"

class ConstantMedium :
	public Shape
{
public:
	ConstantMedium(ShapePtr p, float d, Texture* a);
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	ShapePtr _ptr;
	float _density;
	std::shared_ptr<Material>_phaseFunction;
};
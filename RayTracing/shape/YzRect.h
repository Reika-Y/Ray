#pragma once 
#include "HitRecord.h"

class YzRect :public Shape
{
public:
	YzRect();
	YzRect(float y0, float y1, float z0, float z1, float k, const std::shared_ptr<Material>& mat);
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	std::shared_ptr<Material> _mat;
	float _y0, _y1, _z0, _z1, _k;
};
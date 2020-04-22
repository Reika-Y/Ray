#pragma once
#include "HitRecord.h"

class FlipNormals 
	:public Shape
{
public:
	FlipNormals(Shape*p):_ptr(p){}
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	Shape* _ptr;
};
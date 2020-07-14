#pragma once
#include "HitRecord.h"
#include "../AABB.h"

class BvhNode :
	public Shape
{
public:
	BvhNode(Shape** l, int n, float time0, float time1);
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:

	Shape* left;
	Shape* right;
	AABB box;
};

int BoxXCompare(const void* a, const void* b);
int BoxYCompare(const void* a, const void* b);
int BoxZCompare(const void* a, const void* b);

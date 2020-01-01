#include "BvhNode.h"
#include "../common/Geometry.h"

BvhNode::BvhNode()
{
}

BvhNode::BvhNode(Shape** l, int n, float time0, float time1)
{
	int axis = static_cast<int>(3 * DRand());
	if (axis == 0)
	{
		qsort(l, n, sizeof(Shape*), BoxXCompare);
	}
	else if (axis == 1)
	{
		qsort(l, n, sizeof(Shape*), BoxYCompare);
	}
	else
	{
		qsort(l, n, sizeof(Shape*), BoxZCompare);
	}

	if (n == 1)
	{
		left = right = l[0];
	}
	else if (n == 2)
	{
		left = l[0];
		right = l[1];
	}
	else
	{
		left = new BvhNode(l, n / 2, time0, time1);
		right = new BvhNode(l + n / 2, n - n / 2, time0, time1);
	}
	AABB boxLeft, boxRight;
	if (!left->BoundingBox(time0, time1, boxLeft) || !right->BoundingBox(time0, time1, boxRight))
	{
		// error
	}
	box = SurroudingBox(boxLeft, boxRight);
}

bool BvhNode::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	if (box.Hit(ray, t_min, t_max))
	{
		HitRecord l_rec, r_rec;
		bool hit_l = left->Hit(ray, t_min, t_max, l_rec);
		bool hit_r = right->Hit(ray, t_min, t_max, r_rec);
		if (hit_l && hit_r)
		{
			if (l_rec.t < r_rec.t)
			{
				rec = l_rec;
			}
			else
			{
				rec = r_rec;
			}
			return true;
		}
		else if (hit_l)
		{
			rec = l_rec;
			return true;
		}
		else if (hit_r)
		{
			rec = r_rec;
			return true;
		}
	}
	return false;
}

bool BvhNode::BoundingBox(float t0, float t1, AABB& box) const
{
	box = BvhNode::box;
	return true;
}

int BoxXCompare(const void* a, const void* b)
{
	AABB boxLeft, boxRight;
	Shape* as = *(Shape**)a;
	Shape* bs = *(Shape**)b;
	if (!as->BoundingBox(0, 0, boxLeft) || !bs->BoundingBox(0, 0, boxRight))
	{
		// error
	}
	if ((boxLeft.Min().x - boxRight.Min().x) < 0.f)
	{
		return -1;
	}
	return 1;
}

int BoxYCompare(const void* a, const void* b)
{
	AABB boxLeft, boxRight;
	Shape* as = *(Shape * *)a;
	Shape* bs = *(Shape * *)b;
	if (!as->BoundingBox(0, 0, boxLeft) || !bs->BoundingBox(0, 0, boxRight))
	{
		// error
	}
	if ((boxLeft.Min().y - boxRight.Min().y) < 0.f)
	{
		return -1;
	}
	return 1;
}

int BoxZCompare(const void* a, const void* b)
{
	AABB boxLeft, boxRight;
	Shape* as = *(Shape * *)a;
	Shape* bs = *(Shape * *)b;
	if (!as->BoundingBox(0, 0, boxLeft) || !bs->BoundingBox(0, 0, boxRight))
	{
		// error
	}
	if ((boxLeft.Min().z - boxRight.Min().z) < 0.f)
	{
		return -1;
	}
	return 1;
}

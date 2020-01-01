#include "ShapeList.h"
#include "../Ray.h"
#include "../AABB.h"

ShapeList::ShapeList()
{
}

ShapeList::~ShapeList()
{
}

bool ShapeList::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	HitRecord tmpRecord;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for (auto& shape : _shapes)
	{
		if ((*shape).Hit(ray, t_min, closest_so_far, tmpRecord))
		{
			hit_anything = true;
			closest_so_far = tmpRecord.t;
			rec = tmpRecord;
		}
	}
	return hit_anything;
}

void ShapeList::Add(const ShapePtr& shape)
{
	_shapes.emplace_back(shape);
}

bool ShapeList::BoundingBox(float t0, float t1, AABB& box) const
{
	if (!_shapes.size())
	{
		return false;
	}

	AABB tmpBox;
	bool firstTrue = _shapes[0]->BoundingBox(t0, t1, tmpBox);
	if (!firstTrue)
	{
		return false;
	}
	else
	{
		box = tmpBox;
	}

	for (int i = 1; i < _shapes.size(); i++)
	{
		if (_shapes[0]->BoundingBox(t0, t1, tmpBox))
		{
			box = SurroudingBox(box, tmpBox);
		}
		else
		{
			return false;
		}
	}
	return true;
}

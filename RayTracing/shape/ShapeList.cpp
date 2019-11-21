#include "ShapeList.h"
#include "../Ray.h"

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

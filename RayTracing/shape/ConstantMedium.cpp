#include "ConstantMedium.h"
#include "../material/Isotropic.h"
#include <iostream>

ConstantMedium::ConstantMedium(ShapePtr p, float d, Texture* a)
{
	_ptr = p;
	_density = d;
	_phaseFunction = std::make_shared<Isotropic>(a);
}

bool ConstantMedium::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	bool db = (DRand() < 0.00001);
	db = false;
	HitRecord rec1, rec2;
	if ((*_ptr).Hit(ray, -FLT_MAX, FLT_MAX, rec1))
	{
		if ((*_ptr).Hit(ray, rec1.t + 0.001, FLT_MAX, rec2))
		{
			if (db)
			{
				std::cerr << "\nt0 t1 " << rec1.t << " " << rec2.t << "\n";
			}
			if (rec1.t < t_min)
			{
				rec1.t = t_min;
			}
			if (rec2.t > t_max)
			{
				rec2.t = t_max;
			}
			if (rec1.t >= rec2.t)
			{
				return false;
			}
			if (rec1.t < 0)
			{
				rec1.t = 0;
			}
			float distance_inside_boundary = (rec2.t - rec1.t) * ray.Direction().Length();
			float hit_distance = -(1 / _density) * log(DRand());
			if (hit_distance < distance_inside_boundary)
			{
				if (db)
				{
					std::cerr << "hit_distance = " << hit_distance << "\n";
				}
				rec.t = rec1.t + hit_distance / ray.Direction().Length();
				if (db)
				{
					std::cerr << "rec.t = " << rec.t << "\n";
				}
				rec.p = ray.PointAtParameter(rec.t);
				// arbitrary
				rec.normal = Vector3(1, 0, 0);
				rec.mat = _phaseFunction;
				return true;
			}
		}
	}
	return false;
}

bool ConstantMedium::BoundingBox(float t0, float t1, AABB& box) const
{
	return (*_ptr).BoundingBox(t0, t1, box);
}

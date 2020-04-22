#include "YzRect.h"
#include "../AABB.h"

YzRect::YzRect()
{
	_y0 = 0;
	_y1 = 0;
	_z0 = 0;
	_z1 = 0;
	_k = 0;
	_mat = nullptr;
}

YzRect::YzRect(float y0, float y1, float z0, float z1, float k, const std::shared_ptr<Material>& mat)
{
	_y0 = y0;
	_y1 = y1;
	_z0 = z0;
	_z1 = z1;
	_k = k;
	_mat = mat;
}

bool YzRect::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	float t = (_k - ray.Origin().x) / ray.Direction().x;
	if (t < t_min || t > t_max)
	{
		return false;
	}

	float y = ray.Origin().y + t * ray.Direction().y;
	float z = ray.Origin().z + t * ray.Direction().z;
	if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
	{
		return false;
	}

	rec.u = (y - _y0) / (_y1 - _y0);
	rec.v = (z - _z0) / (_z1 - _z0);
	rec.t = t;
	rec.mat = _mat;
	rec.p = ray.PointAtParameter(t);
	rec.normal = Vector3(1, 0, 0);
	return true;
}

bool YzRect::BoundingBox(float t0, float t1, AABB& box) const
{
	box = AABB(Vector3(_k - 0.0001, _y0, _z0), Vector3(_k + 0.0001, _y1, _z1));
	return true;
}

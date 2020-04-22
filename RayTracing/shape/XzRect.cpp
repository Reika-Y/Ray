#include "XzRect.h"
#include "../AABB.h"

XzRect::XzRect()
{
	_x0 = 0;
	_x1 = 0;
	_z0 = 0;
	_z1 = 0;
	_k = 0;
	_mat = nullptr;
}

XzRect::XzRect(float x0, float x1, float z0, float z1, float k, const std::shared_ptr<Material>& mat)
{
	_x0 = x0;
	_x1 = x1;
	_z0 = z0;
	_z1 = z1;
	_k = k;
	_mat = mat;
}

bool XzRect::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	float t = (_k - ray.Origin().y) / ray.Direction().y;
	if (t < t_min || t > t_max)
	{
		return false;
	}

	float x = ray.Origin().x + t * ray.Direction().x;
	float z = ray.Origin().z + t * ray.Direction().z;
	if (x < _x0 || x > _x1 || z < _z0 || z > _z1)
	{
		return false;
	}

	rec.u = (x - _x0) / (_x1 - _x0);
	rec.v = (z - _z0) / (_z1 - _z0);
	rec.t = t;
	rec.mat = _mat;
	rec.p = ray.PointAtParameter(t);
	rec.normal = Vector3(0, 1, 0);
	return true;
}

bool XzRect::BoundingBox(float t0, float t1, AABB& box) const
{
	box = AABB(Vector3(_x0, _k - 0.0001, _z0), Vector3(_x1, _k + 0.0001, _z1));
	return true;
}

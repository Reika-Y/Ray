#include "XyRect.h"
#include "../AABB.h"

XyRect::XyRect(float x0, float x1, float y0, float y1, float k, const std::shared_ptr<Material>& mat)
{
	_x0 = x0;
	_x1 = x1;
	_y0 = y0;
	_y1 = y1;
	_k = k;
	_mat = mat;
}

bool XyRect::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	float t = (_k - ray.Origin().z) / ray.Direction().z;
	if (t < t_min || t>t_max)
	{
		return false;
	}
	float x = ray.Origin().x + t * ray.Direction().x;
	float y = ray.Origin().y + t * ray.Direction().y;
	if (x<_x0 || x>_x1 || y<_y0 || y>_y1)
	{
		return false;
	}
	rec.u = (x - _x0) / (_x1 - _x0);
	rec.v = (y - _y0) / (_y1 - _y0);
	rec.t = t;
	rec.mat = _mat;
	rec.p = ray.PointAtParameter(t);
	rec.normal = Vector3(0, 0, 1);
	return true;
}

bool XyRect::BoundingBox(float t0, float t1, AABB& box) const
{
	box = AABB(Vector3(_x0, _x1, _k - 0.0001), Vector3(_x1, _y1, _k + 0.0001));
	return true;
}

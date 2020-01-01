#include "MovingSphere.h"
#include "../AABB.h"

MovingSphere::MovingSphere(const Vector3& cen0, const Vector3& cen1, float t0, float t1, float r, const std::shared_ptr<Material>& mat)
{
	_center0 = cen0;
	_center1 = cen1;
	_time0 = t0;
	_time1 = t1;
	_radius = r;
	_mat = mat;
}
const Vector3& MovingSphere::Center(float time) const
{
	return _center0 + (_center1 - _center0)*((time - _time0) / (_time1 - _time0));
}
// 衝突関数
bool MovingSphere::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	Vector3 oc = ray.Origin() - Center(ray.Time());
	float a = Dot(ray.Direction(), ray.Direction());
	float b = Dot(oc, ray.Direction());
	float c = Dot(oc, oc) - _radius * _radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrtf(discriminant)) / a;
		if (t_min < temp && temp < t_max)
		{
			rec.t = temp;
			rec.p = ray.PointAtParameter(rec.t);
			rec.normal = (rec.p - Center(ray.Time())) / _radius;
			rec.mat = _mat;
			return true;
		}
		temp = (-b + sqrtf(discriminant)) / a;
		if (t_min < temp && temp < t_max)
		{
			rec.t = temp;
			rec.p = ray.PointAtParameter(rec.t);
			rec.normal = (rec.p - Center(ray.Time())) / _radius;
			rec.mat = _mat;
			return true;
		}
	}
	return false;
}

bool MovingSphere::BoundingBox(float t0, float t1, AABB& box) const
{
	auto box0 = AABB(_center0 - Vector3(_radius, _radius, _radius), _center0 + Vector3(_radius, _radius, _radius));
	auto box1 = AABB(_center1 - Vector3(_radius, _radius, _radius), _center1 + Vector3(_radius, _radius, _radius));
	box = SurroudingBox(box0, box1);
	return true;
}

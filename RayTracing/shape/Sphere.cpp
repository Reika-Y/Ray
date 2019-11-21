#include "Sphere.h"
#include "../Ray.h"

Sphere::Sphere()
{
	_center = { 0.0f,0.0f,0.0f };
	_radius = 0.0f;
	_mat = nullptr;
}

Sphere::Sphere(const Vector3& c, float r, const std::shared_ptr<Material>& mat)
{
	_center = c;
	_radius = r;
	_mat = mat;
}

Sphere::~Sphere()
{
}

// 衝突関数
bool Sphere::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	auto oc = ray.Origin() - _center;
	auto a = Dot(ray.Direction(), ray.Direction());
	auto b = 2.0f * Dot(oc, ray.Direction());
	auto c = Dot(oc, oc) - Pow2(_radius);
	auto discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		float root = sqrtf(discriminant);
		float tmp = (-b - root) / (2.0f * a);
		if (t_min < tmp && tmp < t_max)
		{
			rec.t = tmp;
			rec.p = ray.PointAtParameter(rec.t);
			rec.normal = (rec.p - _center) / _radius;
			rec.mat = _mat;
			return true;
		}
		tmp = (-b + root) / (2.0f * a);
		if (t_min < tmp && tmp < t_max)
		{
			rec.t = tmp;
			rec.p = ray.PointAtParameter(rec.t);
			rec.normal = (rec.p - _center) / _radius;
			rec.mat = _mat;
			return true;
		}
	}
	return false;
}

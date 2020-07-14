#include "Metal.h"
#include "../shape/HitRecord.h"

Metal::Metal(const Vector3& v, float f)
{
	_albedo = v;
	if (f < 1)
	{
		_fuzz = f;
	}
	else
	{
		_fuzz = 1.0f;
	}
}

// 散乱のシュミレーション
bool Metal::Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec) const
{
	auto ray_vec = ray.Direction();
	Vector3 reflected = Reflect(ray_vec.Normalized(), rec.normal);
	// 反射ベクトルの先を中心とした単位球内の点を無作為に選んでそこまでのベクトルを反射ベクトルとする
	reflected += RandomInUnitSphere() * _fuzz;
	srec.ray = Ray(rec.p, reflected);
	srec.albedo = _albedo;
	return Dot(srec.ray.Direction(), rec.normal) > 0;
}

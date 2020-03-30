#include "Lambertian.h"
#include "../shape/HitRecord.h"

Lambertian::Lambertian(const std::shared_ptr<Texture>& c)
{
	_albedo = c;
}

bool Lambertian::Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec) const
{
	Vector3 target = rec.p + rec.normal + RandomInUnitSphere();
	srec.ray = Ray(rec.p, target - rec.p, ray.Time());
	srec.albedo = _albedo->Value(rec.u, rec.v, rec.p);
	return true;
}

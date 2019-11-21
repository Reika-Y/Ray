#include "Lambertian.h"
#include "../shape/HitRecord.h"

Lambertian::Lambertian(const Vector3& c)
{
	_albedo = c;
}

bool Lambertian::Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec) const
{
	Vector3 target = rec.p + rec.normal + RandomInUnitSphere();
	srec.ray = Ray(rec.p, target - rec.p);
	srec.albedo = _albedo;
	return true;
}

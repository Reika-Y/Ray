#include "Isotropic.h"
#include "../shape/HitRecord.h"

Isotropic::Isotropic(Texture* a)
{
	_albedo = a;
}

bool Isotropic::Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec) const
{
	srec.ray = Ray(rec.p, RandomInUnitSphere(),ray.Time());
	srec.albedo = (*_albedo).Value(rec.u, rec.v, rec.p);
	return true;
}

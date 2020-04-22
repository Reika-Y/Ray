#include "DiffuseLight.h"

bool DiffuseLight::Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec) const
{
	return false;
}

Vector3 DiffuseLight::Emitted(float u, float v, const Vector3& p) const
{
	return emit->Value(u, v, p);
}

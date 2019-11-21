#include "Dielectric.h"
#include "../shape/HitRecord.h"

Dielectric::Dielectric(float ri)
{
	_ri = ri;
}

bool Dielectric::Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec) const
{
	Vector3 outoutward_normal = { 0.0f,0.0f,0.0f };
	Vector3 reflected = Reflect(ray.Direction(), rec.normal);
	float ni_over_nt = 0.0f;
	float cos = 0.0f;
	if (Dot(ray.Direction(), rec.normal) > 0)
	{
		outoutward_normal = rec.normal * -1;
		ni_over_nt = _ri;
		cos = _ri * Dot(ray.Direction(), rec.normal) / ray.Direction().Length();
	}
	else
	{
		outoutward_normal = rec.normal;
		ni_over_nt = Recip(_ri);
		cos = -Dot(ray.Direction(), rec.normal) / ray.Direction().Length();
	}
	srec.albedo = { 1.0f,1.0f,1.0f };

	Vector3 refracted = { 0.0f,0.0f,0.0f };
	float reflect_prob = 0.0f;
	if (Refract(ray.Direction() * -1, outoutward_normal, ni_over_nt, refracted))
	{
		reflect_prob = Schlick(cos, _ri);
	}
	else
	{
		srec.ray = Ray(rec.p, reflected);
		reflect_prob = 1.0f;
	}

	if (DRand() < reflect_prob)
	{
		srec.ray = Ray(rec.p, reflected);
	}
	else
	{
		srec.ray = Ray(rec.p, refracted);
	}
	return true;
}

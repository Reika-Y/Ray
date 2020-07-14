#include "DiffuseLight.h"

// 散乱のシュミレーション
bool DiffuseLight::Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec) const
{
	return false;
}

// 発光色を返す
Vector3 DiffuseLight::Emitted(float u, float v, const Vector3& p) const
{
	return emit->Value(u, v, p);
}

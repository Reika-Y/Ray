#pragma once
#include "Material.h"

// 拡散反射
class Lambertian :
	public Material
{
public:
	Lambertian(const Vector3& c);
	// 散乱のシュミレーション
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const override;
private:
	Vector3 _albedo;
};


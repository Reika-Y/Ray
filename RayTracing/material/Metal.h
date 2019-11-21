#pragma once
#include "Material.h"

class Metal :
	public Material
{
public:
	Metal(const Vector3& v,float f);
	// 散乱のシュミレーション
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const override;
private:
	Vector3 _albedo;
	float _fuzz;
};


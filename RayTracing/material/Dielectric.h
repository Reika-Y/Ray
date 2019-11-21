#pragma once
#include "Material.h"

// 誘導体
class Dielectric :
	public Material
{
public:
	Dielectric(float ri);
	// 散乱のシュミレーション
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const override;
private:
	float _ri;		// 屈折率
};


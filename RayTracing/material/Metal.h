#pragma once
#include "Material.h"

// 金属
class Metal :
	public Material
{
public:
	Metal(const Vector3& v,float f);
	// 散乱のシュミレーション
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const override;
private:
	// 色
	Vector3 _albedo;
	// ずらし
	float _fuzz;
};


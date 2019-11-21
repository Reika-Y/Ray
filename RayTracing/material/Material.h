#pragma once
#include "../common/Geometry.h"
#include "../Ray.h"

struct HitRecord;

// 散乱後の情報
struct ScatterRec
{
	Ray ray;		// 光の向き
	Vector3 albedo;	// 反射率
};

// 材質
class Material
{
public:
	// 散乱のシュミレーション
	virtual bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const = 0;
};


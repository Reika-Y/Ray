#pragma once
#include "Material.h"
#include <memory>
#include "../Texture.h"

// 拡散反射
class Lambertian :
	public Material
{
public:
	Lambertian(const std::shared_ptr<Texture>& c);
	// 散乱のシュミレーション
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const override;
private:
	std::shared_ptr<Texture>_albedo;
};


#pragma once 
#include "Material.h"
#include "../texture/Texture.h"

// 等方性の散乱
class Isotropic :
	public Material
{
public:
	Isotropic(Texture* a);
	// 散乱のシュミレーション
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const;
private:
	Texture *_albedo;
};
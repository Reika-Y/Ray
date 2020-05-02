#pragma once 
#include "Material.h"
#include "../Texture.h"

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
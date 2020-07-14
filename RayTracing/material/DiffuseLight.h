#pragma once
#include "Material.h"
#include "../texture/Texture.h"

// 拡散光
class DiffuseLight :public Material
{
public:
	DiffuseLight(Texture* t) :emit(t) {}
	// 散乱のシュミレーション
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const override;
	// 発光色を返す
	Vector3 Emitted(float u, float v, const Vector3& p)const override;
private:
	Texture* emit;
};
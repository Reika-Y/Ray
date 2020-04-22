#pragma once
#include "Material.h"
#include "../Texture.h"

class DiffuseLight :public Material
{
public:
	DiffuseLight(Texture* t) :emit(t) {}
	bool Scatter(const Ray& ray, const HitRecord& rec, ScatterRec& srec)const override;
	Vector3 Emitted(float u, float v, const Vector3& p)const override;
private:
	Texture* emit;
};
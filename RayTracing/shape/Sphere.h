#pragma once
#include "HitRecord.h"
#include "../material/Material.h"

// 球クラス
class Sphere :
	public Shape
{
public:
	Sphere();
	// <param = c> 中心座標
	// <param = r> 半径
	Sphere(const Vector3& c, float r, std::shared_ptr<Material> mat);
	~Sphere();
	// 衝突関数
	// <param = ray> 光線
	// <param = t_min> 光線の衝突範囲の始点
	// <param = t_max> 光線の衝突範囲の終点
	// <param = rec> 衝突情報
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	Vector3 _center;		// 中心座標
	float _radius;			// 半径
	std::shared_ptr<Material> _mat;
};


#pragma once
#include "HitRecord.h"

class MovingSphere :
	public Shape
{
public:
	MovingSphere(const Vector3& cen0, const Vector3& cen1,float t0,float t1,float r, const std::shared_ptr<Material>& mat);
	const Vector3& Center(float time)const;
	// 衝突関数
	// <param = ray> 光線
	// <param = t_min> 光線の衝突範囲の始点
	// <param = t_max> 光線の衝突範囲の終点
	// <param = rec> 衝突情報
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const override;
	bool BoundingBox(float t0, float t1, AABB& box)const override;
private:
	Vector3 _center0;
	Vector3 _center1;
	float _time0;
	float _time1;
	float _radius;
	std::shared_ptr<Material> _mat;
};


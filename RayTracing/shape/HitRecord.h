#pragma once
#include <memory>
#include "../common/Geometry.h"
#include "../material/Material.h"

class Ray;
class AABB;

// 衝突時の情報格納用
struct HitRecord
{
	float t;		// 光線
	Vector3 p;		// 衝突位置
	Vector3 normal;	// 衝突位置の法線
	std::shared_ptr<Material> mat;		// 材質
};

// 物体の抽象クラス
class Shape
{
public:
	// 衝突関数
	// <param = ray> 光線
	// <param = t_min> 光線の衝突範囲の始点
	// <param = t_max> 光線の衝突範囲の終点
	// <param = rec> 衝突情報
	virtual bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const = 0;
	virtual bool BoundingBox(float t0, float t1, AABB& box)const = 0;
};
#pragma once
#include <memory>
#include <vector>
#include "HitRecord.h"

using ShapePtr = std::shared_ptr<Shape>;

class ShapeList :
	public Shape
{
public:
	ShapeList();
	~ShapeList();
	// 衝突関数
	// <param = ray> 光線
	// <param = t_min> 光線の衝突範囲の始点
	// <param = t_max> 光線の衝突範囲の終点
	// <param = rec> 衝突情報
	bool Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const override;
	// 物体追加
	void Add(const ShapePtr& shape);
	const size_t Count(void);
	bool BoundingBox(float t0, float t1, AABB& box)const override;
	std::vector<ShapePtr> Vector(void);
private:
	std::vector<ShapePtr>_shapes;
};


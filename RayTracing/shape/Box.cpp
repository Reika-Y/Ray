#include "Box.h"
#include "ShapeList.h"
#include "../AABB.h"
#include "FlipNormals.h"
#include "XyRect.h"
#include "XzRect.h"
#include "YzRect.h"

Box::Box()
{
	_pmin = Vector3(0, 0, 0);
	_pmax = Vector3(0, 0, 0);
	list = nullptr;
}

Box::Box(const Vector3& p0, const Vector3& p1, const std::shared_ptr<Material>& mat)
{
	_pmin = p0;
	_pmax = p1;
	list = new ShapeList();
	(*list).Add(std::make_shared<XyRect>(p0.x, p1.x, p0.y, p1.y, p1.z, mat));
	(*list).Add(std::make_shared<FlipNormals>(new XyRect(p0.x, p1.x, p0.y, p1.y, p0.z, mat)));
	(*list).Add(std::make_shared<XzRect>(p0.x, p1.x, p0.z, p1.z, p1.y, mat));
	(*list).Add(std::make_shared<FlipNormals>(new XzRect(p0.x, p1.x, p0.z, p1.z, p0.y, mat)));
	(*list).Add(std::make_shared<YzRect>(p0.y, p1.y, p0.z, p1.z, p1.x, mat));
	(*list).Add(std::make_shared<FlipNormals>(new YzRect(p0.y, p1.y, p0.z, p1.z, p0.x, mat)));
}

bool Box::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	return (*list).Hit(ray, t_min, t_max, rec);
}

bool Box::BoundingBox(float t0, float t1, AABB& box) const
{
	box = AABB(_pmin, _pmax);
	return true;
}

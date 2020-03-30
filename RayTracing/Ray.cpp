#include "Ray.h"
#define _USE_MATH_DEFINES
#include <math.h>

Ray::Ray()
{
	_origin = { 0,0,0 };
	_direction = { 0,0,0 };
}

Ray::Ray(const Vector3& o, const Vector3& dir, float ti)
{
	_origin = o;
	_direction = dir;
	_time = ti;
}

Ray::~Ray()
{
}

const Vector3& Ray::Origin() const
{
	return _origin;
}

const Vector3& Ray::Direction() const
{
	return _direction;
}

Vector3 Ray::PointAtParameter(float t) const
{
	return _origin + _direction * t;
}

// 残存時間を返す
const float Ray::Time(void) const
{
	return _time;
}

// 球状マッピングしたテクスチャ座標を取得する
void GetSphereUv(const Vector3& p, float& u, float& v)
{
	float phi = atan2(p.z, p.x);
	float theta = asin(p.y);
	u = 1 - (phi + M_PI) / (2.f * M_PI);
	v = (theta + M_PI / 2.f) / M_PI;
}

#include "Ray.h"

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

const float Ray::Time(void) const
{
	return _time;
}

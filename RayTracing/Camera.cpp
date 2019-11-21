#include <math.h>
#include "Camera.h"

Camera::Camera()
{
	_position = { 0,0,0 };
	for (auto uvw : _uvw)
	{
		uvw = { 0,0,0 };
	}
}

Camera::Camera(const Vector3& u, const Vector3& v, const Vector3& w)
{
	_position = { 0,0,0 };
	_uvw[0] = u;
	_uvw[1] = v;
	_uvw[2] = w;
}

Camera::Camera(const Vector3& lookfrom, const Vector3& lookat, const Vector3& vup, float vfov, float aspect)
{
	Vector3 u, v, w = { 0,0,0 };
	float harf_h = tanf(Radians(vfov) / 2.0f);
	float harf_w = aspect * harf_h;
	_position = lookfrom;
	w = (lookfrom - lookat).Normalized();
	u = Cross(vup, w).Normalized();
	v = Cross(w, u);
	_uvw[0] = u * 2.0f * harf_w;
	_uvw[1] = v * 2.0f * harf_h;
	_uvw[2] = _position - (u * harf_w) - (v * harf_h) - w;
}

Ray Camera::GetRay(float u, float v) const
{
	return Ray(_position, _uvw[2] + _uvw[0] * u + _uvw[1] * v - _position);;
}

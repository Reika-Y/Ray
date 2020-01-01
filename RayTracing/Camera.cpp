#include <math.h>
#include "Camera.h"

Camera::Camera(const Vector3& lookfrom, const Vector3& lookat, const Vector3& vup, float vfov, float aspect, float aperture, float t0, float t1)
{
	Vector3 _u, _v, _w = { 0,0,0 };
	float harf_h = tanf(Radians(vfov) / 2.0f);
	float harf_w = aspect * harf_h;
	_position = lookfrom;
	_w = (lookfrom - lookat).Normalized();
	_u = Cross(vup, _w).Normalized();
	_v = Cross(_w, _u);
	_uvw[0] = _u * 2.0f * harf_w;
	_uvw[1] = _v * 2.0f * harf_h;
	_uvw[2] = _position - (_u * harf_w) - (_v * harf_h) - _w;
	_t0 = t0;
	_t1 = t1;
	lensRadius = aperture / 2;
}

Ray Camera::GetRay(float u, float v) const
{
	Vector3 rd = RandomVector() * lensRadius;
	Vector3 offset = _u * rd.x + _v * rd.y;
	float time = _t0 + DRand() + (_t1 - _t0);
	return Ray(_position + offset, _uvw[2] + _uvw[0] * u + _uvw[1] * v - _position - offset, time);
}

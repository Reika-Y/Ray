#pragma once
#include "common/Geometry.h"
#include "Ray.h"

class Camera
{
public:
	Camera(const Vector3& lookfrom, const Vector3& lookat, const Vector3& vup, float vfov, float aspect, float aperture, float focus_dist, float t0, float t1);
	Ray GetRay(float u, float v)const;
private:
	Vector3 _position;		// 位置
	Vector3 _lowerLeftCorner;
	Vector3 _horizontal;
	Vector3 _vertical;
	Vector3 _u, _v, _w;
	float _t0, _t1;
	float lensRadius;
};


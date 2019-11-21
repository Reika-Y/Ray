#pragma once
#include "common/Geometry.h"
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(const Vector3& u, const Vector3& v, const Vector3& w);
	Camera(const Vector3& lookfrom, const Vector3& lookat, const Vector3& vup, float vfov, float aspect);
	Ray GetRay(float u, float v)const;
private:
	Vector3 _position;		// 位置
	Vector3 _uvw[3];		// 直交基底ベクトル
};


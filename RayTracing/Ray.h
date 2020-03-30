#pragma once
#include "common/Geometry.h"

class Ray
{
public:
	Ray();
	Ray(const Vector3& o, const Vector3& dir, float ti = 0.0f);
	~Ray();
	// 始点を返す
	const Vector3& Origin()const;
	// 方向を返す
	const Vector3& Direction()const;
	Vector3 PointAtParameter(float t)const;
	// 残存時間を返す
	const float Time(void)const;
private:
	Vector3 _origin;		// 始点
	Vector3 _direction;		// 方向(非正規)
	float _time;			// 残存時間
};

// 球状マッピングしたテクスチャ座標を取得する
void GetSphereUv(const Vector3& p, float& u, float& v);

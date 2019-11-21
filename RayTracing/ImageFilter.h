#pragma once
#include "common/Geometry.h"

// フィルターの抽象クラス
class ImageFilter
{
public:
	virtual Vector3 Filter(const Vector3& c)const = 0;
};

// ガンマ補正をかけるフィルタークラス
class GammaFilter :public ImageFilter
{
public:
	GammaFilter(float factor);
	Vector3 Filter(const Vector3& c)const;
private:
	float _factor;
};
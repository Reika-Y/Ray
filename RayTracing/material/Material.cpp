#include "Material.h"

// 発光色を返す
Vector3 Material::Emitted(float u, float v, const Vector3& p) const
{
	// 基本はなし（黒）
	return Vector3(0, 0, 0);
}

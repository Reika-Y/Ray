#include "Vector3.h"
#include <cmath>

// オペレーターオーバーロード
void Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

Vector3 Vector3::operator*(float scale)const {
	return Vector3(x * scale, y * scale, z * scale);
}

Vector3 operator+(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x + vb.x, va.y + vb.y, va.z + vb.z);
}

Vector3 operator-(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x - vb.x, va.y - vb.y, va.z - vb.z);
}

// 添え字演算子
float Vector3::operator[](int k)
{
	if (k == 0)
	{
		return x;
	}
	if (k == 1)
	{
		return y;
	}
	if (k == 2)
	{
		return z;
	}
}

// ベクトルの大きさを返します
float Vector3::Length()const {
	return sqrt(x * x + y * y + z * z);
}

// ベクトルの長さの2乗を返します
float Vector3::LengthSqr() const
{
	return (x * x + y * y + z * z);
}

// 正規化します
void Vector3::Normalize() {
	float mag = Length();
	x /= mag;
	y /= mag;
	z /= mag;
}

// 正規化ベクトルを返します
Vector3 Vector3::Normalized() {
	float mag = Length();
	return Vector3(x / mag, y / mag, z / mag);
}


// 内積を返す
float Dot(const Vector3& va, const Vector3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

// 外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z * vb.y - va.y * vb.z, va.z * vb.x - va.x * vb.z, va.x * vb.y - vb.x * va.y);
}

// 乗算演算子
Vector3 operator*(const Vector3& va, const Vector3& vb) {
	return Vector3{ va.x * vb.x, va.y * vb.y, va.z * vb.z };
}

// 除算演算子 
Vector3 operator/(const Vector3& va, float t)
{
	return Vector3(va.x / t, va.y / t, va.z / t);
}

// 直線上にある２つのベクトル間を補間する関数
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	auto distance = v2 - v1;
	auto mag = distance.Length() * t;
	return v1 + distance * mag;
}

// 加算
void Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
// 減算
void Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
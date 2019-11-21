#include "Vector3.h"
#include <cmath>

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

float
Vector3::Length()const {
	return sqrt(x * x + y * y + z * z);
}

float Vector3::LengthSqr() const
{
	return (x * x + y * y + z * z);
}


void Vector3::Normalize() {
	float mag = Length();
	x /= mag;
	y /= mag;
	z /= mag;
}


Vector3 Vector3::Normalized() {
	float mag = Length();
	return Vector3(x / mag, y / mag, z / mag);
}


///内積を返す
float Dot(const Vector3& va, const Vector3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

///外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z * vb.y - va.y * vb.z, va.z * vb.x - va.x * vb.z, va.x * vb.y - vb.x * va.y);
}

Vector3 operator*(const Vector3& va, const Vector3& vb) {
	return Vector3{ va.x * vb.x, va.y * vb.y, va.z * vb.z };
}

Vector3 operator/(const Vector3& va, float t)
{
	return Vector3(va.x / t, va.y / t, va.z / t);
}


Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	auto distance = v2 - v1;
	auto mag = distance.Length() * t;
	return v1 + distance * mag;
}


void Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
void Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
#pragma once

//3D座標・ベクトルを表す構造体
struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float inx, float iny, float inz) :x(inx), y(iny), z(inz) {}
	float x, y, z;

	float operator[](int k);

	///ベクトルの大きさを返します
	float Length()const;

	// ベクトルの長さの2乗を返します
	float LengthSqr() const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
	Vector3 Normalized();

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	Vector3 operator-() {
		return Vector3(-x, -y, -z);
	}
};
Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

///内積を返す
float Dot(const Vector3& va, const Vector3& vb);

///外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb);

///乗算演算子
Vector3 operator*(const Vector3& va, const Vector3& vb);

Vector3 operator/(const Vector3& va, float t);

// 直線上にある２つのベクトル間を補間する関数
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

typedef Vector3 Position3;


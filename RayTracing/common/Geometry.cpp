#include "Geometry.h"
#include <cmath>

// 乱数の最大値
const float rand_max = 32767;

// 0,1の一様乱数を返す
float DRand()
{
	return static_cast<float>(static_cast<double>(rand()) / rand_max);
}

// xの2乗を返す
float Pow2(float x)
{
	return x * x;
}

// xの3乗を返す
float Pow3(float x)
{
	return x * x * x;
}

// xの4乗を返す
float Pow4(float x)
{
	return x * x * x * x;
}

// xの5乗を返す
float Pow5(float x)
{
	return x * x * x * x * x;
}

// a < x < bを満たすxを返す
float Clamp(float x, float a, float b)
{
	if (a < x)
	{
		if (b > x)
		{
			return x;
		}
		return b;
	}
	return a;
}

// 0 < x < 1を満たすxを返す
float Saturate(float x)
{
	return Clamp(x, 0.0f, 1.0f);
}

// 1/xを返す
float Recip(float x)
{
	return 1.0f / x;
}

// aとbをパラメータで線形補間した値を返す
float Mix(float a, float b, float t)
{
	return a * (1.0f - t) + b * t;
}

// edge以下なら0、それ以外は1を返す
float Step(float edge, float x)
{
	if (x <= edge)
	{
		return 0.0f;
	}
	return 1.0f;
}

// aとbをパラメータtでスプライン補間した値を返す
float SmoothStep(float a, float b, float t)
{
	if (a >= b)
	{
		return 0.0f;
	}
	float x = Saturate((t - a) / (b - a));
	return x * x * (3.0f - 2.0f * t);
}

// ラジアン変換
float Radians(float deg)
{
	return deg * PI / 180.0f;
}

// 度数変換
float Degrees(float rad)
{
	return rad * 180.0f / PI;
}

float Schlick(float cos, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = Pow2(r0);
	return r0 + (1 - r0) * Pow5((1 - cos));
}

// 0～1を満たすベクトルを返す
Vector3 Clamp(Vector3 x, Vector3 a, Vector3 b)
{
	return Vector3(Clamp(x.x, a.x, b.x), Clamp(x.y, a.y, b.y), Clamp(x.z, a.z, b.z));
}

// 一様乱数を使ってベクトルを作成
Vector3 RandomVector(void)
{
	return Vector3(DRand(), DRand(), DRand());
}

// 単位球の中の任意の点を生成
Vector3 RandomInUnitSphere(void)
{
	Vector3 p = { 0.0f,0.0f,0.0f };
	do
	{
		p = RandomVector() * 2.0f - Vector3(1.0f, 1.0f, 1.0f);

	} while (Dot(p,p) >= 1.0f);
	return p;
}

// 反射ベクトルを返す
Vector3 Reflect(const Vector3& v, const Vector3& n)
{
	return v - n * 2.0f * Dot(v, n);
}

// 屈折ベクトル返す(スネルの法則)
bool Refract(const Vector3& v, const Vector3& n, float ni_over_nt, Vector3& refracted)
{
	Vector3 uv = v;
	uv.Normalize();
	float dt = Dot(uv, n);
	float D = 1.0f - Pow2(ni_over_nt) * (1.0f - Pow2(dt));
	if (D > 0.0f)
	{
		refracted = (uv - n * dt) * (-ni_over_nt) - n * sqrtf(D);
		return true;
	}
	return false;
}

// リニア空間からsRGB空間に変換
Vector3 LinearToGamma(const Vector3& v, float gammaFactor)
{
	float recipGammaFactor = Recip(gammaFactor);
	return Vector3(powf(v.x, recipGammaFactor), powf(v.y, recipGammaFactor), powf(v.z, recipGammaFactor));
}

// sRGB空間からリニア空間に変換
Vector3 GammaToLinear(const Vector3& v, float gammaFactor)
{
	return Vector3(powf(v.x, gammaFactor), powf(v.y, gammaFactor), powf(v.z, gammaFactor));
}

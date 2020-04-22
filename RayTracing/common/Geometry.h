#pragma once
#include "Size.h"
#include "Vector3.h"
// ユーティリティ関数を定義

// 数学の定義
#define PI 3.14159265359f
#define PI2 6.28318530718f
#define RECIP_PI 0.31830988618f
#define RECIP_PI2 0.15915494f
#define LOG2 1.442695f
#define EPSILON 1e-6f
#define GAMMA_FACTOR 2.2f

// 0,1の一様乱数を返す
float DRand();

// xの2乗を返す
float Pow2(float x);

// xの3乗を返す
float Pow3(float x);

// xの4乗を返す
float Pow4(float x);

// xの5乗を返す
float Pow5(float x);

// a < x < bを満たすxを返す
float Clamp(float x, float a, float b);

// 0 < x < 1を満たすxを返す
float Saturate(float x);

// 1/xを返す
float Recip(float x);

// aとbをパラメータで線形補間した値を返す
float Mix(float a, float b, float t);

// edge以下なら0、それ以外は1を返す
float Step(float edge, float x);

// aとbをパラメータtでスプライン補間した値を返す
float SmoothStep(float a, float b, float t);

// ラジアン変換
float Radians(float deg);

// 度数変換
float Degrees(float rad);

float Schlick(float cos, float ref_idx);

Vector3 Clamp(Vector3 x, Vector3 a = Vector3(0, 0, 0), Vector3 b = Vector3(1, 1, 1));

Vector3 RandomVector(void);

Vector3 RandomInUnitSphere(void);

// 反射ベクトルを返す
Vector3 Reflect(const Vector3& v, const Vector3& n);

// 屈折ベクトル返す(スネルの法則)
bool Refract(const Vector3& v, const Vector3& n, float ni_over_nt, Vector3& refracted);

// リニア空間からsRGB空間に変換
Vector3 LinearToGamma(const Vector3& v, float gammaFactor);

// sRGB空間からリニア空間に変換
Vector3 GammaToLinear(const Vector3& v, float gammaFactor);
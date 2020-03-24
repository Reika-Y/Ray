#include <iostream>
#include "Scene.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include "Image.h"
#include "Camera.h"
#include "shape/ShapeList.h"
#include "shape/Sphere.h"
#include "shape/MovingSphere.h"
#include "material/Material.h"
#include "material/Lambertian.h"
#include "material/Metal.h"
#include "material/Dielectric.h"
#include "NoiseTexture.h"

// 再帰呼び出しの最大
const int max_depth = 50;

Scene::Scene(int w, int h, int samples)
{
	_image = std::make_unique<Image>(w, h);
	_backColor = { 0.2f,0.2f,0.2f };
	_samples = samples;
}

Scene::~Scene()
{
}

void Scene::Render(void)
{
	Init();

	auto size = (*_image).ImageSize();

#ifdef _OPENMP
#pragma omp parallel for
#endif
	for (int j = 0; j < size.height; j++)
	{
		for (int i = 0; i < size.width; i++)
		{
			Vector3 c = { 0.0f,0.0f,0.0f };
			for (int s = 0; s < _samples; s++)
			{
				float u = static_cast<float>(i + DRand()) / static_cast<float>(size.width);
				float v = static_cast<float>(j + DRand()) / static_cast<float>(size.height);
				Ray ray = (*_camera).GetRay(u, v);
				c += GetColor(ray, _shape.get(),0);
			}

			c = c / static_cast<float>(_samples);
			(*_image).Write(i, (size.height - j - 1), c.x, c.y, c.z);
		}
	}

	stbi_write_bmp("image/smooth.bmp", size.width, size.height, sizeof(Color), (*_image).Pixcels());
}

// レンダリングするときに一度だけ呼ばれる関数
void Scene::Init(void)
{
	// Camera
	Vector3 lookfrom(13.0f, 2.0f, 3.0f);
	Vector3 lookat(0.0f, 0.0f, 0.0f);
	Vector3 vup(0.0f, 1.0f, 0.0f);
	auto size = (*_image).ImageSize();
	float aspect = static_cast<float>(size.width) / static_cast<float>(size.height);
	_camera = std::make_unique<Camera>(lookfrom, lookat, vup, 20, aspect, 0.f, 10.0f, 1.0f);

	// Shape
	ShapeList* list = new ShapeList();
	auto checker = std::make_shared<NoiseTexture>(3.0f);
	(*list).Add(std::make_shared<Sphere>(Vector3(0.f, -1000.f, 0.f),1000.f, std::make_shared<Lambertian>(checker)));
	(*list).Add(std::make_shared<Sphere>(Vector3(0.f, 2.f, 0.f),2.f, std::make_shared<Lambertian>(checker)));
	_shape.reset(list);
}

// 色の取得
Vector3 Scene::GetColor(const Ray& ray, const Shape* shape,int depth)
{
	HitRecord rec;
	// 誤差による反射方向のずれを防ぐ
	if ((*shape).Hit(ray, 0.001f, FLT_MAX, rec))
	{
		ScatterRec srec;
		if (depth < max_depth && (*rec.mat).Scatter(ray, rec, srec))
		{
			return srec.albedo * GetColor(srec.ray, shape, ++depth);
		}
		return Vector3{ 0.0f,0.0f,0.0f };
	}
	return BackGroundSky(ray.Direction());
}

// 背景色の取得
Vector3 Scene::BackGroundSky(const Vector3& dir)
{
	auto v = dir;
	v.Normalize();
	auto t = 0.5f * (dir.y + 1.0f);
	return Lerp(Vector3(0.5f, 0.7f, 1.0f), Vector3(1, 1, 1), t);
}


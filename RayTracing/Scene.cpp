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
#include "shape/XyRect.h"
#include "shape/XzRect.h"
#include "shape/YzRect.h"
#include "shape/Box.h"
#include "shape/FlipNormals.h"
#include "shape/Translate.h"
#include "shape/RotateY.h"
#include "shape/ConstantMedium.h"
#include "material/Material.h"
#include "material/Lambertian.h"
#include "material/Metal.h"
#include "material/Dielectric.h"
#include "material/DiffuseLight.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "ConstantTexture.h"

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
			c = Clamp(c);
			(*_image).Write(i, (size.height - j - 1), c.x, c.y, c.z);
		}
	}

	stbi_write_bmp("image/volume.bmp", size.width, size.height, sizeof(Color), (*_image).Pixcels());
}

// レンダリングするときに一度だけ呼ばれる関数
void Scene::Init(void)
{
	// Camera
	Vector3 lookfrom(278, 278, -800);
	Vector3 lookat(278, 278, 0.0f);
	Vector3 vup(0.0f, 1.0f, 0.0f);
	auto size = (*_image).ImageSize();
	float aspect = static_cast<float>(size.width) / static_cast<float>(size.height);
	_camera = std::make_unique<Camera>(lookfrom, lookat, vup, 40, aspect, 0.f, 10.0f, 0.0f, 1.0f);

	// Shapes
	ShapeList* list = new ShapeList();
	Mat red = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.65, 0.05, 0.05)));
	Mat white = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.73, 0.73, 0.73)));
	Mat green = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.12, 0.45, 0.15)));
	Mat light = std::make_shared<DiffuseLight>(new ConstantTexture(Vector3(7, 7, 7)));
	(*list).Add(std::make_shared<XzRect>(113, 443, 127, 432, 554, light));
	(*list).Add(std::make_shared<FlipNormals>(new YzRect(0, 555, 0, 555, 555, green)));
	(*list).Add(std::make_shared<YzRect>(0, 555, 0, 555, 0, red));
	(*list).Add(std::make_shared<FlipNormals>(new XzRect(0, 555, 0, 555, 555, white)));
	(*list).Add(std::make_shared<XzRect>(0, 555, 0, 555, 0, white));
	(*list).Add(std::make_shared<FlipNormals>(new XyRect(0, 555, 0, 555, 555, white)));
	ShapePtr b1 = std::make_shared<Translate>(std::make_shared<RotateY>(std::make_shared<Box>(Vector3(0, 0, 0), Vector3(165, 165, 165), white), -18), Vector3(130, 0, 65));
	ShapePtr b2 = std::make_shared<Translate>(std::make_shared<RotateY>(std::make_shared<Box>(Vector3(0, 0, 0), Vector3(165, 330, 165), white), 15), Vector3(265, 0, 295));
	(*list).Add(std::make_shared<ConstantMedium>(b2, 0.01, new ConstantTexture(Vector3(1.0, 1.0, 1.0))));
	(*list).Add(std::make_shared<ConstantMedium>(b1, 0.01, new ConstantTexture(Vector3(0.f, 0.f, 0.f))));
	_shape.reset(list);
}

// 色の取得
Vector3 Scene::GetColor(const Ray& ray, const Shape* shape,int depth)
{
	HitRecord rec;
	// 誤差による反射方向のずれを防ぐ
	if ((*shape).Hit(ray, 0.001f, FLT_MAX, rec))
	{
		Vector3 emitted = rec.mat->Emitted(rec.u, rec.v, rec.p);
		ScatterRec srec;
		if (depth < max_depth && (*rec.mat).Scatter(ray, rec, srec))
		{
			return emitted + srec.albedo * GetColor(srec.ray, shape, ++depth);
		}
		return emitted;
	}
	return Vector3(0, 0, 0);
}

// 背景色の取得
Vector3 Scene::BackGroundSky(const Vector3& dir)
{
	auto v = dir;
	v.Normalize();
	auto t = 0.5f * (dir.y + 1.0f);
	return Lerp(Vector3(0.5f, 0.7f, 1.0f), Vector3(1, 1, 1), t);
}

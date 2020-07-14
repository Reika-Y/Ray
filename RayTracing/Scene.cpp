#include "Scene.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include "Image.h"
#include "Camera.h"
#include "shape/Shapes.h"
#include "material/Material.h"
#include "material/Materials.h"
#include "texture/Textures.h"


// 再帰呼び出しの最大
const int max_depth = 7;

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

	stbi_write_bmp("image/next_week_end.bmp", size.width, size.height, sizeof(Color), (*_image).Pixcels());
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

	int nb = 20;
	auto boxList = new Shape * [nb * nb];
	auto ground = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.48, 0.83, 0.53)));
	for (int i = 0; i < nb; i++)
	{
		for (int j = 0; j < nb; j++)
		{
			float w = 100;
			float x0 = -1000 + i * w;
			float y0 = 0;
			float z0 = -1000 + j * w;
			float x1 = x0 + w;
			float y1 = 100 * (DRand() + 0.01);
			float z1 = z0 + w;
			boxList[nb * i + j] = new Box(Vector3(x0, y0, z0), Vector3(x1, y1, z1), ground);
		}
	}
	(*list).Add(std::make_shared<BvhNode>(boxList, nb * nb, 0, 1));

	Mat light = std::make_shared<DiffuseLight>(new ConstantTexture(Vector3(7, 7, 7)));
	(*list).Add(std::make_shared<XzRect>(123, 423, 147, 412, 554, light));
	
	Vector3 center{ 400,400,200 };
	Mat orange = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.7, 0.3, 0.1)));
	(*list).Add(std::make_shared<MovingSphere>(center, center + Vector3(30, 0, 0), 0, 1, 50, orange));

	(*list).Add(std::make_shared<Sphere>(Vector3(260, 150, 45), 50, std::make_shared<Dielectric>(1.5)));

	(*list).Add(std::make_shared<Sphere>(Vector3(0, 150, 145), 50, std::make_shared<Metal>(Vector3(0.8, 0.8, 0.9), 10.f)));

	auto boundary = std::make_shared<Sphere>(Vector3(360, 150, 145), 70, std::make_shared<Dielectric>(1.5f));
	(*list).Add(boundary);
	(*list).Add(std::make_shared<ConstantMedium>(boundary, 0.2f, new ConstantTexture(Vector3(0.2, 0.4, 0.9))));
	boundary = std::make_shared<Sphere>(Vector3(0, 0, 0), 5000, std::make_shared<Dielectric>(1.5));
	(*list).Add(std::make_shared<ConstantMedium>(boundary, 0.0001, new ConstantTexture(Vector3(1.f, 1.f, 1.f))));

	int nx, ny, nn;
	auto tex_data = stbi_load("asset/earth.jpg", &nx, &ny, &nn, 0);
	Mat earth = std::make_shared<Lambertian>(std::make_shared<ImageTexture>(tex_data, nx, ny));
	(*list).Add(std::make_shared<Sphere>(Vector3(400, 200, 400), 100, earth));

	auto pertext = std::make_shared<NoiseTexture>(0.1);
	(*list).Add(std::make_shared<Sphere>(Vector3(220, 280, 300), 80, std::make_shared<Lambertian>(pertext)));

	int ns = 1000;
	auto boxList2 = new Shape * [ns];
	Mat white = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.73f, 0.73f, 0.73f)));
	for (int j = 0; j < ns; j++)
	{
		boxList2[j] = new Sphere(Vector3(165 * DRand(), 165 * DRand(), 165 * DRand()), 10, white);
	}
	(*list).Add(std::make_shared<Translate>(std::make_shared<RotateY>(std::make_shared<BvhNode>(boxList2, ns, 0.0, 1.0), 15), Vector3(-100, 270, 395)));

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
	auto t = 0.5f * (dir.y + 1.f);
	return Lerp(Vector3(0.5f, 0.7f, 1.f), Vector3(1, 1, 1), t);
}

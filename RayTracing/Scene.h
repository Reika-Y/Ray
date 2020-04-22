#pragma once
#include <memory>
#include "common/Geometry.h"
#include "Ray.h"
#include "material/Material.h"

class Image;
class Camera;
class Shape;

using Mat = std::shared_ptr<Material>;

class Scene
{
public:
	Scene(int w, int h, int samples);
	~Scene();
	// レンダリングする
	void Render(void);
private:
	void Init(void);
	Vector3 GetColor(const Ray& ray, const Shape* shape, int depth);
	Vector3 BackGroundSky(const Vector3& dir);

	std::unique_ptr<Image>_image;
	std::unique_ptr<Camera>_camera;
	std::unique_ptr<Shape> _shape;
	Vector3 _backColor;		// 背景色
	int _samples;
};


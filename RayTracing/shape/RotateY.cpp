#include "RotateY.h"

RotateY::RotateY(ShapePtr p, float angle)
{
	_ptr = p;
	float radians = (PI / 180.f) * angle;
	_sin = sin(radians);
	_cos = cos(radians);
	_isbox = (*p).BoundingBox(0, 1, _bbox);
	float min[] = { FLT_MAX, FLT_MAX, FLT_MAX };
	float max[] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

	// 頂点数分計算
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				float x = i * _bbox.Max().x + (1 - i) * _bbox.Min().x;
				float y = i * _bbox.Max().y + (1 - j) * _bbox.Min().y;
				float z = i * _bbox.Max().z + (1 - k) * _bbox.Min().z;
				// 回転行列
				float newx = _cos * x + _sin * z;
				float newz = -_sin * x + _cos * z;
				Vector3 tester(newx, y, newz);

				for(int c = 0; c < 3; c++)
				{
					if (tester[c] > max[c])
					{
						max[c] = tester[c];
					}
					if (tester[c] < min[c])
					{
						min[c] = tester[c];
					}
				}
			}
		}
	}

	_bbox = AABB(Vector3(min[0], min[1], min[2]), Vector3(max[0], max[1], max[2]));
}

bool RotateY::Hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	Vector3 origin = ray.Origin();
	Vector3 direction = ray.Direction();
	origin.x = _cos * ray.Origin().x - _sin * ray.Origin().z;
	origin.z = _sin * ray.Origin().x + _cos * ray.Origin().z;
	direction.x = _cos * ray.Direction().x - _sin * ray.Direction().z;
	direction.z = _sin * ray.Direction().x + _cos * ray.Direction().z;
	Ray rotatedR(origin, direction, ray.Time());
	if ((*_ptr).Hit(rotatedR, t_min, t_max, rec))
	{
		Vector3 p = rec.p;
		Vector3 normal = rec.normal;
		p.x = _cos * rec.p.x + _sin * rec.p.z;
		p.z = -_sin * rec.p.x + _cos * rec.p.z;
		normal.x = _cos * rec.normal.x + _sin * rec.normal.z;
		normal.z = -_sin * rec.normal.x + _cos * rec.normal.z;
		rec.p = p;
		rec.normal = normal;
		return true;
	}
	return false;
}

bool RotateY::BoundingBox(float t0, float t1, AABB& box) const
{
	box = _bbox;
	return _isbox;
}

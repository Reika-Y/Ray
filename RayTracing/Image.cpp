#include <iostream>
#include "Image.h"

Image::Image():m_pixcel(nullptr)
{
	_size = { 0,0 };
}

Image::Image(int w, int h)
{
	_size.width = w;
	_size.height = h;
	m_pixcel.reset(new Color[_size.width * _size.height]);
	_filters.emplace_back(std::make_unique<GammaFilter>(GAMMA_FACTOR));
}

Image::~Image()
{
}

Size Image::ImageSize(void) const
{
	return _size;
}

void* Image::Pixcels() const
{
	return m_pixcel.get();
}

void Image::Write(int x, int y, float r, float g, float b)
{
	Vector3 c = { r,g,b };
	for (auto& f : _filters)
	{
		c = (*f).Filter(c);
	}
	int index = _size.width * y + x;
	m_pixcel[index].r = static_cast<unsigned char>(c.x * 255.99);
	m_pixcel[index].g = static_cast<unsigned char>(c.y * 255.99);
	m_pixcel[index].b = static_cast<unsigned char>(c.z * 255.99);
}

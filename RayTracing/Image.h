#pragma once
#include <memory>
#include <vector>
#include "common/Geometry.h"
#include "ImageFilter.h"

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class Image
{
public:
	Image();
	Image(int w, int h);
	~Image();
	Size ImageSize(void)const;
	void* Pixcels()const;
	void Write(int x, int y, float r, float g, float b);
private:
	Size _size;
	std::unique_ptr<Color[]>m_pixcel;
	std::vector<std::unique_ptr<ImageFilter>> _filters;
};


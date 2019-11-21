#include "ImageFilter.h"

GammaFilter::GammaFilter(float factor)
{
	_factor = factor;
}

Vector3 GammaFilter::Filter(const Vector3& c) const
{
	return LinearToGamma(c, _factor);
}

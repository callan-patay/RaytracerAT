#include "BBox.h"
#include <algorithm>
BBox::BBox()
{
}

BBox::BBox(const Vec3 & min, const Vec3 & max) : min(min), max(max)
{
	extent = max - min;
}

BBox::BBox(const Vec3 & p): min(p), max(p)
{
	extent = max - min;
}

bool BBox::intersect(const Ray & ray, float * tnear, float * tfar) const
{
	return false;
}

void BBox::expandToInclude(const Vec3 & p)
{
	min = std::min(min, p);
	max = std::max(max, p);
	extent = max - min;
}

void BBox::expandToInclude(const BBox & b)
{
	min = std::min(min, b.min);
	max = std::max(max, b.max);
	extent = max - min;
}

int BBox::maxDimension() const
{
	int result = 0;
	if (extent._y > extent._x)
	{
		result = 1;
	}
	
	if (extent._z > extent._y)
	{
		result = 2;
	}


	return result;
}

float BBox::surfaceArea()
{
	return 0.0f;
}

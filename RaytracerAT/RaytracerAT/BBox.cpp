#include "BBox.h"
#include <algorithm>
#include <utility>
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

bool BBox::intersect(const Ray & ray) const
{
	float tmin = (min._x - ray._origin._x) / ray._direction._x;
	float tmax = (max._x - ray._origin._x) / ray._direction._x;

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (min._y - ray._origin._y) / ray._direction._y;
	float tymax = (max._y - ray._origin._y) / ray._direction._y;

	if (tymin > tymax)
	{
		std::swap(tymin, tymax);
	}
	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (min._z - ray._origin._z) / ray._direction._z;
	float tzmax = (max._z - ray._origin._z) / ray._direction._z;

	if (tzmin > tzmax) {
		std::swap(tzmin, tzmax);
	}

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return true;
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

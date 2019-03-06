#pragma once

#include "Ray.h"
#include "Vector3.h"
#include <stdint.h>

struct BBox 
{
	Vec3 min, max, extent;
	BBox();
	BBox(const Vec3& min, const Vec3& max);
	BBox(const Vec3& p);

	bool intersect(const Ray& ray) const;
	void expandToInclude(const Vec3& p);
	void expandToInclude(const BBox& b);
	int maxDimension() const;
	float surfaceArea();
};
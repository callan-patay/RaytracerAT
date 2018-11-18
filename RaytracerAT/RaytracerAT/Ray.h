#pragma once
#include "Vector3.h"


class Ray
{
public:
	Ray(Vec3 pos, Vec3 dir);
	~Ray() = default;

	Vec3 Calculate_position(float t) const;

	Vec3 _origin;
	Vec3 _direction;
};
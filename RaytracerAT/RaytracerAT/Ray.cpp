#include "Ray.h"

Ray::Ray(Vec3 pos, Vec3 dir) : _origin(pos), _direction(dir)
{
}

Vec3 Ray::Calculate_position(float t) const
{
	return _origin + _direction * t;
}

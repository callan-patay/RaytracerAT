#include "Plane.h"
#include <cmath>

Plane::Plane(float distance, Vec3 vecOrthagonal, sf::Color c, Material m): Surface(c,m), _distance(distance)
{
	_vecOrthagonal = vecOrthagonal*-1;
	_vecOrthagonal.normalize();
}

Plane::Plane(float distance, Vec3 vecOrthagonal, sf::Color c): Plane(distance, vecOrthagonal, c, Material(50, 0.0))
{
}

Vec3 Plane::Normal(const Vec3 &)
{
	return _vecOrthagonal;
}

std::pair<bool, float> Plane::Collision(const Ray &r)
{
	float t = 0;
	if (r._direction * _vecOrthagonal != 0)
	{
		t = (-(r._origin * _vecOrthagonal) - _distance) / (r._direction * _vecOrthagonal);
	}
	else
	{
		t = -1;
	}

	if (t >= 0)
	{
		return{ true, t };
	}


	return { false, t };
}

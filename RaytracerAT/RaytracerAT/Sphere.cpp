#include "Sphere.h"

#include <cmath>




Sphere::Sphere(Vec3 centre, float radius, sf::Color c , Material m) : Surface(c,m), _centre(centre), _radius(radius)
{
}

Sphere::Sphere(Vec3 centre, float radius, sf::Color c): Sphere(centre, radius, c, Material(50, 0.0))
{
}

Vec3 Sphere::Normal(const Vec3 & pos)
{
	Vec3 N = pos - _centre;
	N.normalize();
	return N;
}

std::pair<bool, float> Sphere::Collision(const Ray & r)
{
	float a = r._direction.squared();
	float b = 2 * (r._origin * r._direction - _centre * r._direction);
	float c = r._origin.squared() + _centre.squared() - (r._origin * _centre) * 2 - _radius*_radius;

	float discriminant = b*b - 4 * a*c;

	float t = -1;
	float t1 = 0;
	float t2 = 0;

	if (discriminant > 0.00001 && a != 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		t = t1 > t2 ? t2 : t1;
	}
	else if (discriminant > 0)
	{
		t = -b / (2 * a);
	}

	if (t >= 0)
	{
		return { true, t };
	}

	return { false, t };
}

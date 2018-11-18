#pragma once
#include "Surface.h"
class Sphere : public Surface
{
public:
	Sphere(Vec3 centre, float ray, sf::Color, Material);
	Sphere(Vec3 centre, float ray, sf::Color);
	~Sphere() = default;


	Vec3 Normal(const Vec3& pos);
	std::pair<bool, float> Collision(const Ray&);

private:
	Vec3 _centre;
	float _ray;
};


#pragma once
#include "Surface.h"
class Plane :
	public Surface
{
public:
	Plane(float distance, Vec3 vecOrthagonal, sf::Color, Material);
	Plane(float distance, Vec3 vecOrthagonal, sf::Color);
	~Plane() = default;

	Vec3 Normal(const Vec3&);
	std::pair<bool, float> Collision(const Ray&);
private:
	float _distance;
	Vec3 _vecOrthagonal;
};


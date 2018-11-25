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

	BBox getBBox() const {
		return BBox(_centre - Vec3(_ray, _ray, _ray), _centre + Vec3(_ray, _ray, _ray));
	}

	Vec3 getCentroid() const {
		return _centre;
	}

private:
	Vec3 _centre;
	float _ray;
};


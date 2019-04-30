#pragma once

#include <SFML\Graphics.hpp>

#include "Vector3.h"
#include "Ray.h"








class LightSource
{
public:
	LightSource(Vec3 pos);
	LightSource(Vec3 pos, float);
	LightSource(Vec3 pos, sf::Color);
	LightSource(Vec3 pos, float, sf::Color);
	~LightSource() = default;

	Ray createRay(const Vec3& pos)const;

	std::pair<bool, float> Collision(Ray&) const;

	Vec3 _position;
	float _lightIntensity;
	sf::Color _colour;


};


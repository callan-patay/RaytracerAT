#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Ray.h"
#include "Material.h"
#include "Vector3.h"
#include "BBox.h"

class Surface
{
public:
	Surface(sf::Color&, Material);
	Surface(sf::Color&);

	virtual ~Surface() = default;


	virtual Vec3 Normal(const Vec3&) = 0;
	virtual std::pair<bool, float> Collision(const Ray&) = 0;
	virtual BBox getBBox() const = 0;
	virtual Vec3 getCentroid() const = 0;
	sf::Color _colour;
	Material _material;
};
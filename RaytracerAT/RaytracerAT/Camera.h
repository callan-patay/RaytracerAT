#pragma once

#include <SFML\System.hpp>
#include<SFML\Graphics.hpp>
#include "Vector3.h"
#include "Ray.h"

class Camera
{
public:
	Camera(Vec3, Vec3, float, sf::Vector2i, Vec3);
	Camera(Vec3, Vec3, float, sf::Vector2i);
	~Camera() = default;

	Ray createRay(int x, int y);
	const sf::Image& Image() const;
	sf::Vector2i _resolution;
	sf::Image _result;
private:
	Vec3 _position;
	Vec3 _direction;

	float _zoom;

	Vec3 _up;
	Vec3 _right;

	float _IR;
	float _MX;
	float _MY;
};
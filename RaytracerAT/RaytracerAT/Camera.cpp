#include "Camera.h"
#include <cmath>


Camera::Camera(Vec3 p, Vec3 d, float z, sf::Vector2i res, Vec3 orientation)
{
	_position = p;
	_direction = d - p;
	_direction.normalize();
	_zoom = z;
	_resolution = res;

	_up = orientation;
	_up = _up - _direction * (_direction * _up);

	_IR = sqrt(_resolution.x*_resolution.x + _resolution.y*_resolution.y);
	_MX = _resolution.x / 2;
	_MY = _resolution.y / 2;

	if (_direction == _up)
	{
		_right = Vec3(1, 0, 0);
	}
	else
	{
		_right = _direction.vector_procduct(_up);
	}

	_result.create(res.x, res.y);


}

Camera::Camera(Vec3 p, Vec3 d , float z, sf::Vector2i res): Camera(p, d, z, res, Vec3(0,0,1))
{
}

Ray Camera::createRay(int x, int y)
{
	float X = (x - _MX) / _IR;
	float Y = (abs(_resolution.y - y) - _MY) / _IR;
	Vec3 direction = _direction*_zoom + _right * X + _up * Y;
	direction.normalize();

	return Ray(_position + direction * 0.1, direction);
}

const sf::Image & Camera::Image() const
{
	return _result;
}

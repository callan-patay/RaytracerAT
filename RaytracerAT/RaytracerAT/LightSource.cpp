#include "LightSource.h"

LightSource::LightSource(Vec3 pos): LightSource(pos, 1.0, sf::Color(255,255,255))
{
}

LightSource::LightSource(Vec3 pos, float f): LightSource(pos, f, sf::Color(255,255,255))
{
}

LightSource::LightSource(Vec3 pos, sf::Color c): LightSource(pos, 1.0, c)
{
}

LightSource::LightSource(Vec3 pos, float f, sf::Color c): _position(pos), _lightIntensity(f), _color(c)
{
}

Ray LightSource::createRay(const Vec3 & pos) const
{
	Vec3 direction = _position - pos;
	direction.normalize();
	return Ray(pos + direction*0.1, direction);
}

std::pair<bool, float> LightSource::Collision(Ray &r) const
{
	float t = (r._origin - _position) *(r._direction*-1);
	if (t > 0)
	{
		return std::make_pair(true, t);
	}

	return std::make_pair(false, -1);
}

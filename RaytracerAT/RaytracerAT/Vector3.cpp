#include "Vector3.h"
#include <cmath>
Vec3::Vec3(float x, float y, float z) : _x(x), _y(y), _z(z)
{

}

Vec3::Vec3() : Vec3(0,0,0)
{
}

Vec3 Vec3::operator+(const Vec3 & b) const
{
	return { _x + b._x,_y + b._y,_z + b._z };
}

Vec3 Vec3::operator-(const Vec3 & b) const
{
	return { _x - b._x,_y - b._y,_z - b._z };
}

float Vec3::operator*(const Vec3 & b) const
{
	return dot_product(b);
}

Vec3 Vec3::operator*(const float & b) const
{
	return { _x*b,_y*b,_z*b };
}

Vec3 Vec3::operator/(const Vec3 & b) const
{
	return { _x / b._x,_y / b._y,_z / b._z };

}

bool Vec3::operator==(const Vec3 & b) const
{
	return (_x == b._x && _y == b._y && _z == b._z);
}



float Vec3::length2() const
{
	return _x*_x + _y*_y + _z*_z;
}

float Vec3::length() const
{
	return sqrt(length2());
}

void Vec3::normalize()
{
	float n = length();
	if (n != 0)
	{
		_x /= n;
		_y /= n;
		_z /= n;
	}
}

float Vec3::dot_product(const Vec3 & v) const
{
	return _x*v._x + _y *v._y + _z*v._z;
}

Vec3 Vec3::vector_procduct(const Vec3 & b) const
{
	return { _y * b._z - _z * b._y,
		_z * b._x - _x * b._z,
		_x * b._y - _y * b._x
	};
}

std::ostream & operator<<(std::ostream & os, const Vec3 & v)
{
	os << v._x << " " << v._y << " " << v._z << '\n';
	return os;
}

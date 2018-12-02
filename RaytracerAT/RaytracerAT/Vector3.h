#pragma once

#include <iostream>

class Vec3
{
public:
	Vec3(float, float, float);
	Vec3();
	~Vec3() = default;


	float _x;
	float _y;
	float _z;
	Vec3 operator+(const Vec3& b) const;
	Vec3 operator-(const Vec3& b) const;
	float operator*(const Vec3& b) const;
	Vec3 operator*(const float& b) const;
	Vec3 operator/(const Vec3& b) const;

	bool operator==(const Vec3& b) const;
	float& operator[](const unsigned int i) { return (&_x)[i]; }
	bool operator>(const Vec3& b) const { return (_x > b._x && _y > b._y && _z > b._z); };
	bool operator<(const Vec3& b) const { return (_x < b._x && _y < b._y && _z < b._z); };
	const float& operator[](const unsigned int i) const { return (&_x)[i]; }


	float length2() const;
	float length() const;

	void normalize();

	float dot_product(const Vec3& v) const;
	Vec3 vector_procduct(const Vec3&) const;

};

std::ostream& operator<< (std::ostream& os, const Vec3& v);
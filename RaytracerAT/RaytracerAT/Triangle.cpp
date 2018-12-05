#include "Triangle.h"

//Triangle::Triangle(Vec3 _v1, Vec3 _v2, Vec3 _v3, sf::Color c, Material m) : v1(_v1), v2(_v2), v3(_v3), Surface(c, m)
//{
//}
//
//Triangle::Triangle(Vec3 _v1, Vec3 _v2, Vec3 _v3, sf::Color c): Triangle(_v1, _v2, _v3, c, Material(50, 0.0))
//{
//}
//
//Vec3 Triangle::Normal(const Vec3 & pos)
//{
//	Vec3 v1v2 = v2 - v1;
//	Vec3 v1v3 = v3 - v1;
//
//	Vec3 N = v1v2.vector_procduct(v1v3);
//	N.normalize();
//
//	
//
//
//
//	return N;
//}
//
//std::pair<bool, float> Triangle::Collision(const Ray &ray)
//{
//	float t = -1;
//	constexpr float kEpsilon = 1e-8;
//	Vec3 v1v2 = v2 - v1;
//	Vec3 v1v3 = v3 - v1;
//	Vec3 N = v1v2.vector_procduct(v1v3);
//	float denom = N.dot_product(N);
//
//	//if the ray and plane are parallel, ignore it
//	float dotRayDir = N.dot_product(ray._direction);
//	if (fabs(dotRayDir < kEpsilon))
//	{
//		return { false, t };
//	}
//
//	float d = N.dot_product(v1);
//	t = (N.dot_product(ray._origin) + d) / dotRayDir;
//	if (t < 0)
//	{
//		return { false, -1 };
//	}
//
//	Vec3 P = ray.Calculate_position(t);
//
//	Vec3 C;
//
//	//edge 1
//	Vec3 edge1 = v2 - v1;
//	Vec3 vp1 = P - v1;
//	C = edge1.vector_procduct(vp1);
//	if (N.dot_product(C) < 0)
//	{
//		return { false, -1 };
//	}
//
//	//edge 2
//	Vec3 edge2 = v3 - v2;
//	Vec3 vp2 = P - v2;
//	C = edge2.vector_procduct(vp2);
//	if ((u = N.dot_product(C)) < 0)
//	{
//		return { false, -1 };
//	}
//
//	//edge 3
//	Vec3 edge3 = v1 - v3;
//	Vec3 vp3 = P - v3;
//	C = edge3.vector_procduct(vp3);
//	if ((v = N.dot_product(C)) < 0)
//	{
//		return { false, -1 };
//	}
//
//	u /= denom;
//	v /= denom;
//
//
//	return { true, t };
//}

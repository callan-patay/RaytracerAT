#pragma once

class Material
{
public:
	Material(int _spec, float _reflec);
	~Material() = default;

	int _specular;
	float _reflection;
};
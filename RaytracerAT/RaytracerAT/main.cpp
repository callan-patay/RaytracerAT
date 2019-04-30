#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "LightSource.h"
#include <iostream>






int main()
{
	Scene S;

	S.addCamera(Camera(Vec3(20, -10, 5), Vec3(1, 15, 1), 1, sf::Vector2i(1600, 900)));

	S.addLight(LightSource(Vec3(50, -50, 100)));

	float _x = 10;
	float _y = 10;

	for (int x = 0; x < _x; x++)
	{
		for (int y = 0; y < _y; y++)
		{
			S.addSurface(new Sphere(Vec3(x, y, 0), 0.5, sf::Color(255, 0, 0)));
		}
	}

	sf::Clock clock;
	S.createImage(0);
	sf::Time elapsed = clock.getElapsedTime();
	std::cout << elapsed.asSeconds() << std::endl;
	S.saveImage(0, "Image1.png");
	S.displayImage(0);



	return 0;
}
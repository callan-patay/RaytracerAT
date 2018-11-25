#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "LightSource.h"
#include <iostream>




int main()
{
	Scene S;

	S.addCamera(Camera(Vec3(0, 0, 1), Vec3(0, 15, 2), 1, sf::Vector2i(1600, 900)));

	S.addLight(LightSource(Vec3(50, -50, 100)));

	//S.addSurface(new Plane(1, Vec3(0, 0, -1), sf::Color(13, 71, 171)));

	S.addSurface(new Sphere(Vec3(3, 25, 6), 1, sf::Color(255, 0, 0)));
	S.addSurface(new Sphere(Vec3(-3, 16, 0), 1, sf::Color(0, 255, 0)));
	S.addSurface(new Sphere(Vec3(3, 15, 0), 1, sf::Color(0, 0, 255)));

	S.createImage(0);
	S.saveImage(0, "Image.png");



	return EXIT_SUCCESS;
}
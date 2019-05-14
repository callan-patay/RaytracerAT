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

	//image1
	//S.addCamera(Camera(Vec3(20, -10, 5), Vec3(1, 15, 1), 1, sf::Vector2i(1600, 900)));

	//S.addLight(LightSource(Vec3(50, 50, -50)));
	//S.addLight(LightSource(Vec3(50, 50, 50)));
	//float _x = 10;
	//float _y = 10;

	//for (int x = 0; x < _x; x++)
	//{
	//	for (int y = 0; y < _y; y++)
	//	{
	//		S.addSurface(new Sphere(Vec3(x, y, 0), 0.5, sf::Color(255, 0, 0)));
	//	}
	//}



	//image2
	//S.addCamera(Camera(Vec3(5, 0, 0), Vec3(5, 10, 0), 0.75, sf::Vector2i(1600, 900)));
	//S.addLight(LightSource(Vec3(10, 0, 0), sf::Color(255, 0, 0)));
	//S.addLight(LightSource(Vec3(-10, 0, 0), sf::Color(0, 255, 0)));
	//S.addLight(LightSource(Vec3(0, 0, 10), sf::Color(0, 0, 255)));
	//S.addLight(LightSource(Vec3(0, 0, -10), sf::Color(100, 0, 100)));


	//S.addSurface(new Sphere(Vec3(10, 20, 0), 1, sf::Color(255, 255, 255)));
	//S.addSurface(new Sphere(Vec3(4, 20, -5), 1, sf::Color(255, 255, 255)));
	//S.addSurface(new Sphere(Vec3(0, 20, 5), 1, sf::Color(255, 255, 255)));
	//S.addSurface(new Sphere(Vec3(2, 20, 8), 1, sf::Color(255, 255, 255)));
	//S.addSurface(new Sphere(Vec3(6, 20, 6), 1, sf::Color(255, 255, 255)));
	//S.addSurface(new Sphere(Vec3(-5, 20, 2), 1, sf::Color(255, 255, 255)));



	//image3
	//Material Mirror(500, 1.0);
	//S.addCamera(Camera(Vec3(5, -15, 0), Vec3(5, 10, 0), 1.3, sf::Vector2i(1600, 900)));

	//S.addLight(LightSource(Vec3(10, 10, 0)));
	//S.addLight(LightSource(Vec3(10, 0, 0)));

	//S.addSurface(new Sphere(Vec3(4, 8, -3), 1, sf::Color(255, 0, 0), Mirror));
	//S.addSurface(new Sphere(Vec3(6, 8, 1), 1, sf::Color(0, 0, 255), Mirror));
	//S.addSurface(new Sphere(Vec3(3, 8, 0), 1, sf::Color(0, 255, 0), Mirror));

	//image4
	//Material lowSpecular(10, 0.0);
	//Material mediumSpecular(50, 0.0);
	//Material highSpecular(100, 0.0);


	//S.addCamera(Camera(Vec3(0, 0, 0), Vec3(0, 1, 1), 0.25, sf::Vector2i(1600, 900)));

	//S.addLight(LightSource(Vec3(2, 0, 0), 0.5));
	//S.addLight(LightSource(Vec3(0, 0, 2), 1.0));

	//S.addSurface(new Sphere(Vec3(0, -2, 2), 1, sf::Color(255, 0, 0), lowSpecular));
	//S.addSurface(new Sphere(Vec3(0, 2, 2), 1, sf::Color(255, 0, 0), mediumSpecular));
	//S.addSurface(new Sphere(Vec3(0, 4 ,2), 1, sf::Color(255, 0, 0), highSpecular));

	//imagepooltable
	S.addCamera(Camera(Vec3(20, -10, 5), Vec3(1, 15, 1), 1, sf::Vector2i(1600, 900)));

	S.addLight(LightSource(Vec3( 20, 5, 30)));

	//row1
	S.addSurface(new Sphere(Vec3(1, 1, 0), 1, sf::Color(255, 0, 0)));
	S.addSurface(new Sphere(Vec3(3, 1, 0), 1, sf::Color(255, 165, 0)));
	S.addSurface(new Sphere(Vec3(5, 1, 0), 1, sf::Color(255, 0, 0)));
	S.addSurface(new Sphere(Vec3(7, 1, 0), 1, sf::Color(255, 165, 0)));
	S.addSurface(new Sphere(Vec3(9, 1, 0), 1, sf::Color(255, 165, 0)));

	//row2
	S.addSurface(new Sphere(Vec3(2, 3, 0), 1, sf::Color(255, 165, 0)));
	S.addSurface(new Sphere(Vec3(4, 3, 0), 1, sf::Color(255, 0, 0)));
	S.addSurface(new Sphere(Vec3(6, 3, 0), 1, sf::Color(255, 165, 0)));
	S.addSurface(new Sphere(Vec3(8, 3, 0), 1, sf::Color(255, 0, 0)));

	//row3
	S.addSurface(new Sphere(Vec3(3, 5, 0), 1, sf::Color(255, 0, 0)));
	S.addSurface(new Sphere(Vec3(5, 5, 0), 1, sf::Color(0, 0, 0)));
	S.addSurface(new Sphere(Vec3(7, 5, 0), 1, sf::Color(255, 165, 0)));

	//row4
	S.addSurface(new Sphere(Vec3(4, 7, 0), 1, sf::Color(255, 165, 0)));
	S.addSurface(new Sphere(Vec3(6, 7, 0), 1, sf::Color(255, 0, 0)));

	//row5
	S.addSurface(new Sphere(Vec3(5, 9, 0), 1, sf::Color(255, 0, 0)));


	//white ball
	S.addSurface(new Sphere(Vec3(5, 20, 0), 1, sf::Color(255, 255, 255)));

	sf::Clock clock;
	S.createImage(0);
	sf::Time elapsed = clock.getElapsedTime();
	std::cout << elapsed.asSeconds() << std::endl;
	S.saveImage(0, "Image3.png");
	S.displayImage(0);



	return 0;
}
#include "Scene.h"
#include "Colour.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <thread>

Scene::Scene(): Scene(sf::Color(0,0,0), 0.1)
{
}

Scene::Scene(sf::Color c): Scene(c, 0.1)
{
}

Scene::Scene(float ambient): Scene(sf::Color(0,0,0), ambient)
{
}

Scene::Scene(sf::Color c, float ambient) : ambientColour(c), ambientLight(ambient), bvh(nullptr)
{
}


Scene::~Scene()
{
	for (auto o : objList)
	{
		delete o;
	}

	delete bvh;
}

void Scene::addCamera(Camera c)
{
	camList.push_back(c);
}

void Scene::addLight(LightSource l)
{
	lightList.push_back(l);
}

void Scene::addSurface(Surface * s)
{
	objList.push_back(s);
}

void Scene::renderSection(int heightstart, int heightfinish, int width, int height, int numCam, int depthMax)
{

	for (int y = heightstart; y < heightfinish; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Ray r_camera = camList[numCam].createRay(x, y);
			sf::Color c = launchRay(numCam, r_camera, depthMax);

			camList[numCam]._result.setPixel(x, y, c);
		}
	}
}

void Scene::createImage(unsigned int numCam)
{
	return createImage(numCam, 5, false);
}

void Scene::createImage(unsigned int numCam, int depthMax)
{
	return createImage(numCam, depthMax, false);
}

void Scene::createImage(unsigned int numCam, bool debug)
{
	return createImage(numCam, 5, debug);
}

void Scene::createImage(unsigned int numCam, int depthMax, bool debug)
{
	int h = camList[numCam]._resolution.y;
	int w = camList[numCam]._resolution.x;

	int nbr = (h * 1);
	float b = nbr / 100;
	int p = 0;
	int r = 0;
	
	//please ignore this
	int zero = 0;
	int one = (h / 4) * 2;
	int two = (h / 4) * 3;
	int three = h / 4;
	int four = 4;
	std::thread thread1(&Scene::renderSection,this, zero, three, w, h, numCam, depthMax);
	std::thread thread2(&Scene::renderSection,this,  three, one , w, h, numCam, depthMax);
	std::thread thread3(&Scene::renderSection,this, one, two, w, h, numCam, depthMax);
	std::thread thread4(&Scene::renderSection, this, two, h, w, h, numCam, depthMax);
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();


}




float Scene::clamp(const float & lo, const float & hi, const float & v)
{
	return std::max(lo, std::min(hi, v));
}

void Scene::displayImage(unsigned int numCam)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;

	unsigned int length = camList[numCam]._resolution.x;
	unsigned int height = camList[numCam]._resolution.y;

	sf::RenderWindow window(sf::VideoMode(length, height, 32), "Raytrace", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	sf::Texture T;

	T.loadFromImage(camList[numCam].Image());

	sf::Sprite sprite;
	sprite.setTexture(T);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}
}

void Scene::saveImage(unsigned int numCam, const std::string fileName)
{
	camList[numCam].Image().saveToFile(fileName);
}

void Scene::createBVH()
{
	bvh = new BVH();
	bvh->build(objList);
}

sf::Color Scene::launchRay(unsigned int numCam, const Ray & ray, int depth)
{
	if (depth <= 0)
	{
		return sf::Color(0, 0, 0);
	}


	

	std::pair<Surface*, float> P = Intersection(ray);
	//std::pair<Surface*, float> P = bvh->intersect(ray);
	Surface* surface = P.first;
	Vec3 pos = ray.Calculate_position(P.second);

	if (surface == nullptr)
	{
		return ambientColour;
	}

	Vec3 norm = surface->Normal(pos);
	sf::Color lightCalc = PhongIllumination(surface, ray._direction, pos, norm);

	if (surface->_material._reflection > 0)
	{
		Ray rayReflect = reflection(pos, norm, ray._direction);
		sf::Color lightReflect = launchRay(numCam, rayReflect, depth - 1)*(surface->_material._reflection);
		lightCalc = lightCalc + lightReflect * 2;
	}
	lightCalc.r = clamp(0, 255, lightCalc.r);
	lightCalc.g = clamp(0, 255, lightCalc.g);
	lightCalc.b = clamp(0, 255, lightCalc.b);


	return lightCalc;
}

sf::Color Scene::PhongIllumination(Surface * surface, const Vec3 & rayDir, const Vec3 & pos, const Vec3 & N)
{
	sf::Color colour = surface->_colour * ambientLight;

	for (const LightSource& light : lightList)
	{
		Ray lightRay = light.createRay(pos);
		float visibleObj = light.Collision(lightRay).second;

		std::pair<Surface*, float> P = Intersection(lightRay);
		//std::pair<Surface*, float> P = bvh->intersect(lightRay);
		Surface* s = P.first;
		float t = P.second;

		if (s == nullptr || visibleObj < t)
		{
			Vec3 L = lightRay._direction;
			Vec3 R = N * 2 * (N*L) - L;
			R.normalize();
			Vec3 V = rayDir * -1;
			float cos1 = (N * L);

			if (cos1 > 0)
			{
				//diffuse
				float kd = cos1*light._lightIntensity;


				//specular
				float cos2 = (R*V);
				float ka = cos2 > 0 ? cos2 : 0;
				ka = pow(ka, surface->_material._specular)*light._lightIntensity;
				colour += (light._color*surface->_colour)*kd + light._color*ka;
			}
		}
	}

	return colour;
}

std::pair<Surface*, float> Scene::Intersection(const Ray & ray)
{
	float t_min = 500;
	Surface* surface = nullptr;
	bool visible = false;

	for (auto s : objList)
	{
		std::pair<bool, float> P = s->Collision(ray);
		float t = P.second;
		if (P.first && (t < t_min || visible == false))
		{
			t_min = t;
			surface = s;
			visible = true;
		}
	}

	if (visible)
	{
		return { surface, t_min };
	}


	return { nullptr, -1.0 };
}

Ray Scene::reflection(const Vec3 & pos, const Vec3 & normal, const Vec3 & rayDir)
{
	Vec3 direction = normal*(normal*rayDir)*-2 + rayDir;
	direction.normalize();
	return Ray(pos + direction*0.1, direction);
}

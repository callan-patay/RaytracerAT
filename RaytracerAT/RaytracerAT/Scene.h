#pragma once
#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "Vector3.h"
#include "Surface.h"
#include "Ray.h"
#include "Camera.h"
#include "LightSource.h"
#include "BVH.h"

//struct Node {
//	//bounding Volume;
//	Node leftChild;
//	Node rightChild;
//
//};


class Scene
{
public:
	Scene();
	Scene(sf::Color);
	Scene(float);
	Scene(sf::Color, float);
	~Scene();

	void addCamera(Camera);
	void addLight(LightSource);
	void addSurface(Surface*);

	void createImage(unsigned int numCam);
	void createImage(unsigned int numCam, int depthMax);
	void createImage(unsigned int numCam, bool debug);
	void createImage(unsigned int numCam, int depthMax, bool debug);
	float clamp(const float &lo, const float &hi, const float &v);
	void displayImage(unsigned int numCam);
	void saveImage(unsigned int numCam, const std::string fileName);

private:
	sf::Color launchRay(unsigned int numCam, const Ray&, int depth);
	sf::Color PhongIllumination(Surface*, const Vec3& rayDir, const Vec3& pos, const Vec3& N);

	std::pair<Surface*, float> Intersection(const Ray&);

	static Ray reflection(const Vec3& pos, const Vec3& normal, const Vec3& rayDir);

	sf::Color ambientColour;
	float ambientLight;

	std::vector<Surface*> objList;
	std::vector<Camera> camList;
	std::vector<LightSource> lightList;

};


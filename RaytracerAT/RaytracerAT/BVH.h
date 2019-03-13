#pragma once
#include "BBox.h"
#include "BVHNode.h"
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <limits>
#include <stack>
#include "Ray.h"

class Surface;

constexpr float infinity = std::numeric_limits<float>::max();

struct StackItem
{
	BVHNode* ptr;
	float t;
};


class BVH
{
public:
	BVH();
	~BVH();



	void build(std::vector<Surface*> &objs);
	void buildRecursive(int leftIndex, int rightIndex, BVHNode* node, int depth);
	std::pair<Surface*, float> intersect(const Ray& ray);
	std::pair<Surface*, float> intersect(const Ray & ray, BVHNode* currentNode, float &t);
	//bool intersect(const Ray& ray)


private:
	std::vector<Surface*> copies;
	std::vector<BVHNode> nodes;
	BVHNode* rootNode;
	BBox worldBox;
	int left_index;
	int right_index;
	int depth;
	std::stack<StackItem> stack;

};
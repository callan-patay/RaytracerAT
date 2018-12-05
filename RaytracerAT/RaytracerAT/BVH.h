#pragma once
#include "BBox.h"
#include "BVHNode.h"
#include <vector>
#include <stdint.h>
#include <algorithm>
#include "Surface.h"
#include "Ray.h"


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
private:
	std::vector<Surface*> copies;
	std::vector<BVHNode> nodes;
	BBox worldBox;
	int left_index;
	int right_index;
	int depth;


};
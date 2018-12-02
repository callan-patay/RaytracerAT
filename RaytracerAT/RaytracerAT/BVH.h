#pragma once
#include "BBox.h"
#include <vector>
#include <stdint.h>
#include "Surface.h"
#include "Ray.h"


struct BVHFlatNode {
	BBox bbox;
	int start, nPrims, rightOffSet;

};


class BVH
{
	int nNodes, nLeafs, leafSize;
	std::vector<Surface*>* build_prims;

	void build();

	BVHFlatNode *flatTree;

public:
	BVH(std::vector<Surface*>* surfaces, int leafSize = 4);
	std::pair<Surface*, float> Intersection(const Ray& ray) const;

	~BVH();

};
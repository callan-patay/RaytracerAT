#pragma once
#include "BBox.h"
#include "BVHNode.h"
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <limits>
#include <stack>
#include "Ray.h"
#include "BVHBranch.h"
class Surface;


class BVHManager
{
public:
	BVHManager();
	~BVHManager();

	void build(std::vector<Surface*> &objs);

	std::vector<Surface*> getObjs();

private:
	BVHBranch * rootBranch;





};


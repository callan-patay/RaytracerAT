#pragma once

#include <vector>
#include "BBox.h"
class Surface;


class BVHBranch
{
public:
	BVHBranch();
	~BVHBranch();



	void init(std::vector<BBox*> boxes);




	void intersection(std::vector<Surface*> objs);
private:
	BVHBranch * leftBranch;
	BVHBranch * rightBranch;
	BBox* branchBox;
};


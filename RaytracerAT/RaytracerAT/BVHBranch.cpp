#include "BVHBranch.h"
#include "ComparePrimitives.h"
#include <algorithm>


BVHBranch::BVHBranch()
{
}


BVHBranch::~BVHBranch()
{
}

void BVHBranch::init(std::vector<BBox*> boxes)
{
	branchBox = new BBox();

	branchBox->min = boxes.at(0)->min;
	branchBox->max = boxes.at(0)->max;

	for (auto& box : boxes)
	{
		branchBox->min._y = std::min(branchBox->min._y, box->min._y);
		branchBox->min._x = std::min(branchBox->min._x, box->min._x);
		branchBox->min._z = std::min(branchBox->min._z, box->min._z);
													
		branchBox->max._y = std::max(branchBox->max._y, box->max._y);
		branchBox->max._x = std::max(branchBox->max._x, box->max._x);
		branchBox->max._z = std::max(branchBox->max._z, box->max._z);
	}
	 
	// calculate best split of boxes
	ComparePrimitives cmp;
	cmp.sort_dim = 0;
	std::sort(boxes.begin(), boxes.end(), cmp);
	// assign boxes to left and right branches

	// init each branch

}

void BVHBranch::intersection(std::vector<Surface*> objs)
{
}

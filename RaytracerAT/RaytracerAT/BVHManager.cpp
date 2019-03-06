#include "BVHManager.h"
#include "Surface.h"


BVHManager::BVHManager()
{
}


BVHManager::~BVHManager()
{
}

void BVHManager::build(std::vector<Surface*>& objs)
{
	std::vector<BBox*> boxes;
	rootBranch = new BVHBranch();

	for (auto& obj : objs)
	{
		BBox * tempBox;

		tempBox->min._y = obj->getBBox().min._y;
		tempBox->min._x = obj->getBBox().min._x;
		tempBox->min._z = obj->getBBox().min._z;
		tempBox->max._y = obj->getBBox().max._y;
		tempBox->max._x = obj->getBBox().max._x;
		tempBox->max._z = obj->getBBox().max._z;

		boxes.push_back(tempBox);
	}

	rootBranch->init(boxes);
}

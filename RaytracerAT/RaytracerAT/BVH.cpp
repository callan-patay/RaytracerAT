#include "BVH.h"

BVH::BVH()
{
}

BVH::~BVH()
{
}
//http://fileadmin.cs.lth.se/cs/education/edan30/lectures/s2-bvh.pdf

void BVH::build(std::vector<Surface*>& objs)
{
	BVHNode rootNode;
	worldBox = BBox();

	for (int i; i < objs.size(); i++)
	{
		worldBox.expandToInclude(objs[i]->getBBox());
		copies.push_back(objs[i]);
	}

	rootNode.setBBox(worldBox);

	buildRecursive(0, copies.size(), &rootNode, 0);



}

void BVH::buildRecursive(int leftIndex, int rightIndex, BVHNode * node, int depth)
{
	if ((rightIndex - leftIndex) <= 4)
	{
		node->makeLeaf(leftIndex, rightIndex);
	}
	else
	{
		int splitIndex = rightIndex / 2;

		BBox leftBox = BBox();
		leftBox.min = node->getBBox().min;
		leftBox.max = node->getBBox().max;
		leftBox.max._x -= node->getBBox().extent._x / 2;
		leftBox.extent = leftBox.max - leftBox.min;
		BBox rightBox = BBox();
		rightBox.min = node->getBBox().min;
		rightBox.min._x += node->getBBox().extent._x / 2;
		rightBox.max = node->getBBox().max;
		rightBox.extent = rightBox.max - rightBox.min;

		BVHNode * leftNode;
		leftNode->setBBox(leftBox);
		BVHNode * rightNode;
		rightNode->setBBox(rightBox);


		
		buildRecursive(left_index, splitIndex, leftNode, depth + 1);
		buildRecursive(splitIndex, left_index, rightNode, depth + 1);
	}
}

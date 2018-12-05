#include "BVHNode.h"

BVHNode::BVHNode()
{
}

void BVHNode::setBBox(BBox box)
{
	bbox = box;
}

void BVHNode::makeLeaf(unsigned int index_, unsigned int n_objs_)
{
	leaf = true;
	index = index_;
	n_objs = n_objs_;
}

void BVHNode::makeNode(unsigned int left_index_, unsigned int n_objs_)
{
	leaf = false;
	index = left_index_;
	n_objs = n_objs_;
}

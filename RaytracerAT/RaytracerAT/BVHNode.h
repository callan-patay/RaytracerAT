#pragma once


#include "BBox.h"

struct BVHChildren
{
	BVHNode leftChild;
	BVHNode rightChild;
};


class BVHNode
{
public:
	BVHNode();
	~BVHNode() = default;
	BBox getBBox() { return bbox; }
	unsigned int getIndex() { return index; }
	unsigned int getNObjs() { return n_objs; }
	bool isLeaf() { return leaf; }
	void setBBox(BBox box);
	void makeLeaf(unsigned int index_, unsigned int n_objs_);
	void makeNode(unsigned int left_index_, unsigned int n_objs_);
	BVHChildren childNodes;
private:
	BBox bbox;
	bool leaf;
	unsigned int n_objs;
	unsigned int index;

};
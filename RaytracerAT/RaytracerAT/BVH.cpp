#include "BVH.h"
#include "ComparePrimitives.h"
#include <iostream>
#include "Surface.h"
BVH::BVH()
{
}

BVH::~BVH()
{
}
//http://fileadmin.cs.lth.se/cs/education/edan30/lectures/s2-bvh.pdf

void BVH::build(std::vector<Surface*>& objs)
{
	rootNode = new BVHNode();
	worldBox = BBox();


	for (auto& obj : objs)
	{
		worldBox.min._y = std::min(obj->getBBox().min._y, worldBox.min._y);
		worldBox.min._x = std::min(obj->getBBox().min._x, worldBox.min._x);
		worldBox.min._z = std::min(obj->getBBox().min._z, worldBox.min._z);

		worldBox.max._y = std::max(obj->getBBox().max._y, worldBox.max._y);
		worldBox.max._x = std::max(obj->getBBox().max._x, worldBox.max._x);
		worldBox.max._z = std::max(obj->getBBox().max._z, worldBox.max._z);


		copies.push_back(obj);

	}




	rootNode->setBBox(worldBox);

	buildRecursive(0, copies.size() -1, rootNode, 0);
}

void BVH::buildRecursive(int leftIndex, int rightIndex, BVHNode * node, int depth)
{
	if ((rightIndex - leftIndex) <= 4 || depth > 100)
	{
		node->makeLeaf(leftIndex, rightIndex);
		std::cout << "Leaf: " << node->getIndex() << " Objects: " << node->getNObjs() << std::endl;
		
	}
	else
	{
		int splitIndex = 0;

		ComparePrimitives cmp;
		cmp.sort_dim = 0;

		std::sort(copies.begin() + leftIndex, copies.begin() + rightIndex, cmp);

		float splitPartition = std::abs(copies[leftIndex]->getCentroid()._x - copies[rightIndex]->getCentroid()._x) / 2;
		splitPartition += copies[leftIndex]->getCentroid()._x;


		BBox leftBox = BBox();
		leftBox.min = Vec3(infinity,infinity,infinity);
		leftBox.max = Vec3(-infinity, -infinity, -infinity);
		BBox rightBox = BBox();
		rightBox.min = Vec3(infinity, infinity, infinity);
		rightBox.max = Vec3(-infinity, -infinity, -infinity);


		for (int i = leftIndex; i < rightIndex; i++)
		{
			if (copies[i]->getCentroid()._x < splitPartition)
			{
				leftBox.min._x =  std::min(leftBox.min._x, copies[i]->getBBox().min._x);
				leftBox.min._y = std::min(leftBox.min._y, copies[i]->getBBox().min._y);
				leftBox.min._z = std::min(leftBox.min._z, copies[i]->getBBox().min._z);
				
				leftBox.max._x = std::max(leftBox.max._x, copies[i]->getBBox().max._x);
				leftBox.max._y = std::max(leftBox.max._y, copies[i]->getBBox().max._y);
				leftBox.max._z = std::max(leftBox.max._z, copies[i]->getBBox().max._z);

				splitIndex++;
			}
			else
			{
				rightBox.min._x = std::min(rightBox.min._x, copies[i]->getBBox().min._x);
				rightBox.min._y = std::min(rightBox.min._y, copies[i]->getBBox().min._y);
				rightBox.min._z = std::min(rightBox.min._z, copies[i]->getBBox().min._z);

				rightBox.max._x = std::max(leftBox.max._x, copies[i]->getBBox().max._x);
				rightBox.max._y = std::max(leftBox.max._y, copies[i]->getBBox().max._y);
				rightBox.max._z = std::max(leftBox.max._z, copies[i]->getBBox().max._z);
			}
		}

		BVHNode * leftNode = new BVHNode();
		leftNode->setBBox(leftBox);
		leftNode->makeNode(leftIndex, splitIndex - leftIndex);
		BVHNode * rightNode = new BVHNode();
		rightNode->setBBox(rightBox);
		rightNode->makeNode(splitIndex, rightIndex - splitIndex);

		node->leftChild = leftNode;
		node->rightChild = rightNode;

		std::cout << "Node: " << node->getIndex() << " Objects: " << node->getNObjs() << std::endl;

		buildRecursive(left_index, splitIndex, leftNode, depth + 1);
		buildRecursive(splitIndex, left_index, rightNode, depth + 1);
	}
}

std::pair<Surface*, float> BVH::intersect(const Ray & ray)
{
	float t = FLT_MAX;
	return intersect(ray, rootNode, t);
}

std::pair<Surface*, float> BVH::intersect(const Ray & ray, BVHNode* currentNode, float &t)
{
	// Intersect ray with this node AABB
	// If intersection:
	//   If leaf: Intersect spheres, and update t
	//   Otherwise try intersecting children intersect(ray, currentNode->leftChild, t)
	Ray localRay = ray;
	//BVHNode* currentNode = rootNode;

	float t_min = t;
	Surface* surface = nullptr;
	bool visible = false;
	


	if (currentNode->getBBox().intersect(ray))
	{
		if (currentNode->isLeaf())
		{
			for (int i = currentNode->getIndex(); i < currentNode->getNObjs() + currentNode->getIndex(); i++)
			{
				std::pair<bool, float> P = copies[i]->Collision(localRay);
				float t = P.second;
				if (P.first && (t < t_min || visible == false))
				{
					t_min = t;
					surface = copies[i];
					visible = true;
				}
			}
		}
		else
		{
			if (currentNode->leftChild->getBBox().intersect(localRay))
			{
				intersect(localRay, currentNode->leftChild, t_min);
			}
			else if(currentNode->rightChild->getBBox().intersect(localRay))
			{
				intersect(localRay, currentNode->rightChild, t_min);
			}
		}
	}


	if (visible)
	{
		return { surface, t_min };
	}

	//for (int i = 0; i < infinity; i++)
	//{
	//	if (!currentNode->isLeaf())
	//	{
	//		if(currentNode->leftChild->getBBox().intersect(ray) && currentNode->rightChild->getBBox().intersect(ray))
	//		{
	//			
	//		}
	//		else if (currentNode->leftChild->getBBox().intersect(ray) || currentNode->rightChild->getBBox().intersect(ray))
	//		{

	//		}
	//		else
	//		{

	//		}
	//	}
	//	else
	//	{

	//	}
	//}

	return { nullptr, -1.0 };

}

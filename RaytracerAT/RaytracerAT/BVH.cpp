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
	if ((rightIndex - leftIndex) <= 4 || depth > 300)
	{
		node->makeLeaf(leftIndex, rightIndex - left_index);
		std::cout << "Leaf: " << node->getIndex() << " Objects: " << node->getNObjs() << std::endl;
		
	}
	else
	{
		int splitIndex = 0;

		ComparePrimitives cmp;


		float splitPartition = 0;
		int biggestAxis = 0;
		for (int i = 0; i < 3; i++)
		{
			cmp.sort_dim = i;

			std::sort(copies.begin() + leftIndex, copies.begin() + rightIndex, cmp);
			
			if (i == 0)
			{
				float splitPartition_x = std::abs(copies[leftIndex]->getCentroid()._x - copies[rightIndex]->getCentroid()._x) / 2;
				splitPartition_x += copies[leftIndex]->getCentroid()._x;
				
				splitPartition = std::max(splitPartition, splitPartition_x);
				if (splitPartition_x > splitPartition)
				{
					biggestAxis = i;
				}
			}
			else if (i == 1)
			{
				float splitPartition_y = std::abs(copies[leftIndex]->getCentroid()._y - copies[rightIndex]->getCentroid()._y) / 2;
				splitPartition_y += copies[leftIndex]->getCentroid()._y;

				splitPartition = std::max(splitPartition, splitPartition_y);
				if (splitPartition_y > splitPartition)
				{
					biggestAxis = i;
				}
			}
			else if (i == 2)
			{
				float splitPartition_z = std::abs(copies[leftIndex]->getCentroid()._z - copies[rightIndex]->getCentroid()._z) / 2;
				splitPartition_z += copies[leftIndex]->getCentroid()._z;

				splitPartition = std::max(splitPartition, splitPartition_z);
				if (splitPartition_z > splitPartition)
				{
					biggestAxis = i;
				}
			}
		}

		cmp.sort_dim = biggestAxis;

		std::sort(copies.begin() + leftIndex, copies.begin() + rightIndex, cmp);

		

		BBox leftBox = BBox();
		leftBox.min = Vec3(infinity,infinity,infinity);
		leftBox.max = Vec3(-infinity, -infinity, -infinity);
		BBox rightBox = BBox();
		rightBox.min = Vec3(infinity, infinity, infinity);
		rightBox.max = Vec3(-infinity, -infinity, -infinity);

		// Find the middle point of the world box
		 // for each object
			// Find side of the biggestAxis the object is on
			// Update the bounding box and a counter for left and right

		// If either counter is 0
			// Reset
			// for half the objects
				// Update left box
			// For the other half
				// Update the right box


		for (int i = leftIndex; i < rightIndex; i++)
		{
			switch (biggestAxis)
			{
			case 0:
				if (copies[i]->getCentroid()._x < splitPartition)
				{
					leftBox.min._x = std::min(leftBox.min._x, copies[i]->getBBox().min._x);
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

					rightBox.max._x = std::max(rightBox.max._x, copies[i]->getBBox().max._x);
					rightBox.max._y = std::max(rightBox.max._y, copies[i]->getBBox().max._y);
					rightBox.max._z = std::max(rightBox.max._z, copies[i]->getBBox().max._z);
				}
				break;
			case 1:
				if (copies[i]->getCentroid()._y < splitPartition)
				{
					leftBox.min._x = std::min(leftBox.min._x, copies[i]->getBBox().min._x);
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

					rightBox.max._x = std::max(rightBox.max._x, copies[i]->getBBox().max._x);
					rightBox.max._y = std::max(rightBox.max._y, copies[i]->getBBox().max._y);
					rightBox.max._z = std::max(rightBox.max._z, copies[i]->getBBox().max._z);
				}
				break;
			case 2:
				if (copies[i]->getCentroid()._z < splitPartition)
				{
					leftBox.min._x = std::min(leftBox.min._x, copies[i]->getBBox().min._x);
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

					rightBox.max._x = std::max(rightBox.max._x, copies[i]->getBBox().max._x);
					rightBox.max._y = std::max(rightBox.max._y, copies[i]->getBBox().max._y);
					rightBox.max._z = std::max(rightBox.max._z, copies[i]->getBBox().max._z);
				}
				break;
			default:
				break;
			}
		//if (copies[i]->getCentroid()._x < splitPartition)
		//{
		//	leftBox.min._x = std::min(leftBox.min._x, copies[i]->getBBox().min._x);
		//	leftBox.min._y = std::min(leftBox.min._y, copies[i]->getBBox().min._y);
		//	leftBox.min._z = std::min(leftBox.min._z, copies[i]->getBBox().min._z);

		//	leftBox.max._x = std::max(leftBox.max._x, copies[i]->getBBox().max._x);
		//	leftBox.max._y = std::max(leftBox.max._y, copies[i]->getBBox().max._y);
		//	leftBox.max._z = std::max(leftBox.max._z, copies[i]->getBBox().max._z);

		//	splitIndex++;
		//}
		//else
		//{
		//	rightBox.min._x = std::min(rightBox.min._x, copies[i]->getBBox().min._x);
		//	rightBox.min._y = std::min(rightBox.min._y, copies[i]->getBBox().min._y);
		//	rightBox.min._z = std::min(rightBox.min._z, copies[i]->getBBox().min._z);

		//	rightBox.max._x = std::max(leftBox.max._x, copies[i]->getBBox().max._x);
		//	rightBox.max._y = std::max(leftBox.max._y, copies[i]->getBBox().max._y);
		//	rightBox.max._z = std::max(leftBox.max._z, copies[i]->getBBox().max._z);
		//}
		}

		if (splitIndex == 0 || splitIndex == rightIndex)
		{
			splitIndex = (rightIndex - leftIndex) / 2;
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
		buildRecursive(splitIndex, right_index, rightNode, depth + 1);
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

				intersect(localRay, currentNode->leftChild, t_min);


				intersect(localRay, currentNode->rightChild, t_min);
			
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

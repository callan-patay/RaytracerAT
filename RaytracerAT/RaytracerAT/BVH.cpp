#include "BVH.h"


struct BVHTraversal {
	int i; // Node
	float mint; // Minimum hit time for this node.
	BVHTraversal() { }
	BVHTraversal(int _i, float _mint) : i(_i), mint(_mint) { }
};

struct BVHBuildEntry {
	// If non-zero then this is the index of the parent. (used in offsets)
	int parent;
	// The range of objects in the object list covered by this node.
	int start, end;
};

void BVH::build()
{
//	BVHBuildEntry todo[128];
//	int stackptr = 0;
//	const int Untouched = 0xffffffff;
//	const int TouchedTwice = 0xfffffffd;
//
//	todo[stackptr].start = 0;
//	todo[stackptr].end = build_prims->size();
//	todo[stackptr].parent = 0xfffffffc;
//	stackptr++;
//
//	BVHFlatNode node;
//	std::vector<BVHFlatNode> buildnodes;
//	buildnodes.reserve(build_prims->size() * 2);
//
//	while (stackptr > 0) {
//		// Pop the next item off of the stack
//		BVHBuildEntry &bnode(todo[--stackptr]);
//		int start = bnode.start;
//		int end = bnode.end;
//		int nPrims = end - start;
//
//		nNodes++;
//		node.start = start;
//		node.nPrims = nPrims;
//		node.rightOffSet = Untouched;
//
//		// Calculate the bounding box for this node
//		/*BBox bb((*build_prims)[start]->getBBox());
//		BBox bc((*build_prims)[start]->getCentroid());
//		for (int p = start + 1; p < end; ++p) {
//			bb.expandToInclude((*build_prims)[p]->getBBox());
//			bc.expandToInclude((*build_prims)[p]->getCentroid());
//		}*/
//		node.bbox = bb;
//
//		// If the number of primitives at this point is less than the leaf
//		// size, then this will become a leaf. (Signified by rightOffset == 0)
//		if (nPrims <= leafSize) {
//			node.rightOffSet = 0;
//			nLeafs++;
//		}
//
//		buildnodes.push_back(node);
//
//		// Child touches parent...
//		// Special case: Don't do this for the root.
//		if (bnode.parent != 0xfffffffc) {
//			buildnodes[bnode.parent].rightOffSet--;
//
//			// When this is the second touch, this is the right child.
//			// The right child sets up the offset for the flat tree.
//			if (buildnodes[bnode.parent].rightOffSet == TouchedTwice) {
//				buildnodes[bnode.parent].rightOffSet = nNodes - 1 - bnode.parent;
//			}
//		}
//
//		// If this is a leaf, no need to subdivide.
//		if (node.rightOffSet == 0)
//			continue;
//
//		// Set the split dimensions
//		int split_dim = bc.maxDimension();
//
//		// Split on the center of the longest axis
//		float split_coord = .5f * (bc.min[split_dim] + bc.max[split_dim]);
//
//		// Partition the list of objects on this split
//		int mid = start;
//		for (int i = start; i<end; ++i) {
//			if ((*build_prims)[i]->getCentroid()[split_dim] < split_coord) {
//				std::swap((*build_prims)[i], (*build_prims)[mid]);
//				++mid;
//			}
//		}
//
//		// If we get a bad split, just choose the center...
//		if (mid == start || mid == end) {
//			mid = start + (end - start) / 2;
//		}
//
//		// Push right child
//		todo[stackptr].start = mid;
//		todo[stackptr].end = end;
//		todo[stackptr].parent = nNodes - 1;
//		stackptr++;
//
//		// Push left child
//		todo[stackptr].start = start;
//		todo[stackptr].end = mid;
//		todo[stackptr].parent = nNodes - 1;
//		stackptr++;
//	}
//
//	// Copy the temp node data to a flat array
//	flatTree = new BVHFlatNode[nNodes];
//	for (int n = 0; n<nNodes; ++n)
//		flatTree[n] = buildnodes[n];
//

}

BVH::BVH(std::vector<Surface*>* surfaces, int leafSize): nNodes(0), nLeafs(0), leafSize(leafSize), build_prims(surfaces), flatTree(NULL)
{
	build();
}


std::pair<Surface*, float> BVH::Intersection(const Ray &ray) const
{
	float t_min = 500;
	Surface* surface = nullptr;
	bool visible = false;

	float bbhits[4];
	int32_t closer, other;

	BVHTraversal todo[64];
	int32_t stackptr = 0;

	todo[stackptr].i = 0;
	todo[stackptr].mint = -500;

	while (stackptr >= 0)
	{
		int ni = todo[stackptr].i;
		float near = todo[stackptr].mint;
		stackptr--;
		const BVHFlatNode &node(flatTree[ni]);

		if (near > t_min)
		{
			continue;
		}


		if (node.rightOffSet == 0)
		{
			for (int o = 0; o < node.nPrims; o++)
			{
				Surface* obj = (*build_prims)[node.start + o];
				std::pair<bool, float> p = obj->Collision(ray);
				bool hit = p.first;

				if (p.first && (p.second < t_min || visible == false))
				{
					t_min = p.second;
					surface = obj;
					visible = true;
				}
				

			}
		}
		else
		{
			bool hitc0 = flatTree[ni + 1].bbox.intersect(ray, bbhits, bbhits + 1);
			bool hitc1 = flatTree[ni + node.rightOffSet].bbox.intersect(ray, bbhits + 2, bbhits + 3);

			if (hitc0 && hitc1) {

				// We assume that the left child is a closer hit...
				closer = ni + 1;
				other = ni + node.rightOffSet;

				// ... If the right child was actually closer, swap the relavent values.
				if (bbhits[2] < bbhits[0]) {
					std::swap(bbhits[0], bbhits[2]);
					std::swap(bbhits[1], bbhits[3]);
					std::swap(closer, other);
				}

				// It's possible that the nearest object is still in the other side, but we'll
				// check the further-awar node later...

				// Push the farther first
				todo[++stackptr] = BVHTraversal(other, bbhits[2]);

				// And now the closer (with overlap test)
				todo[++stackptr] = BVHTraversal(closer, bbhits[0]);
			}

			else if (hitc0) {
				todo[++stackptr] = BVHTraversal(ni + 1, bbhits[0]);
			}

			else if (hitc1) {
				todo[++stackptr] = BVHTraversal(ni + node.rightOffSet, bbhits[2]);
			}
		}
	}

	if (visible)
	{
		return { surface, t_min };
	}


	return { nullptr, -1.0 };
}

BVH::~BVH()
{
	delete[] flatTree;
}

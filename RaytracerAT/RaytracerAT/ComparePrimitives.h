#pragma once
#include "Surface.h"



class ComparePrimitives
{
public:
	bool operator()(Surface* a, Surface *b)
	{
		BBox box;
		float ca;
		float cb;


		if (sort_dim == 0)
		{
			box = a->getBBox();
			ca = (box.max._x + box.min._x) * 0.5f;
			box = b->getBBox();
			cb = (box.max._x + box.min._x) * 0.5f;

		}
		else if (sort_dim == 1)
		{
			box = a->getBBox();
			ca = (box.max._y + box.min._y) * 0.5f;
			box = b->getBBox();
			cb = (box.max._y + box.min._y) * 0.5f;
		}
		else if (sort_dim == 2)
		{
			box = a->getBBox();
			ca = (box.max._z + box.min._z) * 0.5f;
			box = b->getBBox();
			cb = (box.max._z + box.min._z) * 0.5f;
		}
		
		return ca < cb;
	}

	int sort_dim;
};


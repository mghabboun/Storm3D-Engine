#ifndef OCTREE_NODE
#define OCTREE_NODE

#include "Storm3DMath/include/AABB.h"
#include "Storm3DCore/include/OctreeEntry.h"

struct OctreeNode
{
	OctreeNode():childCount(0)
	{
		memset( m_children, NULL, sizeof(m_children) );
	}

	OctreeNode*					m_children[8];
	AxisAlignedBox				m_bounds;
	std::vector<OctreeObject>   m_objects;
	int childCount;
	int index;
	bool IsLeaf(){ return childCount == 0;}
};

#endif
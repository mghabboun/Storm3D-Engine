#ifndef OCTREE_TRAVERSAL
#define OCTREE_TRAVERSAL

#include "Storm3DMath/include/AABB.h"
#include "Storm3DMath/include/Intersections.h"

#include "Storm3DCore/include/OctreeNode.h"

#include "glm/glm.hpp"

// Finds the deepest node that the point is contained in.
inline OctreeNode* PointTraverse( OctreeNode* root, glm::vec3& point )
{	
	auto result = root->m_bounds.Contains( point );
	OctreeNode* r = NULL;
	if ( result )
	{
		for (int i=0; i < 8; ++i)
		{
			OctreeNode* childNode = root->m_children[i];
			if( childNode )
			{
				OctreeNode* r = PointTraverse( childNode, point );
				if ( r )
					break;
			}
		}
	}

	return r;
}

#endif
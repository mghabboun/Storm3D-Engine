#include "Storm3DCore/include/OctreeNode.h"

#include "Storm3DMath/include/AABB.h"
#include "Storm3DMath/include/Intersections.h"

#include "Storm3DCore/include/SubMesh.h"

inline void InsertObject( OctreeNode* root, OctreeObject* object, SubMesh* mesh )
{
	Triangle tri = mesh->GetTriangle(object->triangleIdx);

	bool result = TriBoxOverlap( root->m_bounds.GetCenter(), root->m_bounds.GetHalfSize(), tri.m_V );
	if ( result )
	{
		int count = 0;
		for (int i=0; i < 8; ++i)
		{
			OctreeNode* childNode = root->m_children[i];
			bool childResult = false;
			if( childNode )
			{
				childResult = TriBoxOverlap( childNode->m_bounds.GetCenter(), childNode->m_bounds.GetHalfSize(), tri.m_V );
			}

			root->m_children[i]->m_bounds;

			if (childResult)
			{
				count++;
			}
		}
		std::cout << count << std::endl;
	}

	glm::vec3  center = root->m_bounds.GetCenter();
	root->m_bounds.CalcRadius();
}
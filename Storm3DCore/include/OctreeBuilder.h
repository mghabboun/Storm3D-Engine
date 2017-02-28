#ifndef OCTREE_BUILDER
#define OCTREE_BUILDER

#include "Storm3DCore/include/OctreeNode.h"
#include "Storm3DCore/include/OctreeEntry.h"
#include "Storm3DCore/include/Octree.h"

#include "Storm3DCore/include/OctreeInserter.h"

#include "Storm3DMath/include/AABB.h"
#include "Storm3DMath/include/Intersections.h"


class OctreeBuilder
{
public:
	static OctreeNode* BuildOctree( AxisAlignedBox aabb, int stopDepth)
	{
		if(stopDepth < 0 )
			return NULL;

		AxisAlignedBox boxes[8];		
		aabb.SplitToEight( boxes );	

		OctreeNode* node = new OctreeNode();
		node->m_bounds = aabb;
		//node->halfWidth = aabb.GetMaximum()[0] - aabb.GetMinimum()[0];
		for (int i=0; i<8; ++i)
		{
			node->m_children[i] = BuildOctree( boxes[i], stopDepth-1 );
		}

		return node;
	}

	static Octree* BuildOctreeFromMesh( SubMesh* mesh, AxisAlignedBox aabb, int levels)
	{		
		std::vector<OctreeObject> octreeObjects;
		octreeObjects.reserve( mesh->TringleCount() );
		size_t triCount = mesh->TringleCount();
		for (int i=0; i< triCount; ++i)
		{
			octreeObjects.push_back( OctreeObject() );
			//octreeObjects[i].mesh = mesh;
			octreeObjects[i].triangleIdx = i;
		}

		OctreeNode* root =  BuildOctreeFromMeshImpl( mesh, octreeObjects, aabb, levels, -1);
		auto octree = new Octree(root);
		return octree;
	}

	static OctreeNode* BuildOctreeFromMeshImpl( SubMesh* mesh, std::vector<OctreeObject>& objects,  AxisAlignedBox aabb, int stopDepth, int nodeIdx)
	{		
		if(stopDepth < 0 )
			return NULL;
	
		// Split to 8 cubes
		AxisAlignedBox boxes[8];
		aabb.SplitToEight( boxes );	

		// Create a node and attach the objects
		int childCount = 0;
		OctreeNode* node = new OctreeNode();
		node->m_bounds = aabb;
		//node->halfWidth = ( aabb.GetMaximum()[0] - aabb.GetMinimum()[0] ) *0.5f;
		node->m_objects = /*std::move*/(objects); // Moving it because we know it won't be used again.
		node->index = nodeIdx;
		//
		std::vector<OctreeObject> boxObjects[8];		
		//for each triangle check intersection with 8 boxes
		for (int i=0; i < objects.size(); ++i)
		{
			Triangle tri = mesh->GetTriangle(objects[i].triangleIdx);
			for (int boxId=0; boxId<8; ++boxId)
			{
				glm::vec3 center = boxes[boxId].GetCenter();
				glm::vec3 halfsize = boxes[boxId].GetHalfSize();
				//glm::vec3 vert[3] ={ tri.m_V[0], tri.m_V[1], tri.m_V[2]  };
				int overlaps = TriBoxOverlap( center, halfsize,  tri.m_V  );

				if ( overlaps )
				{
					boxObjects[boxId].push_back( objects[i] );					
				}
			}
		}

		//Loop through boxes and divide them more.
		for (int i=0; i < 8; ++i)
		{
			size_t size = boxObjects[i].size();
			if ( size )
			{
				node->m_children[i] = BuildOctreeFromMeshImpl(mesh, boxObjects[i], boxes[i], stopDepth-1, i );
				if (node->m_children[i])
					node->childCount++;
			}
		}
		return node;
	}
	

	static void InsertMeshIntoTree(OctreeNode* root, SubMesh* mesh)
	{		
		size_t triCount = mesh->m_triangles.size() / 3;
		for (int i=0;i < triCount; i++)
		{
			Triangle triangle =	mesh->GetTriangle( i );
			OctreeObject* object = new OctreeObject;
			//object->radius   = root->m_bounds.CalcRadius();
			//object->m_center = root->m_bounds.GetCenter();
			object->triangleIdx = i;
			//object->mesh = mesh;

			InsertObject( root, object, mesh );
		}
	}

	static void Traverse( OctreeNode* node, glm::vec3 &origin, glm::vec3 &dir )
	{
		float dist;
		glm::vec3 pointer;
		node->m_bounds.RayIntersect( origin, dir, dist, pointer);

		//Detect which child was intersected 

		// Traverse that child
	}

private:
	

};

#endif
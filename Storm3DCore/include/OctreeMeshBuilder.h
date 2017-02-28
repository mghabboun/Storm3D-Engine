#ifndef OCTREE_MESH_BUILDER
#define OCTREE_MESH_BUILDER

#include "Storm3DCore/include/OctreeNode.h"
#include "Storm3DCore/include/Mesh.h"

class OctreeMeshBuilder
{
public:
	//------------------------------------------------------------------
	static void ConvertOctreeToMesh(OctreeNode* root, Mesh* pMesh)
	{
		if( !root )
		   return;		

        if (!pMesh)
            return;       

      SubMesh* mesh = new SubMesh;
      pMesh->AddSubMesh( mesh );
      ConvertOctreeToMeshImpl( root, mesh );
	}

private:
	static void ConvertOctreeToMeshImpl(OctreeNode* root, SubMesh* mesh)
    {       
        AxisAlignedBox box = root->m_bounds;
        auto cubeCorners = box.GetAllCorners();

        //a.insert(a.end(), b.begin(), b.end());
        size_t offset = mesh->m_vertices.size();
        mesh->m_vertices.insert( mesh->m_vertices.end(), cubeCorners.begin(), cubeCorners.end()  );
        //build quads.
        //front 0 1 2 3	
        mesh->AddQuadAsLineStripWithOffset( offset, 0, 1, 2, 3);
        //right 8 5 2 1
        mesh->AddQuadAsLineStripWithOffset( offset, 2, 4, 7, 3 );
        //left  0 3 6 7
        mesh->AddQuadAsLineStripWithOffset( offset,  6, 5, 1, 0);
        //back  7 6 5 8
        mesh->AddQuadAsLineStripWithOffset( offset,  7, 4, 5, 6);
        //top   2 5 6 3
        mesh->AddQuadAsLineStripWithOffset( offset,  4, 2, 1, 5);
        //bot   8 1 0 7
        mesh->AddQuadAsLineStripWithOffset( offset,  7, 6, 0, 3);

        //Add to mesh.
        for (int i=0; i< 8; ++i)
        {
            if( root->m_children[i] )
                ConvertOctreeToMeshImpl(root->m_children[i], mesh );
        }
    }

};
#endif
#ifndef STORM_3D_MESH_MANAGER
#define STORM_3D_MESH_MANAGER

#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/Handle.h"

class MeshManager;

typedef Handle< Mesh, MeshManager> MeshHandle;


class MeshManager
{  

public: 
    
    enum PrimitiveType
    {
        eCube,
        eSphere,
        ePlane,
        eTriangle
    };

	static MeshManager&		GetInstance()
	{
		static MeshManager manager;
		return manager;
	}

    //Mesh*             LoadMesh        (const char* filename, bool calcTangents= false);
	MeshHandle          LoadMesh        ( const char* filename, bool calcTangents= false);
    Mesh*				GetMesh         ( const std::string& name);
    Mesh*				GetMesh         ( int id);    
    Mesh*				CreatePrimitive ( PrimitiveType type);
	MeshHandle			AddResource		( Mesh* pMesh );
	Mesh*	 			GetResource		(int id){ return m_meshes[id]; }

private: 
    void							AddMesh         ( Mesh* pMesh ){ m_meshes.push_back(pMesh); }

    std::vector<Mesh*> m_meshes;
    
};

#endif
#include "Storm3DCore/include/MeshManager.h" 
#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/ObjReader.h"
#include "Storm3DModelConverter/MeshReader.h"


//===================================================
MeshHandle MeshManager::LoadMesh(const char* filename, bool calcTangents )
{
  MeshLoader loader;
  Mesh* mesh = loader.LoadMesh( filename );	
  return AddResource( mesh ); 
}

//===================================================
Mesh* MeshManager::GetMesh(const std::string& name)
{
    return 0;
}

//===================================================
Mesh* MeshManager::GetMesh(int id)
{
    return this->m_meshes[id];
}

//===================================================
MeshHandle		MeshManager::AddResource( Mesh* pMesh )
{
	// Check if it doesn't exist

	// Add resource.
	this->m_meshes.push_back(pMesh);

	// return Handle to the new resource.
	return MeshHandle( this, m_meshes.size()-1 );
}

//===================================================
Mesh* MeshManager::CreatePrimitive(PrimitiveType type)
{
    switch(type)
	{
	case PrimitiveType::eCube: 
		{
			Mesh* m = new Mesh();
			//m->MakeCube(1);
			this->AddResource( m );
			return m;     
		}
	case PrimitiveType::eTriangle:
		{
		Mesh* m = new Mesh();
		//m->MakeTriangle();
		this->AddResource( m );
		return m;
		}
	}

    return 0;
}
#ifndef STORM_3D__MESH
#define STORM_3D__MESH

#include <glm/glm.hpp>

#include "Storm3DMath/include/AABB.h" 
#include "Storm3DMath/include/Triangle.h" 

#include "Storm3DRendering/include/VertexStream.h"
#include "Storm3DRendering/include/DrawAttribs.h"

#include "Component.h"
#include <vector>

class SubMesh;
class Mesh
{
	
public:

    Mesh();	

    void              CalculateTangents();
    AxisAlignedBox    CalculateBounds();
    void              CalculateNormals();
	AxisAlignedBox    GetBounds(){  return m_bounds; }
    size_t            GetDataSizeInBytes();
    void              AddSubMesh(SubMesh* mesh);//{ m_subMeshses.push_back(mesh); }
    int               SubMeshCount(){ return m_subMeshses.size(); }
    SubMesh& operator[](int i){ return *m_subMeshses[i]; }
    SubMesh& GetSubMesh(int i){ return *m_subMeshses[i]; }    
    std::vector<SubMesh*>       m_subMeshses;
    AxisAlignedBox              m_bounds;
    VertexStream                m_stream; // this encapsulates all the data required for correct streaming of this mesh to the gpu.
};



#endif
#include "Storm3DRendering/include/VertexStream.h" 
#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/SubMesh.h"


#include "glew/include/GL/glew.h" 

VertexStream::VertexStream()
{

}

//========================================
void VertexStream::GenerateStream(SubMesh* pMesh)
{
    glGenVertexArrays( 1, &m_vao);
    glBindVertexArray( m_vao );   
    AnalyzeMeshStreamType(pMesh);
}

//========================================
void VertexStream::AnalyzeMeshStreamType(SubMesh* pMesh)
{
    int vertexCount = pMesh->m_vertices.size(); 
    if(vertexCount  > 0)
    {
        m_type = StreamType::V; 
    }
    else return;

    int normalsCount = pMesh->m_normals.size();
    if( vertexCount==normalsCount )
    {
        m_type = StreamType::VN;        
    }

    if(  pMesh->m_UV1.size())
    {
        m_type = StreamType::VNU;
    }
    
    if(pMesh->m_UV2.size())
    {
        m_type = StreamType::VNUU;
    }
   
    if( pMesh->m_tangents.size())
    {
        m_type = StreamType::VNUUT;
    }
}

void VertexStream::BindStream()
{
  glBindVertexArray(m_vao);
}


#include "Storm3DRendering/include/HardwareBuffer.h"
#include "Storm3DRendering/include/DrawAttribs.h"

#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/SubMesh.h"

#include "glew/include/GL/glew.h"

#define CHECK_GL_ERROR() assert(glGetError() == GL_NO_ERROR)
HardwareBuffer::HardwareBuffer(Mesh* m):   	
									m_vao(-1),
									m_drawMode(DrawMode::Triangles),									
									m_mesh(m)
{
    this->GenerateBuffer();
}

//==============================================
//HardwareBuffer::HardwareBuffer():  m_buffId(0), 
//									m_idxBuffId(0),
//									m_vao(0),
//									m_drawMode(DrawMode::Triangles),									
//									m_mesh(nullptr)
//{
//
//}

//==============================================
void CheckGLError()
{
     GLenum error = glGetError();
    if (error != 0 )
    {
        int stop =0;        
    }
}

//==============================================
bool HardwareBuffer::GenerateBuffer()
{   
  int count = m_mesh->SubMeshCount();
  if ( count == 0 )
      return false; 

  m_buffId.resize( count );
  m_idxBuffId.resize(count);
  glGenBuffers(count, &m_buffId[0]); 
  glGenBuffers(count, &m_idxBuffId[0]); 
  //glGenVertexArrays( 1, &m_vao );
  return true;
}

//==============================================
void HardwareBuffer::BindBuffer()
{
    //glBindBuffer( GL_ARRAY_BUFFER, m_buffId );
}

//==============================================
void HardwareBuffer::AttachData()
{   
    if (!m_mesh)
        return; 

    // upload data for each sub mesh
    for ( int i=0; i< m_mesh->SubMeshCount(); ++i )
    {
      //m_stream.GenerateStream( mesh );
      SubMesh& subMesh = (*m_mesh)[i];
      m_stream.GenerateStream(  &subMesh   );
    
      glBindBuffer( GL_ARRAY_BUFFER, m_buffId[i] );

      size_t vertexBufferSize = subMesh.m_vertices.size()*sizeof(glm::vec3); 
      size_t normalBufferSize = subMesh.m_normals.size()*sizeof(glm::vec3); 
      size_t texCoordBufferSize = subMesh.m_UV1.size()*sizeof(glm::vec2); 
      size_t tangentBufferSize = subMesh.m_tangents.size()*sizeof(glm::vec4);
      size_t colorBufferSize = subMesh.m_color.size() * sizeof(glm::vec4);

      glBufferData( GL_ARRAY_BUFFER, vertexBufferSize+normalBufferSize+texCoordBufferSize+tangentBufferSize+colorBufferSize, 0, GL_DYNAMIC_DRAW);      

      //upload vertices
      glBufferSubData( GL_ARRAY_BUFFER, 0 , vertexBufferSize, &(subMesh.m_vertices[0]) );
      //upload normals 
      if(subMesh.m_normals.size())
        glBufferSubData( GL_ARRAY_BUFFER, vertexBufferSize, normalBufferSize, &(subMesh.m_normals[0]) );

      if(subMesh.m_UV1.size())
        glBufferSubData( GL_ARRAY_BUFFER, vertexBufferSize + normalBufferSize, texCoordBufferSize , &(subMesh.m_UV1[0]));

      if(subMesh.m_tangents.size() )
        glBufferSubData( GL_ARRAY_BUFFER, vertexBufferSize + normalBufferSize + texCoordBufferSize, tangentBufferSize, &(subMesh.m_tangents[0]));

      if( subMesh.m_color.size() )
        glBufferSubData( GL_ARRAY_BUFFER, vertexBufferSize + normalBufferSize + texCoordBufferSize + tangentBufferSize, colorBufferSize, &(subMesh.m_color[0]));

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_idxBuffId[i] );
      glBufferData( GL_ELEMENT_ARRAY_BUFFER, subMesh.m_triangles.size()*sizeof(unsigned int), &(subMesh.m_triangles[0]), GL_DYNAMIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

//==============================================
#define BUFFER_OFFSET(i) ((char*)NULL + i)
void HardwareBuffer::DrawBuffer()
{
    for ( int i=0; i< m_mesh->SubMeshCount(); ++i )
    {
      SubMesh& m = (*m_mesh)[i];
      assert ( m_mesh != nullptr );
      size_t vertexBufferSize = m.m_vertices.size()*sizeof(glm::vec3); 
      size_t normalBufferSize = m.m_normals.size()* sizeof(glm::vec3); 
      size_t texCoordBufferSize = m.m_UV1.size()*   sizeof(glm::vec2); 
      size_t tangentBufferSize = m.m_tangents.size() * sizeof(glm::vec4);
      size_t colorBufferSize = m.m_color.size() * sizeof(glm::vec4);
      //m_stream.BindStream();
      //glBindVertexArray(m_vao);
      glBindBuffer(GL_ARRAY_BUFFER, m_buffId[i]);
      CHECK_GL_ERROR();

      glEnableVertexAttribArray(0);
      CHECK_GL_ERROR();

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);   //The starting point of the VBO, for the vertices
      CHECK_GL_ERROR();


      glEnableVertexAttribArray(1);
      CHECK_GL_ERROR();

      glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, BUFFER_OFFSET(vertexBufferSize) );   //The starting point of the VBO, for the normals
      CHECK_GL_ERROR();

      glEnableVertexAttribArray(2);
      CHECK_GL_ERROR();

      glVertexAttribPointer(2, 2, GL_FLOAT, 0, 0, BUFFER_OFFSET(vertexBufferSize+normalBufferSize) );   //The starting point of the VBO, for the vertices
      CHECK_GL_ERROR();

      glEnableVertexAttribArray(4);
      glVertexAttribPointer(4, 4, GL_FLOAT, 0, 0, BUFFER_OFFSET(vertexBufferSize+normalBufferSize+texCoordBufferSize) );   //The starting point of the VBO, for the vertices

      glEnableVertexAttribArray(5);
      glVertexAttribPointer(5, 4, GL_FLOAT, 0, 0, BUFFER_OFFSET(vertexBufferSize+normalBufferSize+texCoordBufferSize+tangentBufferSize) );   //The starting point of the VBO, for the color

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idxBuffId[i]); 
      //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glEnable(GL_PRIMITIVE_RESTART);
      glPrimitiveRestartIndex( ResetPrimitiveIdx );
      glDrawElements( (unsigned int)m_drawMode, m.m_triangles.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));   //The starting point of the IBO    
      CHECK_GL_ERROR();

      glDisable(GL_PRIMITIVE_RESTART);

      glDisableVertexAttribArray(0);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      //glBindVertexArray(0);

    }
   
}

//==============================================
HardwareBuffer::~HardwareBuffer()
{
  glDeleteBuffers( m_buffId.size(), &m_buffId[0]);
}





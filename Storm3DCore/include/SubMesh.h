#ifndef STORM3D_SUB_MESH
#define STORM3D_SUB_MESH

#include <vector>
#include "Storm3DMath/include/AABB.h"
#include "Storm3DMath/include/Triangle.h"

//* Contains the actual mesh data. Group of SubMeshes make a full mesh.

class SubMesh
{
public:
  SubMesh();
  ~SubMesh();

  void              CalculateTangents();
  AxisAlignedBox    CalculateBounds();
  void              CalculateNormals();
  AxisAlignedBox    GetBounds();//{  return m_bounds; }

  void MakeQuad();
  void MakeCube( float size );
  void MakeTriangle();
  void MakePlane( int length, int width );	
  void MakePlaneFromImage( int imagelength, int imagewidth, unsigned char* imageData );

  size_t GetDataSizeInBytes();

  void AddTriangle( unsigned int i0, unsigned int i1, unsigned int i2)
  {
    m_triangles.push_back( i0 );
    m_triangles.push_back( i1 );
    m_triangles.push_back( i2 );
  }

  void AddQuad( unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3)
  {
    m_triangles.push_back( i0 );
    m_triangles.push_back( i1 );
    m_triangles.push_back( i2 );

    m_triangles.push_back( i0 );
    m_triangles.push_back( i2 );
    m_triangles.push_back( i3 );
  }

  void	AddQuadAsLineStrip(unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3)
  {
    m_triangles.push_back( i0 );
    m_triangles.push_back( i1 );
    m_triangles.push_back( i2 );
    m_triangles.push_back( i3 );
    m_triangles.push_back( i0 );
    //primitive restart index
    m_triangles.push_back( 2147483647 ); // ResetPrimitiveIdx
  }

  void AddQuadWithOffset(unsigned int offset, unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3) 
  {
    AddQuad( offset+i0, offset+i1, offset+i2, offset+i3);
  }

  void AddQuadAsLineStripWithOffset(unsigned int offset, unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3) 
  {
    AddQuadAsLineStrip( offset+i0, offset+i1, offset+i2, offset+i3);
  }

  void  AddVertex( float x , float y , float z)
  {
    m_vertices.push_back(glm::vec3(x,y,z));
  }

  void  AddVertex( const glm::vec3& v)
  {
    m_vertices.push_back(v);
  }

  void  AddNormal( float x , float y , float z)
  {
    m_normals.push_back(glm::vec3(x,y,z));
  }

  void  AddVertexWithAttribs( const glm::vec3& v, const glm::vec3& n, const glm::vec2& t )
  {
    m_vertices.push_back(v);
    m_normals.push_back(n);
    m_UV1.push_back(t);
  }

  void AddFace(int i0, int i1, int i2)
  {
    m_triangles.push_back( i0 );
    m_triangles.push_back( i1 ); 
    m_triangles.push_back( i2 ); 
  }

  void AddUV0( float u, float v)
  {
    m_UV1.push_back( glm::vec2(u,v));
  }

  void AddBiTangent( glm::vec3 bitangent )
  {
    m_bitangents.push_back(bitangent);
  }

  Triangle GetTriangle( unsigned int i )
  {
    return Triangle( m_vertices[m_triangles[i*3]], m_vertices[m_triangles[i*3+1]], m_vertices[m_triangles[i*3+2]] );
  }

  void AddLine( unsigned int v0, unsigned int v1)
  {
    m_triangles.push_back( v0 );
    m_triangles.push_back( v1 );
  }

  void AddVertexColor( float r, float g, float b, float a )
  {
    m_color.push_back( glm::vec4(r,g,b,a) );
  }

  size_t TringleCount()const { return m_triangles.size()/3; }


  std::vector<unsigned int>	m_triangles; 
  std::vector<glm::vec3>		m_vertices;
  std::vector<glm::vec3>		m_normals;
  std::vector<glm::vec2>		m_UV1; 
  std::vector<glm::vec2>		m_UV2; 
  std::vector<glm::vec4>		m_tangents;
  std::vector<glm::vec3>		m_bitangents; 
  std::vector<glm::vec4>		m_color;

  AxisAlignedBox                m_bounds;
};


#endif
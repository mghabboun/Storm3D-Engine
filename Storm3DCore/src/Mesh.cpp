#include "Storm3DCore/include/Mesh.h"
#include "Storm3DCore/include/SubMesh.h"

Mesh::Mesh()
{

}

//=======================================
void Mesh::CalculateTangents()
{

}

//=======================================
AxisAlignedBox Mesh::CalculateBounds()
{
  m_bounds = AxisAlignedBox();
  for (int i=0; i < m_subMeshses.size(); ++i)
  {
      if ( m_subMeshses[i]->TringleCount() > 0 )
        m_bounds.Union( m_subMeshses[i]->CalculateBounds() );
  }

   return m_bounds;
}

//=======================================
void Mesh::CalculateNormals()
{
  for (int i=0; i < m_subMeshses.size(); ++i)
  {
    m_subMeshses[i]->CalculateNormals();
  }
}

//=======================================
void Mesh::AddSubMesh(SubMesh* mesh)
{
    m_subMeshses.push_back(mesh); 
    this->CalculateBounds();
}

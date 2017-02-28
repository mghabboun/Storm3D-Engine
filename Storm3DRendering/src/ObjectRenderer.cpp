#include "Storm3DRendering/include/ObjectRenderer.h"
#include "Storm3DCore/include/Mesh.h" 
#include "Storm3DRendering/include/ObjectRenderer.h" 
#include "Storm3DRendering/include/Renderer.h" 
#include "Storm3DCore/include/MaterialManager.h" 
#include "Storm3DCore/include/Node.h"

#include "glew/include/GL/glew.h"


//ObjectRenderer::ObjectRenderer():m_owner(0), m_buffer(), m_pMaterial(0),m_mode(GL_FILL)
//{
//     //m_pMaterial = MaterialManager::GetInstance().GetMaterialByName("Diffuse");
//    m_isInit = false;
//}

//==================================================
ObjectRenderer::ObjectRenderer(Material* mat, Node* owner,  MeshHandle mesh ):m_owner(owner),  m_pMesh(mesh), m_buffer(mesh.Get()), m_pMaterial(mat),m_mode(GL_FILL)
{
    m_isInit = false;
	m_buffer.AttachData();
}

//==================================================
//void ObjectRenderer::SetMesh(Mesh* mesh)
//{    
//    assert(mesh != NULL);
//	m_pMesh.Get() = mesh;
//    
//	m_buffer.AttachData(m_pMesh.Get() );
//}

//==================================================
void ObjectRenderer::SetMaterial(Material* pMat)
{
    m_pMaterial = pMat;
}

//==================================================
void ObjectRenderer::SetFillMode( GLenum renderMode )
{
	m_mode = renderMode;
}

//==================================================
void ObjectRenderer::Render(const FPSCamera& activeCamera, const glm::mat4& transform)
{    
    assert ( m_pMaterial != nullptr && "Material is NULL" );
    m_pMaterial->ApplyMaterial( activeCamera, transform );

	//assert ( m_pMesh != nullptr && "Mesh is NULL");
	if ( m_pMesh.IsValid() )
	{
		//glPolygonMode( GL_FRONT_AND_BACK, (GLenum)m_mode );
		m_buffer.DrawBuffer();
		//glPolygonMode( GL_FRONT_AND_BACK, GL_POLYGON );
	}
	
}

//==================================================
void ObjectRenderer::SetOwner( Node* owner )
{
    m_owner = owner;
}

//==================================================
const glm::mat4& ObjectRenderer::GetChachedTransform()
{
    assert ( m_owner != nullptr && "Renderer not attached to a Node");
    return m_owner->GetFullTransform();
}

//==================================================
AxisAlignedBox ObjectRenderer::GetBounds()
{
	return m_pMesh->m_bounds;
}

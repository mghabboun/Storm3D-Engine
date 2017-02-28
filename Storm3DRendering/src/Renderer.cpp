#include "Storm3DRendering/include/Renderer.h"
#include "glew/include/GL/glew.h" 

#include "Storm3DCore/include/FPSCamera.h"
#include "Storm3DCore/include/Node.h"

Renderer::Renderer():m_pActiveCamera(nullptr)/*,m_device(1920, 1080)*/
{
   //
    EnableDepthBuffer();
	//m_shadowFrameBuffer = CreateFrameBufferObject();
	int stop =0;
}

//============================================
Renderer& Renderer::GetInstance()
{
    static Renderer renderer; 
    return renderer;
}

//============================================
void Renderer::SetActiveCamera(FPSCamera* pCam)
{
    m_pActiveCamera = pCam;
}

//============================================
FPSCamera* Renderer::GetActiveCamera()
{
    return m_pActiveCamera;
}

void Renderer::RenderShadowPass()
{
	if ( m_shadowFrameBuffer )
	m_shadowFrameBuffer->BindFrameBuffer();
	ClearBuffer();
	RenderVisibleSet();
	if ( m_shadowFrameBuffer )
	m_shadowFrameBuffer->UnBindFrameBuffer();
}

//============================================
void Renderer::Render()
{
	RenderShadowPass();
	RenderVisibleSet();
    //ObjectRenderer* objRenderer = 
	//Render Shadow pass
}

//============================================
void Renderer::RenderVisibleSet()
{  
	for(int i=0; i < m_renderers.size(); ++i)
    {
        m_renderers[i]->Render( *m_pActiveCamera, m_renderers[i]->GetChachedTransform() );
    }
}

//============================================
void Renderer::SetClearColor( float r, float g, float b)
{
     glClearColor ( r, g, b, 1.0 );
}

//============================================
void Renderer::ClearBuffer()
{
    glClearColor(0,0,0,0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//============================================
void Renderer::EnableDepthBuffer()
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::DisableDepthBuffer()
{
    glDisable(GL_DEPTH_TEST);
}

//============================================
ObjectRenderer* Renderer::CreateObjectRenderer( Material *mat, Node* node, MeshHandle mesh)
{
    ObjectRenderer* objRenderer = new ObjectRenderer( mat, node, mesh);
    this->AddObjectRenderer(objRenderer);
	node->AttachObjectRenderer(objRenderer);
    return objRenderer;
}

//============================================
//ObjectRenderer* Renderer::CreateObjectRenderer( Material *mat )
//{
//    ObjectRenderer* objRenderer = new ObjectRenderer( mat);
//    this->AddObjectRenderer(objRenderer);
//    return objRenderer; 
//}

//============================================
void Renderer::AddObjectRenderer(ObjectRenderer* pObjRenderer)
{
    m_renderers.push_back( pObjRenderer);
}


FrameBufferObject* Renderer::CreateFrameBufferObject()
{
    FrameBufferObject* fbo = new FrameBufferObject;
    m_frameBuffers.push_back(fbo);
    return fbo;
}
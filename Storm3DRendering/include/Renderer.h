#ifndef APP_WORLD_RENDERER
#define APP_WORLD_RENDERER

#include "Storm3DCore/include/Geometry.h"
#include "Storm3DRendering/include/ObjectRenderer.h" 
#include "Storm3DRendering/include/RenderDevice.h"

#include "Storm3DCore/include/Camera.h"

#include <vector> 
#include <queue>
#include <list> 

class FrameBufferObject;
class FPSCamera;
class Renderer 
{ 

public:
    
    static Renderer&					GetInstance();
    
    void								SetActiveCamera(FPSCamera* pCam); 
    FPSCamera*							GetActiveCamera();
    //ObjectRenderer* CreateObjectRenderer();
    ObjectRenderer*						CreateObjectRenderer( Material *mat, Node* node, MeshHandle mesh= MeshHandle() );
	void								RenderVisibleSet();

    //ObjectRenderer* CreateObjectRenderer(Material *mat );
	void								RenderShadowPass();
    void								Render();

    //void ParseMat

    /* Clear our buffer with a red background */
    void								SetClearColor( float r, float g, float b);
    void								ClearBuffer();
    void								EnableDepthBuffer();
    void								DisableDepthBuffer();
    void								AddObjectRenderer( ObjectRenderer* pObjRenderer );
    FrameBufferObject*					CreateFrameBufferObject();
   
private:
    FPSCamera*							m_pActiveCamera;
	FrameBufferObject*					m_shadowFrameBuffer;
    std::queue<ObjectRenderer*>			m_visibleSet; 
    std::vector< FrameBufferObject* >	m_frameBuffers; 
    std::vector< ObjectRenderer* >		m_renderers;
	//RenderDevice						m_device;

	Renderer();

};

#endif 
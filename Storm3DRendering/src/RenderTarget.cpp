#include "Storm3DRendering/include/RenderTarget.h"

#include "glew/include/GL/glew.h"

//=======================================================
RenderTarget::RenderTarget(): m_id(0),
							  m_isAttached(false)

{

}

//=======================================================
void RenderTarget::GenRenderTarget()
{
    glGenRenderbuffers( 1, &m_id);
}

//=======================================================
//void RenderTarget::AttachToFrameBuffer( FrameBufferObject* fb)
//{
//    // glFramebufferRenderbuffer( );
//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboName);
//    
//    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
//        GL_RENDERBUFFER, depthBufferName);
//    
//    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//        GL_RENDERBUFFER, renderBufferNames[0]);
//    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
//        GL_RENDERBUFFER, renderBufferNames[1]);
//    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
//        GL_RENDERBUFFER, renderBufferNames[2]);
//}

void RenderTarget::BindRenderTarget()
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_id);

    //glBindRenderbuffer(GL_RENDERBUFFER, m_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, m_width, m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

  //  glBindRenderbuffer(GL_RENDERBUFFER, depthBufferName);
  //  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, screenWidth, screenHeight);
}



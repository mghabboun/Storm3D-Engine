#ifndef STORM3D_OPENGL_RENDER_DEVICE
#define STORM3D_OPENGL_RENDER_DEVICE

#include <memory> 

#include "Storm3DRendering/include/FrameBufferObject.h"
#include "Storm3DCore/include/FullScreenQuad.h"


class RenderDevice
{
public:
  RenderDevice( int width, int height );
  ~RenderDevice();

  void Enable();
private:

  FrameBufferObject	m_frameBuffer;
  FullScreenQuad	m_quad;

};
#endif

#include "Storm3DRendering/include/RenderDevice.h"

RenderDevice::RenderDevice( int width, int height)
{
	//m_frameBuffer.GenerateFrameBuffer( width, height );
}

  
void RenderDevice::Enable(){
   m_quad.DrawFullScreenQuad();
}


RenderDevice::~RenderDevice()
{

}
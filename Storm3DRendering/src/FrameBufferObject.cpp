#include "Storm3DRendering/include/FrameBufferObject.h"

#include "Storm3DRendering/include/OpenGL.h"

#include <stdio.h>


FrameBufferObject::FrameBufferObject():m_id(0),
	depthBufferName(0),
	renderBufferName(0),
	fboName(0),
	m_texName(0)
{
	GenerateFrameBuffer( 800, 600 );        
}

FrameBufferObject::~FrameBufferObject()
{

}

unsigned int FrameBufferObject::GenTexture(unsigned int width, unsigned int height)
{
	glGenTextures( 1, &m_texName );
	glBindTexture(GL_TEXTURE_2D, m_texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameterf(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width,	height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,	nullptr); 
	glBindTexture(GL_TEXTURE_2D, 0);
	//return m_texName;

	return m_texName;
}


void FrameBufferObject::GenerateFrameBuffer( unsigned int width, unsigned int height)
{
	unsigned int texName = GenTexture( width, height );		

	glGenFramebuffers(1, &fboName);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboName);		

	/*glGenRenderbuffers(	1, &renderBufferName	);
	glBindRenderbuffer(	GL_RENDERBUFFER, renderBufferName);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);*/

	//// Attach all  renderbuffers to FBO
	//glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBufferName );
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_texName, 0);

	GLenum e1 = glGetError( );
	GLenum e  = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	switch (e) 
	{	
	case GL_FRAMEBUFFER_UNDEFINED:
		printf("FBO Undefined\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT :
		printf("FBO Incomplete Attachment\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT :
		printf("FBO Missing Attachment\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
		printf("FBO Incomplete Draw Buffer\n");
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED :
		printf("FBO Unsupported\n");
		break;
	case GL_FRAMEBUFFER_COMPLETE:
		printf("FBO OK\n");
		break;
	default:
		printf("FBO Problem?\n");
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	// check if everything is OK	
}


void FrameBufferObject::BindFrameBuffer()
{	
	glBindFramebuffer( GL_FRAMEBUFFER, fboName );
	/*glBindTexture(GL_TEXTURE_2D, m_texName);
	glBindRenderbuffer(	GL_RENDERBUFFER, renderBufferName);*/
	//glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texName, 0);
	glDrawBuffer( GL_NONE );
	//glReadBuffer( GL_NONE );
}

void FrameBufferObject::UnBindFrameBuffer()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void FrameBufferObject::AttachRenderTarget()
{

}



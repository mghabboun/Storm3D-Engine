#include "Storm3DRendering/include/Texture.h" 

#include "glew/include/GL/glew.h" 

Texture::Texture(unsigned int handle)
{
    m_id = handle;
}

//==================================
void Texture::ActivateTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_id );
}

//==================================


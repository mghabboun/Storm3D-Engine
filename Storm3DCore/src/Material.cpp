#include "Storm3DCore/include/Material.h"
#include "Storm3DCore/include/Camera.h" 
#include "Storm3DRendering/include/Texture.h"
#include "Storm3DCore/include/FPSCamera.h"

#include "Storm3DRendering/include/OpenGL.h"


#include <glm/glm.hpp>

//========================================
Material::Material(const std::string& name):m_baseColor(nullptr)
{
    m_name = name;
}

//========================================
void Material::InitializeMaterial()
{

}

//========================================
void Material::ApplyMaterial(const FPSCamera& cam, const glm::mat4& transform)
{  
	glm::mat4 modelView = cam.GetViewMatrix() * transform;
    m_shaders[0]->SetModelViewMatrix( modelView );

	m_shaders[0]->SetNormalMatrix( ( glm::mat3(glm::transpose( glm::inverse( modelView ) )) ) );	

	m_shaders[0]->ActivateShader();
    m_shaders[0]->UpdateProgram();
    ApplyTextures();
}

//========================================
void Material::AddPass(Shader* pShader)
{
    m_shaders.push_back(pShader);
}

void Material::RemovePassByIndex(unsigned int i)
{

}

//=======================================
void Material::RemovePassByName()
{

}

//=======================================
void Material::AddTexture(Texture* pTexture) 
{
    m_textures.push_back( pTexture );
}

//=======================================
void Material::ApplyTextures()
{
    for (int i=0; i < m_textures.size(); ++i)
    {
        glActiveTexture( GL_TEXTURE0 + i);
        m_textures[i]->ActivateTexture();
    }
}

//=======================================
void Material::LinkMaterial()
{
}

//=======================================
Shader* Material::GetShaderByName( const std::string &name )
{
    for (int i=0; i < m_shaders.size(); ++i)
    {
        if ( name.compare( m_shaders[i]->GetName() )  == 0)
        {
            return m_shaders[i];
        }
    }

    return nullptr;
}

//=======================================
Shader* Material::GetShaderByIndex( size_t i )
{
	if ( i < m_shaders.size() )
		return m_shaders[i];

	return nullptr;
}

void Material::SetDiffuseColor(float r, float g, float b)
{
    m_diffuseColor.r = r;
    m_diffuseColor.g = g;
    m_diffuseColor.b = b;    
}

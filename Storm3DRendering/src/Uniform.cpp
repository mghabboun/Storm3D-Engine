#include "Storm3DRendering/include/Uniform.h" 
#include "Storm3DRendering/include/Shader.h" 


#include "glew/include/GL/glew.h" 

const std::string& Uniform::GetName()
{
    return m_name;
}

//===================================================================================
 Uniform::Uniform( Shader* sh, const std::string& name, int location)
 {
     m_name = name;
     AddOwner(sh, location);
 }

//===================================================================================
Uniform::Uniform( const std::string& name )
{
     m_name = name;
}

//===================================================================================
void Uniform::AddOwner(Shader* pShader, unsigned int location)
{
    m_owner.push_back( pShader );
    m_loc.push_back( location  );
    pShader->AddUniform( this  );

}

//===================================================================================
void Uniform::NotifyOwners()
{
    for(int i=0; i< m_owner.size(); ++i)
    {
        m_owner[i]->NotifyDirty(this, m_loc[i] );
    }
}


//===================================================================================
UniformType Uniform::GetType()
{
    return m_type;
}

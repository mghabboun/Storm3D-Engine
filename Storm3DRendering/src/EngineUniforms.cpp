#include "Storm3DRendering/include/UniformTypes.h"
#include "Storm3DRendering/include/EngineUniforms.h"
#include "Storm3DRendering/include/UniformFactory.h"

//Uniform* EngineUniforms::m_viewMatrix; 
//Uniform* EngineUniforms::m_normalMatrix;
//
//Uniform* EngineUniforms::m_projectionMatrix;

//===========================================================
EngineUniforms& EngineUniforms::GetInstance()
{
    static EngineUniforms engineUniform;
    return engineUniform;
}

//===========================================================
void EngineUniforms::InitializeUniforms()
{
    if (!m_init)
    {
        m_viewMatrix        = (UniformMat4*)RegisterEngineUniform("viewMatrix"	, UniformType::FLOAT_MAT4);
        m_normalMatrix      = (UniformMat3*)RegisterEngineUniform("normalMatrix", UniformType::FLOAT_MAT3);
        m_projectionMatrix  = (UniformMat4*)RegisterEngineUniform("projMatrix"	, UniformType::FLOAT_MAT4);
		m_lightDir			= (UniformVec4*)RegisterEngineUniform("lightDir"	, UniformType::FLOAT_VEC4);
        m_lightPos			= (UniformVec3*)RegisterEngineUniform("lightPos"	, UniformType::FLOAT_VEC3);
		m_lightColor		= (UniformVec4*)RegisterEngineUniform("lightColor"	, UniformType::FLOAT_VEC4);

        m_init= true; 
    }
}

//===========================================================
Uniform* EngineUniforms::RegisterEngineUniform(const std::string& name, UniformType type)
{
    Uniform* pUniform = GetEngineUniformByName( name );
    if( pUniform )
    {
        return pUniform;
    }

    return CreateEngineUniform( name, type ); 
}

//===========================================================
bool EngineUniforms::CheckIfEngineUniform(const std::string& name)
{
    for (unsigned int i=0; i < m_engineUniforms.size(); ++i)
    {
        if (name.compare( m_engineUniforms[i]->GetName() ))
        {
            return true;
        }
    }
    return false; 
}

//===========================================================
Uniform* EngineUniforms::GetEngineUniformByName(const std::string& name)
{
    for(unsigned int i=0; i< m_engineUniforms.size(); ++i)
    {
        if ( m_engineUniforms[i]->GetName() == name )
        {
            return m_engineUniforms[i];
        }
    }
    return NULL;
}

//===========================================================
Uniform* EngineUniforms::CreateEngineUniform(const std::string& name, UniformType type)
{
    Uniform* pUniform = EngineUniforms::CreateUniform(type, name );
    m_engineUniforms.push_back( pUniform );
    return pUniform; 
}


//===================================================================================
Uniform* EngineUniforms::CreateUniform(UniformType type, const std::string& name)
{
    switch (type)
    {
    case UniformType::FLOAT_: 
        return new UniformFloat(name);

    case UniformType::FLOAT_VEC3: 
        return new UniformVec3(name); 

    case UniformType::FLOAT_VEC4: 
        return new UniformVec4(name);

    case  UniformType::FLOAT_MAT4:
        return new UniformMat4(name);

    case  UniformType::FLOAT_MAT3:
        return new UniformMat3(name);
    }

    return NULL;
}

//===================================================================================
Uniform* EngineUniforms::CreateUniform(UniformType type, const std::string& name, Shader* owner, unsigned int location)
{
    switch (type)
    {
    case UniformType::FLOAT_: 
        return new UniformFloat( owner, name, location ); 

    case UniformType::FLOAT_VEC3: 
        return new UniformVec3( owner, name, location ); 

    case UniformType::FLOAT_VEC4: 
        return new UniformVec4( owner, name, location );

    case  UniformType::FLOAT_MAT4:
        return new UniformMat4(owner, name, location);

    case  UniformType::FLOAT_MAT3:
        return new UniformMat3(owner, name, location);

    case  UniformType::SAMPLER_1D:
    case  UniformType::SAMPLER_1D_SHADOW:
    case  UniformType::SAMPLER_2D:
    case  UniformType::SAMPLER_2D_SHADOW:
    case  UniformType::SAMPLER_3D:

        return new UniformSampler(owner, name, location); 

    }

    return NULL;
}



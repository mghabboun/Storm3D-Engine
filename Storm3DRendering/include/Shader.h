#ifndef APP_WORLD_SHADER
#define APP_WORLD_SHADER

#include "Storm3DCore/include/Storm3DTypes.h"
#include "Storm3DRendering/include/UniformTypes.h"

#include <glm/glm.hpp>

#include <map> 
#include <queue> 

class Uniform;
class Shader
{

private:
    bool        InitFragmentShader (const char* fragmentSource);
    bool        InitVertexShader(const char* vertSource);
    void        LoadShaderSrcToShaderObject(const char *szShaderSrc, unsigned int shader);    

    // void AddOwner(Shader* pShader);
    void            UpdateUniform( Uniform* uniform, unsigned int loc);

public: 
    static bool     LoadShaderSourceFile(const char *file, std::string& outSrc);
                    Shader(const std::string& name);
                    const std::string& GetName();

    bool            InitShaderFromSource(const char* vertSource, const char* fragmentSource);
    void            ActivateShader();
    void            InitializeShaderAttributes();
    void            ExtractShaderUniforms();
    void            AddUniform( Uniform* uniform);
    Uniform*        CreateUniform(int location, const std::string& name, UniformType t);
    Uniform*        GetUniformByName(const std::string& name);
    void            NotifyDirty(Uniform* uniform, unsigned int locationRelativeToShader);
    void            UpdateProgram();
    void            InitTextureUnits();    
    //bool            SetUniformValueByName( const std::string& uniformName, const float * value, int count  );
	
	template < typename UniformT >
	UniformT*		GetUniformByName(const std::string& name);

	
    void            SetModelViewMatrix(const glm::mat4& modelview );
	void			SetNormalMatrix(const glm::mat3& normalMat );

private:
    unsigned int	m_fragShaderId; 
    unsigned int	m_vertShaderId; 
    unsigned int	m_programId;

private:

    std::map<std::string, Uniform*> m_uniforms;
    //should only be set at initialization time.
    std::vector<Uniform*> m_uniformSamplers; 

    typedef std::pair< Uniform*, unsigned int> UniformLocPair; 
    std::queue<UniformLocPair>              m_dirtyUniforms;
    std::string m_name;


};

//===========================================================
template< typename UniformT >
UniformT* Shader::GetUniformByName(const std::string& name)
{	
    std::map<std::string, Uniform*>::iterator it =  m_uniforms.find( name );
    if ( it != m_uniforms.end() )
    {
		Uniform* uniform = (*it).second;
		if ( UniformT::Type == uniform->GetType() )
			return static_cast<UniformT*>(uniform);
    }

    return NULL;
}

#endif

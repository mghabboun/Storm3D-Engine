#include "Storm3DRendering/include/Shader.h" 
#include "Storm3DCore/include/Storm3DTypes.h"
#include "Storm3DRendering/include/UniformTypes.h"

#include "glew/include/GL/glew.h" 

//
#include "Storm3DRendering/include/Renderer.h"
#include "Storm3DRendering/include/EngineUniforms.h" 
#include "Storm3DRendering/include/UniformFactory.h"
#include <glm/ext.hpp>
#include <assert.h> 
#include <fstream> 

Shader::Shader(const std::string& name)
{
    m_name = name;
}

//===========================================================
const std::string& Shader::GetName()
{
    return m_name;
}

//===========================================================
bool Shader::InitFragmentShader (const char* fragmentSource)
{
    // Create shader objects
    m_fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    // Fragment Program
    if( fragmentSource == "")
    {
        glDeleteShader(m_fragShaderId);
        return false;
    }

    LoadShaderSrcToShaderObject( fragmentSource, m_fragShaderId);

    glCompileShader( m_fragShaderId );
    int compiled =0; 
    glGetObjectParameterivARB(m_fragShaderId, GL_OBJECT_COMPILE_STATUS_ARB, &compiled );
    if( compiled == GL_FALSE ) 
    {
        int  logLength;
        printf( "fragment shader compilation failed.\n" ); 
        glGetObjectParameterivARB( m_fragShaderId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength ); 
        char* log = new char [logLength]; 
        glGetInfoLogARB( m_fragShaderId, logLength, NULL, log ); 
        printf( "\n%s\n", log ); 
        delete [] log;

		__debugbreak();
        return false; 
    }

    glAttachShader( m_programId, m_fragShaderId);
	printf("fragment shader compilation successful\n");
    return (bool)compiled;
}

//===========================================================
bool Shader::InitVertexShader(const char* vertSource)
{
    // Create shader objects
    m_vertShaderId = glCreateShader(GL_VERTEX_SHADER); 
    // Fragment Program
    if( vertSource == "")
    {
        glDeleteShader(m_vertShaderId);
        return false; 
    }

    LoadShaderSrcToShaderObject( vertSource, m_vertShaderId);

    glCompileShader(m_vertShaderId);
    int compiled =0; 
    glGetObjectParameterivARB(m_vertShaderId, GL_OBJECT_COMPILE_STATUS_ARB, &compiled );
    if( compiled == GL_FALSE ) 
    {        
        int  logLength;
        printf( "Vertex shader compilation failed.\n" ); 
        glGetObjectParameterivARB( m_vertShaderId, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength ); 
        char* log = new char [logLength]; 
        glGetInfoLogARB( m_vertShaderId, logLength, NULL, log ); 
        printf( "\n%s\n", log ); 
        delete[] log;
		__debugbreak();
        return false;
    }

    glAttachShader( m_programId, m_vertShaderId);
	printf("vertex shader compilation successful\n");
    return (bool)compiled;
}

//===========================================================
void Shader::LoadShaderSrcToShaderObject(const char *szShaderSrc, unsigned int shader)
{
    GLchar *fsStringPtr[1];
    fsStringPtr[0] = (GLchar *)szShaderSrc;
    glShaderSource(shader, 1, (const GLchar **)fsStringPtr, NULL);
}

//===========================================================
#define MAX_SHADER_LENGTH 8000
bool Shader::LoadShaderSourceFile(const char *file, std::string& outSrc )
{
    char shaderText[MAX_SHADER_LENGTH];
    GLint shaderLength = 0;
    FILE *fp;

    // Open the shader file
    fp = fopen(file, "r");
    if(fp != NULL)
    {
        // See how long the file is
        while (fgetc(fp) != EOF)
            shaderLength++;

        // Allocate a block of memory to send in the shader
        assert(shaderLength < MAX_SHADER_LENGTH);   // make me bigger!
        if(shaderLength > MAX_SHADER_LENGTH)
        {
            fclose(fp);
            return false;
        }

        // Go back to beginning of file
        rewind(fp);

        // Read the whole file in
        if (shaderText != NULL)
            fread(shaderText, 1, shaderLength, fp);

        // Make sure it is null terminated and close the file
        shaderText[shaderLength] = '\0';
        fclose(fp);
    }
    else
        return false;    

    outSrc.assign(shaderText);
    return true;
}   

enum AttributeLoc
{
	ATT_POSITION	=0,
	ATT_NORMAL		=1,
	ATT_TEXCOORD1	=2,
	ATT_TEXCOORD2	=3,
	ATT_TANGET		=4,
	ATT_COLOR		=5
};

//===========================================================
void Shader::InitializeShaderAttributes()
{
    glBindAttribLocation( m_programId, 0, "Position" );
    glBindAttribLocation( m_programId, 1, "Normal"   );
    glBindAttribLocation( m_programId, 2, "TexCoord1");
    glBindAttribLocation( m_programId, 3, "TexCoord2");
    glBindAttribLocation( m_programId, 4, "Tangent"  );
    glBindAttribLocation( m_programId, 5, "Color"  );

    GLenum e = glGetError();
	if (e)
		int stop=0;
}

//===========================================================
void Shader::ActivateShader()
{
    glUseProgram( m_programId );
}

//===========================================================
Uniform* Shader::CreateUniform(int location, const std::string& name, UniformType  type)
{
	Uniform* pUniform = EngineUniforms::CreateUniform( type, name, this, location);
    AddUniform( pUniform );
    return pUniform; 
}

//===========================================================
void Shader::AddUniform( Uniform* uniform )
{
    if(uniform == 0)
        return;
    UniformType type = uniform->GetType();
    if ( type == UniformType::SAMPLER_2D || type == UniformType::SAMPLER_1D || type == UniformType::SAMPLER_CUBE)
        m_uniformSamplers.push_back( uniform ); 
    else 
        m_uniforms[uniform->GetName()] = uniform;
}

//===========================================================
void Shader::ExtractShaderUniforms()
{
    EngineUniforms& engineUniform = EngineUniforms::GetInstance();

    int count; 
    glGetProgramiv( m_programId, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &count);

    for (int i=0; i<count; ++i)
    {
        char name[40];
        GLint size = 40;
        GLenum type; 
        GLsizei length;
        GLsizei bufSize=40;
        glGetActiveUniform( m_programId, i, bufSize, &length, &size, &type, name );
        int location = glGetUniformLocation( m_programId, name);

        Uniform* pEngineUniform = engineUniform.GetEngineUniformByName( name );
        if ( pEngineUniform != 0) // if is engine uniform then link with it.
        {
            pEngineUniform->AddOwner( this, location );
        }
        else
        {    
            UniformType type1 = (UniformType)type;
            Uniform* uniform = CreateUniform( location, name,type1 );
        }
    }
}

//===========================================================
Uniform* Shader::GetUniformByName(const std::string& name)
{
    std::map<std::string, Uniform*>::iterator it =  m_uniforms.find( name );
    if ( it != m_uniforms.end() )
    {
        return (*it).second;
    }

    return NULL;
}

//===========================================================
//bool Shader::SetUniformValueByName(const std::string& uniformName, const float * value, int count  )
//{
//    std::map<std::string, Uniform*>::iterator it =  m_uniforms.find( uniformName );
//    if ( it != m_uniforms.end() )
//    {
//       Uniform* uni = it->second;
//       uni->SetValue( value, count );
//    }
//    
//    return false;
//}

//======================================================================
void printProgramInfoLog(GLuint obj, const char* shaderName)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s:\n", shaderName);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}

//======================================================================
void Shader::InitTextureUnits()
{
    for (int i=0; i< m_uniformSamplers.size(); ++i) 
    {
        UniformSampler* sampler = static_cast<UniformSampler*>( m_uniformSamplers[i] );
		sampler->SetValue( &i );
    }
}

//======================================================================
bool Shader::InitShaderFromSource( const char* vertSource, const char* fragmentSource )
{
    m_programId = glCreateProgram();

    bool vResult = InitVertexShader(vertSource);
    bool fResult = InitFragmentShader( fragmentSource );

    if ( vResult && fResult )
    {
        InitializeShaderAttributes();
        glBindFragDataLocation(m_programId, 0, "outputF");
        glLinkProgram(m_programId);

		printProgramInfoLog( m_programId, this->GetName().c_str() );

        ExtractShaderUniforms();
        InitTextureUnits();
    }
    return (vResult && fResult);
}

//======================================================================
void Shader::NotifyDirty(Uniform* uniform, unsigned int locationRelativeToShader)
{
    m_dirtyUniforms.push( UniformLocPair(uniform, locationRelativeToShader) );
}

//======================================================================
void Shader::UpdateProgram()
{   
    while( !m_dirtyUniforms.empty() )
    {
        UniformLocPair& top= m_dirtyUniforms.front();
        Uniform* currUniform = top.first;
        unsigned int loc = top.second;
        
        UpdateUniform( currUniform, loc);

        m_dirtyUniforms.pop();
    }
}

//======================================================================
void Shader::UpdateUniform( Uniform* uniform, unsigned int loc)
{
	UniformType type = uniform->GetType();
    switch( type  )
    {
    case UniformType::FLOAT_: 
        {
            UniformFloat* unformFloat = static_cast<UniformFloat*>(uniform);
            glUniform1f( loc, *(unformFloat->GetValue()) );
            break;
        }
    case UniformType::FLOAT_MAT4:
        {
			UniformMat4* unformMat = static_cast<UniformMat4*>(uniform);
			float v[16] ;
			memcpy( v, unformMat->GetValue(), 16 * sizeof(float));			
            glUniformMatrix4fv( loc, 1, false, v );
			GLenum e1 = glGetError();
            break;
        }
	 case UniformType::FLOAT_MAT3: 
        {
            UniformMat3* unformMat = static_cast<UniformMat3*>(uniform);
			glm::mat3 m;
            glUniformMatrix3fv( loc, 1, false, unformMat->GetValue() );
			GLenum e1 = glGetError();
            break;
        }


    case UniformType::FLOAT_VEC3: 
        {
            UniformVec3* unformVec = static_cast<UniformVec3*>( uniform );
            glUniform3f( loc, unformVec->GetValue()[0], unformVec->GetValue()[1], unformVec ->GetValue()[2]);
			GLenum e1 = glGetError();
            break;
        }

    case UniformType::FLOAT_VEC4: 
        {
            UniformVec4* unformVec = static_cast<UniformVec4*>( uniform );
            glUniform4f( loc, unformVec->GetValue()[0], unformVec->GetValue()[1], unformVec ->GetValue()[2], unformVec->GetValue()[3]);
			GLenum e1 = glGetError();
            break;
        }

    case UniformType::SAMPLER_1D:
    case UniformType::SAMPLER_1D_SHADOW:
    case UniformType::SAMPLER_2D:
    case UniformType::SAMPLER_2D_SHADOW:
        {
            UniformSampler* uniformSampler = static_cast<UniformSampler*>( uniform );
            glUniform1i( loc, *(uniformSampler->GetValue()) );
            break;
        }
    }
}

//======================================================================
void Shader::SetModelViewMatrix(const glm::mat4& modelview )
{	
    Uniform* uniformModelView = GetUniformByName("viewMatrix");
	assert ( uniformModelView != NULL && "viewMatrix is Null check your shader");
	static_cast<UniformMat4*>(uniformModelView)->SetValue( const_cast<float*>(glm::value_ptr(modelview)) );
}

//======================================================================
void Shader::SetNormalMatrix(const glm::mat3& normalMat )
{	
    Uniform* uniformNormalMatrix = GetUniformByName("normalMatrix");
	//assert ( uniformNormalMatrix != NULL && "normal is Null check your shader");
	if ( uniformNormalMatrix )
		static_cast<UniformMat3*>(uniformNormalMatrix)->SetValue( const_cast<float*>(glm::value_ptr(normalMat)) );

	//normalMatrix
}




#include "Storm3DCore/include/ShaderManager.h"
#include "Storm3DCore/include/XMLParser.h"

#include "Storm3DRendering/include/Shader.h"
#include <string> 

//=======================================================
Shader* ShaderManager::CreateShaderFromSource( const char* name, const char* vertSrc, const char* fragSrc )
{
    Shader* shader = new Shader( name );
	shader->InitShaderFromSource( vertSrc, fragSrc);
    this->AddShader( shader );
    return shader;
}

//=======================================================
void ShaderManager::AddShader( Shader* pShader )
{
	std::map<std::string, Shader*>::iterator shaderIt; 
	shaderIt = m_shaders.find( pShader->GetName() );
	if( shaderIt == m_shaders.end() )
	{
		m_shaders[pShader->GetName()] = pShader;
	}
}

//=======================================================
void ShaderManager::InitDefaulShaders()
{
    //m_isInit = true;    
    //Material* pMat = CreateMaterial( "Simple", "Engine\\Shaders\\simple.vert", "Engine\\Shaders\\simple.frag");
    //pMat->LinkMaterial(); 

    //pMat = CreateMaterial( "Diffuse", "Engine\\Shaders\\diffuse.vert", "Engine\\Shaders\\diffuse.frag");
    //pMat->LinkMaterial(); 

    //pMat = CreateMaterial( "DiffuseBump", "Engine\\Shaders\\diffuseBump.vert", "Engine\\Shaders\\diffuseBump.frag");
    //pMat->LinkMaterial();
}


//=======================================================
Shader* ShaderManager::GetShaderByName(const std::string& name)
{
     std::map<std::string, Shader*>::iterator shaderIt; 
     shaderIt = m_shaders.find( name );
     if(shaderIt != m_shaders.end())
         return (*shaderIt).second;

     return NULL;
}

//=======================================================
Shader*	ShaderManager::LoadShaderFromSource( const char* file )
{
	XMLParser parser;
	if ( !parser.LoadFile( file ) )
	{
		return NULL;
	}

	std::string vertexShader;
	std::string fragShader;

	std::string name;
	std::string value;
	parser.ReadRootTag( "Shader", "name", value, name);

	//Check if shader already loaded ? 
	// TODO: Check on filename
	Shader* shader = this->GetShaderByName( name );
	if (  shader )
		return shader;

	parser.ReadTagText("VertexShader", vertexShader );
	parser.ReadTagText("FragmentShader", fragShader );

	if ( vertexShader.size() && fragShader.size() )
	{
		return CreateShaderFromSource( name.c_str(), vertexShader.c_str(), fragShader.c_str()  );
	}

	return nullptr;
}

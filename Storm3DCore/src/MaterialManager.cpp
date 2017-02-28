#include "Storm3DCore/include/MaterialManager.h" 
#include "Storm3DCore/include/MaterialParser.h"
#include "Storm3DCore/include/ShaderManager.h"
#include "Storm3DCore/include/TextureManager.h"

//=======================================================
MaterialManager::MaterialManager():m_isInit(false)
{
    if ( !m_isInit)
    {      
        InitDefaultMaterials();
        m_isInit = true;
    }
}

//=======================================================
MaterialManager& MaterialManager::GetInstance()
{
    static MaterialManager manager;
    return manager;
}
  
//=======================================================
Material* MaterialManager::GetMaterialByName (const std::string& name)
{
    MaterialsMap::iterator it= m_materials.find(name);
    if (it != m_materials.end())
    {
        return (*it).second;
    }

    return NULL;
}



//=======================================================
Material* MaterialManager::CreateMaterial(const std::string& name)
{
    Material* pMat = new Material(name);
    AddMaterial(pMat);
    return pMat; 
}

//=======================================================
Material* MaterialManager::CreateMaterial(const std::string& name, const char* vertShaderFile, const char* fragShaderFile )
{
    std::string vertShader, fragShader;
    Shader::LoadShaderSourceFile( vertShaderFile, vertShader );
    Shader::LoadShaderSourceFile( fragShaderFile, fragShader );      
    //Shader* shader = CreateShader(name);   
    //shader->InitShaderFromSource( vertShader.c_str(), fragShader.c_str() );
  
    Material* pMat = new Material(name);
    //pMat->AddPass( shader );
    
    AddMaterial(pMat);
    return pMat;
}

//=======================================================
void MaterialManager::AddMaterial(Material* pMat)
{
    if(!pMat)
        return; 

    m_materials[pMat->GetName()]= pMat;    
}

//=======================================================
void MaterialManager::InitDefaultMaterials()
{
     //TODO read from file.
}

//=======================================================
//Material* MaterialManager::CreateDiffuseMaterial()
//{
//    return nullptr;
//}

//=======================================================
Material*   MaterialManager::LoadMaterial  ( const char* filename )
{
	//TODO work on Error checking.
    MaterialParser parser;
    if ( !parser.LoadFile( filename ) )
		return NULL;
	
    std::string value;
    std::string att;
	parser.ReadMaterialName();
    parser.ReadShaderTags();

	parser.ReadSamplerTags();
	//
	Material* mat = MaterialManager::CreateMaterial( parser.GetMaterialName() );

	for (int i=0; i < parser.GetTexturesList().size(); ++i )
	{
		auto& textureName = parser.GetTexturesList()[i];
        TextureHandle texture =	TextureManager::GetInstance().LoadTextureFromFile( textureName );
		
        // revert to default texture
		if ( !texture.IsValid() )
        {
          //texture = TextureManager::GetInstance().GetDefaultTexture();
          texture =	TextureManager::GetInstance().LoadTextureFromFile( "E:/projects/assets/Engine/Textures/default.jpg" );
        }
        mat->AddTexture( texture.Get() );
	}

	auto shaderList = parser.GetShaderList();
	for (int i=0; i < parser.GetShaderList().size(); ++i )
	{
		const char* shaderName = shaderList[i].c_str();
		Shader* pShader = ShaderManager::GetInstance().LoadShaderFromSource( shaderName );
		assert( pShader != NULL && "shader Not found" );
		
		if ( pShader )
			mat->AddPass( pShader );
	}

    return mat;
}
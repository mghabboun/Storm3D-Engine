#include "Storm3DCore/include/MaterialParser.h"
#include "Storm3DCore/include/ShaderManager.h"

#include <string>

//--------------------------------------
bool MaterialParser::LoadFile( const char* filename )
{
    return m_parser.LoadFile( filename );
}

//--------------------------------------
void MaterialParser::ReadShaderTags()
{
    std::string value;
    std::string attribute;
    m_parser.ReadTag( "Shader", "source", value, m_shadersList );	
}

//--------------------------------------
void MaterialParser::ReadSamplerTags()
{
    std::string value;
    std::string attribute;
    m_parser.ReadTag( "Sampler", "source", value, m_texturesList );	
}

//--------------------------------------
void MaterialParser::ReadMaterialName()
{
	std::string val;
	m_parser.ReadRootTag("Material", "name", val, m_name);
}

//--------------------------------------
void MaterialParser::BuildMaterial()
{

}


#ifndef STORM_3D_MATERIAL_PARSER
#define STORM_3D_MATERIAL_PARSER

#include "Storm3DCore/include/XMLParser.h"

#include <tinyxml2/tinyxml2.h>
#include <string> 
#include <vector>

class MaterialParser
{
public:
    
    MaterialParser(){}
    ~MaterialParser(){}

    bool LoadFile( const char* filename );
  
    void ReadShaderTags();
    void ReadSamplerTags();
	std::string GetMaterialName(){ return m_name;}
    void BuildMaterial();

	std::vector<std::string>& GetShaderList(){ return m_shadersList; }
	std::vector<std::string>& GetTexturesList(){ return m_texturesList; }
	void ReadMaterialName();


private:

	XMLParser m_parser;

    std::vector <std::string> m_shadersList;
	std::vector<std::string>  m_texturesList;
	std::string m_name;
};

#endif
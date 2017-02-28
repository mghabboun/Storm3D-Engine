#ifndef APP_WORLD__OBJ_READER
#define APP_WORLD__OBJ_READER

#include <deque>
#include <sstream> 
#include "Storm3DCore/include/Mesh.h" 
#include <glm/glm.hpp>

#include <fstream>

class SubMesh;

class ObjReader
{

public:

	Mesh*	ParseFile( const char* strFileName );
   
    void	ParseMtlLib(const std::string& strFileName);
    bool	ProcessLine(std::istream& is);

private:
	void	SkipLine(std::istream& is);
	bool	SkipCommentLine(std::istream& is);

    void    CreateMesh(SubMesh* pMesh);
    
	//static map<string, >	m_materialMap;
    std::vector<glm::vec3> vertexList;
    std::vector<glm::vec3> normalList;
    std::vector<glm::vec2> texCoordList;

    std::vector<unsigned int> indexList;
    std::vector<unsigned int> texIndexList;
    std::vector<unsigned int> normalIndexList;

};



#endif 

#include "Storm3DCore/include/ObjReader.h" 
#include "Storm3DCore/include/Mesh.h" 
#include "Storm3DCore/include/SubMesh.h" 

#include <fstream> 

// static member
//path ObjReader::m_branchPath;
//map<string, SMaterial> ObjReader::m_materialMap;

//=========================================================
void ObjReader::SkipLine(std::istream& is)
{
    char next;
    is >> std::noskipws;
    while( (is >> next) && ('\n' != next) );
}

//=========================================================
bool ObjReader::SkipCommentLine(std::istream& is)
{
    char next;
    while( is >> std::skipws >> next ) 
    {
        is.putback(next);
        if ('#' == next)
            SkipLine(is);
        else
            return true;
    }
    return false;
}


//=========================================================
void ObjReader::ParseMtlLib(const std::string& strFileName)
{
    //	render the ".mtl" file path application relative (instead of ".obj" file relative)
    //path filePath = m_branchPath/strFileName;
    //CMtlParser::parse(m_materialMap, filePath.string());
}

//=========================================================
Mesh* ObjReader::ParseFile( const char* strFileName )
{
    //	usefull to retrieve material files
    //m_branchPath = filePath.branch_path();

    std::ifstream ifs( strFileName, std::ios::in| std::ios::ate);
    if ( !ifs.is_open() )
        return nullptr;

    const int fileSize = ifs.tellg();    //  get the file size (we started at the end)...
    ifs.seekg (0, std::ios::beg);  //  ...then get back to start

   
    // and go.
    int percent = 10;	//	progress indicator
    while(SkipCommentLine(ifs)) 
    {
        // show progress for files larger than one Mo
        if ((fileSize > 1024*1024) && (100*ifs.tellg()/fileSize >= percent)) 
        {			
            percent = 100*ifs.tellg()/fileSize;
            percent = (percent/10)*10;
            percent += 10;
        }

        if (false == ProcessLine( ifs))
            break;       
    }

    //Fix Mesh
    SubMesh* subMesh = new SubMesh();
    CreateMesh(subMesh);
    
    Mesh* mesh = new Mesh();
    mesh->AddSubMesh( subMesh );
    return mesh;
}

#include <algorithm>
#include <iterator>
#include <string.h>
int CheckFaceCount( std::istream& is)
{
	std::vector<std::string> tokens;
	std::copy(	std::istream_iterator<std::string>(is), 
				std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(tokens)
				);

	return tokens.size();
}


//=========================================================
bool ObjReader::ProcessLine( std::istream& is)
{     
    std::string ele_id;
    float x, y, z;    

    if ( !(is >> ele_id) )
        return false;

    if ("mtllib" == ele_id) 
    {
        std::string strFileName;
        is >> strFileName;
        ParseMtlLib(strFileName);
    }
    else if ("usemtl" == ele_id) 
    {
        /*    std::string strMtlName;
        is >> strMtlName;
        std::map<string, SMaterial>::iterator it = m_materialMap.find(strMtlName);
        if (it != m_materialMap.end())
        pMesh->setMaterial((*it).second);
        else
        CLogger::get() << "  * Material not found in current mtllib :\"" << strMtlName << "\". Ignoring material.\n";
        */}
    else if ("v" == ele_id) 
    {	
        //	vertex data
        is >> x >> y >> z;
		glm::vec3 vert(x, y, z);
        vertexList.push_back(vert);



    }
    else if ("vt" == ele_id) 
    {	// texture data
        is >> x >> y >> z;
        is.clear();                           // is z (i.e. w) is not available, have to clear error flag.
        texCoordList.push_back(glm::vec2(x, y));
    }
    else if ("vn" == ele_id) 
    {	// normal data
        is >> x >> y >> z;
        if(!is.good()) 
        {                     // in case it is -1#IND00
            x = y = z = 0.0;
            is.clear();
            SkipLine(is);
        }
        normalList.push_back(glm::vec3(x, y, z) );
    }
    else if ("f" == ele_id) 
    {

		//CheckFaceCount( is );
        //int vi[10];                               // vertex indices.
        //int ni[10] = { -1, -1, -1, -1, };         // normal indices.
        //int ti[10] = { -1, -1, -1, -1, };         // tex indices.
        int i = 0;
        for (char c; i<3; ++i) 
        {
            unsigned int vi;
            unsigned int ti;
            unsigned int ni;

            if( !texCoordList.size() && ! normalList.size() )
            {                
                is >> vi;
                indexList.push_back( vi-1 );
            }
            else if(!texCoordList.size())
            {
                is >> vi >> c >> c >> ni;
                indexList.push_back( vi-1 );
                normalIndexList.push_back(ni-1);
            }
            else if(!normalList.size())
            {
                is >> vi >> c >> ti;
                indexList.push_back( vi-1 );
                texIndexList.push_back( ti-1 );                
            }
            else
            {
                is >> vi >> c >> ti >> c >>  ni;

                indexList.push_back( vi-1 );
                normalIndexList.push_back(ni-1);
                texIndexList.push_back( ti-1 );
            }

            if(!is.good())
                break;
        }

        is.clear();
    }
    else
        SkipLine(is);
    return true;
}


//=========================================================
void ObjReader::CreateMesh(SubMesh* pMesh)
{
    if (pMesh == 0) 
        return; 

	glm::vec3 max( -999999.9f, -999999.9f, -999999.9f);
	glm::vec3 min( 999999.9f, 999999.9f, 999999.9f);

    unsigned int indexCount = indexList.size();
    pMesh->m_vertices.reserve( indexCount );
    pMesh->m_normals.reserve( normalIndexList.size() );

    for (int i=0; i < indexList.size(); ++i )
    {   
		glm::vec3& vertex =  vertexList[ indexList[i] ];

		if ( vertex.x > max.x )
			max.x = vertex.x;
		if ( vertex.y > max.y )
			max.y = vertex.y;
		if ( vertex.z > max.z )
			max.z = vertex.z;		
		
		if ( vertex.x < min.x )
			min.x = vertex.x;
		if ( vertex.y < min.y )
			min.y = vertex.y;
		if ( vertex.z < min.z )
			min.z = vertex.z;
        
		pMesh->m_vertices.push_back( vertex );
        pMesh->m_triangles.push_back(i);
        
        if (normalList.size() > 0 )
        {
            pMesh->m_normals.push_back( normalList[normalIndexList[i]] );
        }
        if (texCoordList.size() > 0 )
        {              
            pMesh->m_UV1.push_back( texCoordList[texIndexList[i]] );
        }
    }

	pMesh->m_bounds.SetMaximum( max );
	pMesh->m_bounds.SetMinimum( min );

}


#include "Storm3DCore/include/ResourceManager.h" 

#include <filesystem>

using namespace Storm3D;

//=========================================================
void ResourceManager::InitSearchPath()
{

}

//=========================================================
void ResourceManager::AddSearchPath(const std::string& p)
{
	namespace filesystem = std::tr2::sys;
	filesystem::path path1(p);
	if ( path1.is_complete() )
	{
		path1 = filesystem ::complete(path1);
	}

	if ( filesystem::is_directory( path1 ) )
	{
		m_searchPaths.push_back( path1 );
	}
	
}


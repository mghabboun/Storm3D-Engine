#ifndef STORM_3D_RESOURCE_MANAGER
#define STORM_3D_RESOURCE_MANAGER

#include <vector>
#include <string> 

namespace Storm3D
{

class ResourceManager
{

public: 
    
   
    void AddSearchPath(const std::string& path);

private:
	 void InitSearchPath(); 

    std::string m_engineRoot;
    std::vector<std::string> m_searchPaths;  


};


}


#endif 
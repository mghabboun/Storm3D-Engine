#ifndef APP_WORLD_MATERIAL_MANAGER
#define APP_WORLD_MATERIAL_MANAGER

#include "Storm3DCore/include/Material.h"
#include "Storm3DRendering/include/Shader.h"

#include <vector> 
#include <map> 
#include <string>

//#include "Storm3DCore/include/Handle.h"

//class MaterialManager;

//typedef Handle< Material, MaterialManager> MaterialHandle;

class MaterialManager
{
    // Internal Declarations
    typedef std::map<std::string, Shader*>      ShadersMap; 
    typedef std::map<std::string, Material*>    MaterialsMap;

public:

    static MaterialManager&                     GetInstance();    
    Material*                                   GetMaterialByName ( const std::string& name);

    Material*                                   CreateMaterial( const std::string& name);
    Material*                                   CreateMaterial( const std::string& name, const char* vertShaderFile, const char* fragShaderFile );
    Material*                                   LoadMaterial  ( const char* filename );
    void                                        AddMaterial   ( Material* pMat);

  
    void                                        InitDefaultMaterials();


private: 
                                                MaterialManager();

    bool                                        m_isInit;
    ShadersMap                                  m_shaders;
    MaterialsMap                                m_materials;

};


#endif 
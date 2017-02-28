#ifndef APP_WORLD_ENGINE
#define APP_WORLD_ENGINE

#include "Storm3DCore/include/SceneManager.h"
#include "Storm3DRendering/include/Renderer.h"


class Engine
{

public: 

    Engine():m_isInit(false)
	{
	
	}

   // const Engine& Instance();

    void StartEngine();
    void EndEngine();

    Renderer& GetRenderer();
	//PhysicsManager& Physics(){ return *m_physics; }
    SceneManager* CreateScene( const std::string& name );
	//PhysicsManager* m_physics;
    std::vector<SceneManager*> m_scenes; 

private:

    bool m_isInit;
    
};


#endif 
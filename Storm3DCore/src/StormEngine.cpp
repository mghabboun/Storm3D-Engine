#include "Storm3DCore/include/StormEngine.h" 
#include "Storm3DCore/include/MaterialManager.h" 
#include "Storm3DCore/include/TextureManager.h"
#include "Storm3DRendering/include/EngineUniforms.h" 

//---------------------------------------
void Engine::StartEngine()
{
    m_isInit = true;
    TextureManager::GetInstance();
    EngineUniforms::GetInstance().InitializeUniforms();
    Renderer::GetInstance();
    MaterialManager::GetInstance();
}

//---------------------------------------
void Engine::EndEngine()
{

}


//---------------------------------------
Renderer& Engine::GetRenderer()
{
    return Renderer::GetInstance();
}

//---------------------------------------
SceneManager* Engine::CreateScene(const std::string& name)
{
    SceneManager* scene = new SceneManager; 
    m_scenes.push_back(scene);
    return scene; 
}
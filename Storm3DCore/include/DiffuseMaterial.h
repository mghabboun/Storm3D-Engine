#ifndef STORM_3D_MATERIAL
#define STORM_3D_MATERIAL

#include "Storm3DRendering/include/Shader.h" 

#include <glm/glm.hpp>
#include <vector> 

class Texture;
class Camera;
class FPSCamera;
class Uniform;
class Material
{

public:

                            Material(const std::string& name);
    virtual                 ~Material(){}
    const std::string&      GetName(){ return m_name;}

    //void ApplyMaterial(Camera* cam); //material should not have dependency on camera, should be done in other way
    //void ApplyMaterial(const Matrix4& transform);
    void                    ApplyMaterial(const FPSCamera& cam, const glm::mat4& transform);

    void                    AddPass(Shader* pShader);
    Shader*                 GetShaderByName( const std::string &name );
	Shader*					GetShaderByIndex( size_t i );

    void                    RemovePassByIndex(unsigned int i);
    void                    RemovePassByName();
    void                    AddTexture(Texture* pTexture); 
    void                    ApplyTextures();
    virtual void            LinkMaterial();
    void                    SetDiffuseColor(float r, float g, float b);
    void                    SetSpecColor(float r, float g, float b);
    void                    InitializeMaterial();

private: 

    Uniform*        m_diffuseColor;
    glm::vec3       m_diffuseColorVal; 
    glm::vec3       m_SpecColor;

    std::vector<Texture*>   m_textures;
    std::vector<Shader*>    m_shaders;
    //Shader* m_shader;
    std::string m_name;

};


#endif 
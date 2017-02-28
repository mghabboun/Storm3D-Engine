#ifndef APP_WORLD_BUUFERS
#define APP_WORLD_BUUFERS

#include "Storm3DCore/include/Storm3DTypes.h"
 
#include <vector>
#include <string> 


class Shader;
class Uniform 
{

public:
    
    Uniform( Shader* sh, const std::string& name, int location);
    Uniform( const std::string& name);
    
    const std::string& GetName();
    UniformType GetType();

    void AddOwner(Shader* pShader, unsigned int location);
    //void SetValue(const float* value, int elementCount);	

protected:
    void NotifyOwners();

private: 
    std::vector<Shader*> m_owner;
    std::vector<unsigned int> m_loc; // I am saving the uniform location, I shouldn'y need to be fixed.

    std::string m_name;

protected:
    UniformType m_type;

};


#endif 



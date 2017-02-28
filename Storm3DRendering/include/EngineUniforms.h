#ifndef APP_WORLD_ENGINE_UNIFORM
#define APP_WORLD_ENGINE_UNIFORM

//#include "Uniform.h" 
#include "Storm3DCore/include/Storm3DTypes.h"

#include "Storm3DRendering/include/UniformTypes.h"

#include <vector> 

class Uniform;
class Shader;
class EngineUniforms
{

public:

	static Uniform* CreateUniform(UniformType type, const std::string& name);
	static Uniform* CreateUniform(UniformType type, const std::string& name, Shader* owner, unsigned int location);


	~EngineUniforms(){}

	void InitializeUniforms();
	Uniform* RegisterEngineUniform(const std::string& name, UniformType type);

	static EngineUniforms& GetInstance();


	Uniform* GetEngineUniformByName(const std::string& name);
	bool CheckIfEngineUniform(const std::string& name);	

	UniformMat4* m_viewMatrix;
	UniformMat4* m_projectionMatrix;
	UniformMat3* m_normalMatrix;
	UniformVec4* m_lightDir;
	UniformVec3* m_lightPos;
	UniformVec4* m_lightColor;

private:

	Uniform* CreateEngineUniform(const std::string& name, UniformType);

	std::vector<Uniform*> m_engineUniforms; 
	bool m_init;
	//==============================================
	EngineUniforms():	m_viewMatrix(nullptr),
						m_projectionMatrix(nullptr),
						m_normalMatrix(nullptr),
						m_lightDir(nullptr),
						m_lightPos(nullptr),
						m_lightColor(nullptr)
	{
		m_init= false;
	}

	EngineUniforms(const EngineUniforms&);

};

#endif 
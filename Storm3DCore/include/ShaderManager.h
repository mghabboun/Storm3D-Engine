#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include <map>

class Shader;
class ShaderManager
{

public:

	static ShaderManager& GetInstance()
	{
		static ShaderManager instance;
		return instance;
	}

	//Shader*		CreateShaderFromSource(const char* vertFile, const char* fragFile);
	Shader*			CreateShaderFromSource(const char* name, const char* vertSrc, const char* fragSrc);

    void		AddShader(Shader* pShader);
    void		InitDefaulShaders();
	Shader*		LoadShaderFromSource( const char* file );

	Shader*		GetShaderByName     ( const std::string&  name );

private:
	
	ShaderManager(){}

	std::map<std::string, Shader*>	m_shaders;
};

#endif
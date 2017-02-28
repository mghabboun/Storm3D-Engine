#ifndef STORM_3D_POINT_LIGHT
#define STORM_3D_POINT_LIGHT

#include "Storm3DRendering/include/EngineUniforms.h" 
#include <glm/glm.hpp>
#include <iostream>

class PointLight
{
public: 

    PointLight();
    void Init();
    void SetLightPosition( const glm::vec3& pos );
	glm::vec3 GetLightPosition()
	{
		std::cout << m_pos.x <<" " << m_pos.y << " "<< m_pos.z << std::endl;
		return m_pos;
	}

	void Update( const glm::mat4& viewMatrix);
	void _UpdateImpl();
	void MoveLight( float x, float y, float z)
	{
		SetLightPosition( GetLightPosition() + glm::vec3(x,y,z)); //To be refactored
	}

private:
    UniformVec3* m_lightPosition;
	UniformMat4* m_lightMatrix;	

	glm::vec3 m_pos;
	bool	m_castShadows;
};


#endif 
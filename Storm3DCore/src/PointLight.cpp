#include "Storm3DCore/include/PointLight.h" 
#include "Storm3DRendering/include/EngineUniforms.h" 
#include "Storm3DRendering/include/UniformTypes.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>


PointLight::PointLight():	m_pos(0,0,0),
							m_lightPosition(nullptr),
							m_lightMatrix(nullptr), 
							m_castShadows(false)

{
    Init();
}
#include <iostream>
//------------------------------------------------------
void PointLight::Init()
{
    m_lightPosition = (UniformVec3*)EngineUniforms::GetInstance().RegisterEngineUniform("lightPos", FLOAT_VEC3 );
	m_lightMatrix = (UniformMat4*)EngineUniforms::GetInstance().RegisterEngineUniform("lightMatrix", FLOAT_MAT4 );
 //   m_lightProjMatrix = EngineUniforms::GetInstance().RegisterEngineUniform("lightPos", FLOAT_MAT4 );
}

//------------------------------------------------------
void PointLight::SetLightPosition( const glm::vec3& pos )
{    
	m_pos = pos;
}

void PointLight::Update( const glm::mat4& viewMatrix)
{
	UniformVec3* light = static_cast<UniformVec3*>(m_lightPosition);
	glm::vec3 transformedLight = glm::vec3(viewMatrix * glm::vec4(m_pos, 1.0f) );
	light->SetValue( glm::value_ptr( transformedLight ) );
	
	// Calculate light matrix.	
	/*glm::mat4 lightViewMatrix = glm::lookAt( m_pos, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f ) );
	glm::mat4 projMatrix = glm::frustum( -10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 100.0f);
	
	float mat[16] = {	0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.5f, 0.0f,
						0.5f, 0.5f, 0.5f, 1.0f};

	glm::mat4 biasMatrix = glm::make_mat4( mat );
	glm::mat4 finalMatrix = biasMatrix * projMatrix * lightViewMatrix;

	m_lightMatrix->SetValue( glm::value_ptr(finalMatrix) );*/
}

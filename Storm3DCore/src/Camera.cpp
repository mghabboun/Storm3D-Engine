#include "Storm3DCore/include/Camera.h" 

#include "Storm3DRendering/include/EngineUniforms.h"

#include <glm/ext.hpp>

#include <cassert>
//==================================
Camera::Camera():m_forward( 0.0f,0.0f,-1.0f)
{
	//m_forward = glm::normalize(m_viewTarget - m_position);

}

//==================================
Camera::~Camera()
{

}

//==================================
void Camera::LookAt( glm::vec3& position, glm::vec3& target)
{
    m_position = position;
    m_ViewMat = glm::lookAt( position, target, glm::vec3(0.0f, 1.0f, 0.0f ) );
    int len = m_ViewMat.length();

    EngineUniforms::GetInstance().m_viewMatrix->SetValue( glm::value_ptr( m_ViewMat ) );

	glm::mat3 normalMat =  glm::mat3( ( m_ViewMat ));
	//glm::mat3 normalMat =  glm::mat3( glm::transpose( glm::inverse(m_ViewMat) ));
	int count = normalMat.length();
	//EngineUniforms::GetInstance().m_normalMatrix->SetValue(  glm::value_ptr(normalMat) );

}

//#include <iostream>
//==================================
void Camera::RotateY(  float degree )
{    
	printf("%f\n", degree );
	m_viewTarget -= m_position;
    m_viewTarget = glm::rotateY( m_viewTarget, degree );    
	m_viewTarget += m_position;

	m_forward = glm::normalize(m_viewTarget - m_position);
    m_ViewMat = glm::lookAt( m_position, m_viewTarget, glm::vec3(0.0f, 1.0f, 0.0f ) );
    //EngineUniforms::GetInstance().m_viewMatrix->SetValue( glm::value_ptr(m_ViewMat), m_ViewMat.length()  );
}

//==================================
void Camera::RotateX(  float degree )
{	
   	m_viewTarget -= m_position;
    m_viewTarget = glm::rotateX( m_viewTarget, degree );    
	m_viewTarget += m_position;

	m_forward = glm::normalize(m_viewTarget - m_position);
	m_ViewMat = glm::lookAt( m_position, m_viewTarget, glm::vec3(0.0f, 1.0f, 0.0f ) );
    //EngineUniforms::GetInstance().m_viewMatrix->SetValue( glm::value_ptr(m_ViewMat), m_ViewMat.length()  );
}


//==================================
void Camera::Frustum( float left, float right, float bottom, float top, float near, float far )
{ 
    m_ProjectionMat = glm::frustum(left, right, bottom, top, near, far );
   
    EngineUniforms::GetInstance().m_projectionMatrix->SetValue( glm::value_ptr(m_ProjectionMat) );
}

//==================================
void Camera::Perspective( float fov, float ratio, float near, float far)
{
    m_ProjectionMat = glm::perspective( fov, ratio, near, far );
    EngineUniforms::GetInstance().m_projectionMatrix->SetValue( glm::value_ptr( m_ProjectionMat) );
}

//==================================
void Camera::Update ( float deltaTime )
{
   //EngineUniforms::GetInstance().m_projectionMatrix->SetValue( glm::value_ptr(m_ProjectionMat), 16 );
}

//==================================
void Camera::UpdateImpl (float deltaTime)
{
       //m_ProjectionMat = glm::perspective( fov, ratio, near, far );
  
}

//==================================
void Camera::SetPosition(float x, float y, float z)
{

}

//==================================
void Camera::MoveForward( float diff)
{
	m_position = m_position + (m_forward*diff);
	m_viewTarget = m_viewTarget + (m_forward*diff);
	//glm::cross( );
    m_ViewMat = glm::lookAt( m_position, m_viewTarget, glm::vec3(0.0f, 1.0f, 0.0f ) );
	
    //m_ViewMat = glm::lookAt( m_position, m_viewTarget, glm::vec3(0.0f, 1.0f, 0.0f ) );
}

//==================================
const glm::mat4& Camera::GetProjMatrix() const
{
    return m_ProjectionMat; 
}

//==================================
const glm::mat4& Camera::GetViewMatrix() const
{
    return m_ViewMat;
}


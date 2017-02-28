#include "Storm3DCore/include/FPSCamera.h" 

#include "Storm3DCore/include/FPSCamera.h" 

#include "Storm3DCore/include/FPSCamera.h" 

#include "Storm3DRendering/include/EngineUniforms.h"

#include <glm/ext.hpp>

#include <cassert>
//==================================
FPSCamera::FPSCamera():m_starfOffset(0.0), m_moveOffset(0.0f),m_yaw(0.0f), m_pitch(0.0f), m_position(0,0,0,1), m_forward( 0.0f,0.0f,-1.0f, 0.0f)
{
	m_isProjDirty = false;
	m_isViewDirty = false;
	//m_forward = glm::normalize(m_viewTarget - m_position);
}

//==================================
FPSCamera::FPSCamera( glm::vec4 target, glm::vec4 position):m_starfOffset(0.0), m_moveOffset(0.0f),m_yaw(0.0f), m_pitch(0.0f), m_position(0,0,0,1),/*m_up(0.0f, 1.0f, 0.0, 0.0f),*/ m_forward(0,0,0,0)
{
	m_isProjDirty = false;
	m_isViewDirty = false;
	m_forward = glm::normalize(target - position);
}

//==================================
FPSCamera::~FPSCamera()
{

}

//==================================
//void FPSCamera::LookAt( glm::vec3& position, glm::vec3& target)
//{
//    m_position = position;
//    m_ViewMat = glm::lookAt( position, target, glm::vec3(0.0f, 1.0f, 0.0f ) );
//    int len = m_ViewMat.length();
//
//    EngineUniforms::GetInstance().m_viewMatrix->SetValue( glm::value_ptr( m_ViewMat ) );
//
//	glm::mat3 normalMat =  glm::mat3( ( m_ViewMat ));
//	//glm::mat3 normalMat =  glm::mat3( glm::transpose( glm::inverse(m_ViewMat) ));
//	int count = normalMat.length();
//	//EngineUniforms::GetInstance().m_normalMatrix->SetValue(  glm::value_ptr(normalMat) );
//}

//#include <iostream>
//==================================
void FPSCamera::Roll()
{
 //   m_viewTarget = glm::rotateY( m_viewTarget, degree );    
	//m_viewTarget += m_position;

	//m_forward = glm::normalize(m_viewTarget - m_position);
 //   m_ViewMat = glm::lookAt( m_position, m_viewTarget, glm::vec3(0.0f, 1.0f, 0.0f ) );
 //   //EngineUniforms::GetInstance().m_viewMatrix->SetValue( glm::value_ptr(m_ViewMat), m_ViewMat.length()  );
}

//==================================
void FPSCamera::Yaw( float degree )
{
	m_yaw = degree;
	//m_right = glm::vec4(right, 0.0f);
	m_isViewDirty = true;
}

//==================================
void FPSCamera::Pitch( float degree )
{
	m_pitch = degree;
	m_isViewDirty = true;
	//glm::vec3 forward = glm::rotate(glm::vec3(m_forward.x, m_forward.y, m_forward.z), 
	//							degree,
	//							glm::vec3(m_right.x, m_right.y, m_right.z) );

	//m_forward = glm::vec4(forward, 0.0f);
	////m_up = glm::vec4(up, 0.0f);
	//m_isViewDirty = true;
}

//==================================
void FPSCamera::MoveForward( float degree )
{
	m_moveOffset = degree;
	m_isViewDirty = true;
	//EngineUniforms::GetInstance().m_viewMatrix->SetValue( glm::value_ptr( m_viewMat) );
}

//==================================
void FPSCamera::Starf( float offset )
{
	m_starfOffset = offset;
	m_isViewDirty = true;
	/*glm::vec4 moveVec = m_right;
	moveVec *= -degree;
	m_position += moveVec;
	*/
}


//==================================
void FPSCamera::Frustum( float left, float right, float bottom, float top, float near, float far )
{ 
    m_projectionMat = glm::frustum(left, right, bottom, top, near, far );
   
    EngineUniforms::GetInstance().m_projectionMatrix->SetValue( glm::value_ptr(m_projectionMat) );
}

//==================================
void FPSCamera::Perspective( float fov, float ratio, float near, float far)
{
    m_projectionMat = glm::perspective( fov, ratio, near, far );
    EngineUniforms::GetInstance().m_projectionMatrix->SetValue( glm::value_ptr( m_projectionMat ) );
}

//==================================
void FPSCamera::Update ( float deltaTime )
{
	UpdateImpl( deltaTime );
   //EngineUniforms::GetInstance().m_projectionMatrix->SetValue( glm::value_ptr(m_projectionMat), 16 );
}

//==================================
void FPSCamera::UpdateImpl (float deltaTime)
{
	if ( m_isViewDirty )
	{
		glm::vec3 tempForward = glm::rotate( glm::vec3(m_forward.x, m_forward.y, m_forward.z), m_yaw, glm::vec3(0,1,0) );
		// Claculate Right Vector
		glm::vec3 right = glm::cross( tempForward, glm::vec3(0,1,0) );
		tempForward += glm::rotate( glm::vec3(m_forward.x, m_forward.y, m_forward.z), m_pitch, right );

		m_forward = glm::vec4(tempForward, 0.0f);
		m_forward = glm::normalize( m_forward );

		//update position
		glm::vec4 moveVec(m_forward);
		moveVec *= m_moveOffset;

		glm::vec4 starfVec(right, 0.0f);
		starfVec *= m_starfOffset;
		
		m_position += (moveVec + starfVec);

		m_viewMat = glm::lookAt((glm::vec3)m_position, (glm::vec3)(m_position + m_forward), glm::vec3(0,1,0));

		m_yaw = 0.0f;
		m_pitch = 0.0f;
		m_moveOffset = 0.0f;
		m_starfOffset = 0.0f;
		/*	glm::vec3 forward( m_forward.x, m_forward.y, m_forward.z);
		glm::vec3 up( 0, 1, 0 );

		glm::vec3 right = glm::cross( forward, glm::vec3(0,1,0) );

		up = glm::cross( right, forward );

		m_viewMat = glm::mat4( glm::vec4(right,0), glm::vec4(up, 0 ), m_forward, m_position );
		m_viewMat = glm::inverse( m_viewMat );
		*/
		m_isViewDirty = false;
	}
    //m_projectionMat = glm::perspective( fov, ratio, near, far );  
}

//==================================
void FPSCamera::SetPosition(float x, float y, float z)
{
	m_position = glm::vec4(x, y, z, 1);
	m_isViewDirty = true;
}

//==================================
//void FPSCamera::MoveForward( float diff)
//{
//	m_position = m_position + (m_forward*diff);
//	m_viewTarget = m_viewTarget + (m_forward*diff);
//    m_ViewMat = glm::lookAt( m_position, m_viewTarget, glm::vec3(0.0f, 1.0f, 0.0f ) );
//	
//    //m_ViewMat = glm::lookAt( m_position, m_viewTarget, glm::vec3(0.0f, 1.0f, 0.0f ) );
//}

//==================================
const glm::mat4& FPSCamera::GetProjMatrix() const
{
    return m_projectionMat; 
}

//==================================
const glm::mat4& FPSCamera::GetViewMatrix() const
{
    return m_viewMat;
}

//==================================
const glm::mat3& FPSCamera::GetNormalMatrix() const
{
	//return glm::mat3( glm::transpose(glm::inverse( m_viewMat) ));
	return glm::mat3(m_viewMat);

}





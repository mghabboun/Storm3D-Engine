#ifndef STORM_3D_FPS_CAMERA
#define STORM_3D_FPS_CAMERA

#include "Storm3DCore/include/Camera.h"

class FPSCamera 
{
public:
	FPSCamera();
	FPSCamera(glm::vec4 target, glm::vec4 position);
	~FPSCamera();

	void				MoveForward( float step );
	void				Yaw( float degree );
	void				Pitch( float degree);
	void				Roll();
	const glm::mat4&	GetProjMatrix() const;
	const glm::mat4&	GetViewMatrix() const;
	const glm::mat3&	GetNormalMatrix() const;
	glm::vec4			GetForward() const { return m_forward; }
	glm::vec4			Position()const { return m_position; }
	void				Frustum( float left, float right, float bottom, float top, float near, float far );
	void				Perspective( float fov, float ratio, float near, float far);
	void				Update ( float deltaTime );
	void				UpdateImpl (float deltaTime);
	void				SetPosition(float x, float y, float z);
	void				Starf( float degree );

private:
	glm::mat4		m_viewMat;			// the result view matrix  
	glm::mat4		m_projectionMat;	// the projection matrix

	//glm::vec4		m_up;
	glm::vec4		m_position;
	glm::vec4		m_forward;
	float			m_yaw;
	float			m_pitch;
	float			m_moveOffset;
	float			m_starfOffset;
	bool			m_isProjDirty;
	bool			m_isViewDirty;
	RenderTarget	m_target;
};

#endif
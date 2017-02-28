#ifndef STORM_3D_CAMERA_H_
#define STORM_3D_CAMERA_H_

//#include "Storm3DMath/include/AppWorldMatrix4.h"
#include "Storm3DRendering/include/RenderTarget.h" 
#include <glm/glm.hpp>

class Camera
{

public:

    Camera();
    ~Camera();

    void LookAt ( glm::vec3& position, glm::vec3& target);
	void MoveForward( float step );
    void Frustum( float left, float right, float bottom, float top, float near, float far );
    void Perspective( float fov, float ratio, float near, float far);
    void Update ( float deltaTime ); 
    void UpdateImpl (float deltaTime); 

    void SetPosition( float x, float y, float z);

    void RotateY(  float degree );
    void RotateZ(  float degree );
    void RotateX(  float degree );

    const glm::mat4& GetProjMatrix() const;
    const glm::mat4& GetViewMatrix() const;

protected:        

    glm::mat4		m_ViewMat;			// the result view matrix  
    glm::mat4		m_ProjectionMat;	// the projection matrix
    
	glm::vec3		m_position;
	glm::vec3		m_forward;
	glm::vec3		m_right;
    
    glm::vec3		m_viewTarget;
	RenderTarget m_target;
};


#endif
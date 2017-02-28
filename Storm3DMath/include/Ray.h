
#ifndef STORM_3D_RAY
#define STORM_3D_RAY

#include <glm/glm.hpp>

/** Representation of a ray in space, i.e. a line with an origin and direction. */
class Ray
{

public:
    Ray():m_Origin( ), m_Direction( ) {}

    Ray(const glm::vec3& origin, const glm::vec3& direction)
        :m_Origin(origin), m_Direction(direction) {}

    /** Sets the origin of the ray. */
    void SetOrigin(const glm::vec3& origin) {m_Origin = origin;} 

    // Gets the origin of the ray. 
    const glm::vec3& GetOrigin(void) const {return m_Origin;} 
	glm::vec3 GetOrigin(void) {return m_Origin;} 
    // Sets the direction of the ray.
    void SetDirection(const glm::vec3& dir){ m_Direction = dir; } 

    // Gets the direction of the ray.
    const glm::vec3& GetDirection(void) const {return m_Direction;} 
	glm::vec3& GetDirection(void)	{return m_Direction;} 
    // Gets the position of a point t units along the ray.
    glm::vec3 GetPoint(float t) const 
    { 
        return glm::vec3(m_Origin + (m_Direction * t));
    }

    /** Gets the position of a point t units along the ray. */
    glm::vec3 operator*(float t) const {  return GetPoint(t);  }
	
private:
    glm::vec3 m_Origin;
    glm::vec3 m_Direction;

};	


#endif

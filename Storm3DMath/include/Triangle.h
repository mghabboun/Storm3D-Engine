#ifndef STORM_3D_TRIANGLE
#define STORM_3D_TRIANGLE


#include "glm/glm.hpp"


class Triangle
{
public:
					Triangle (const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2 );

	glm::vec3		CalcNormal();

	glm::vec3&		operator[] (int i) { return m_V[i]; }
	glm::vec3		operator [] (int i)const { return m_V[i]; };

	bool			RayIntersect (glm::vec3& origin, glm::vec3& dir, float& distance, glm::vec3 &intersection);

	//void SetVertex ( int i,const glm::vec3& v );
	glm::vec3		m_V[3];
private:
	
	glm::vec3		E1, E2; //edges , precomputed

};
#endif 
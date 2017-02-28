#ifndef ST_HIT_RECORD
#define ST_HIT_RECORD

#include <external/glm/glm.hpp>

//namespace Storm
class HitRecord
{

public:
	HitRecord():m_distance(0.0f), m_hit(false),	m_intrsctPoint(0.0f,0.0f,0.0f)
	{
	
	}

private:
	float			m_distance;
	bool			m_hit;
	glm::vec3		m_intrsctPoint;

};


#endif 
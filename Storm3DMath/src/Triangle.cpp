#include "Storm3DMath/include/Triangle.h"

//===========================================================
Triangle::Triangle(const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2)
{
	m_V[0] = v0;
	m_V[1] = v1;
	m_V[2] = v2;
	/****precalculations ***/
	E1 = m_V[1]-m_V[0];
	E2 = m_V[2]-m_V[0];

	
	//CalculateD (m_V[0]);
}

//===========================================================
glm::vec3 Triangle::CalcNormal()
{
	return glm::normalize( glm::cross(E1, E2) );
	
}

//===========================================================
#define err 0.0001
bool Triangle::RayIntersect (glm::vec3& origin, glm::vec3& dir, float& distance, glm::vec3& intersection)
{
	float u,v,t;
	//bool intersect(const Ray<float> &r, IsectData &isectData) const
	glm::vec3 edge1 = m_V[1] - m_V[0];
	glm::vec3 edge2 = m_V[2] - m_V[0];
	glm::vec3 pvec = glm::cross(dir, edge2);
	float det = glm::dot(edge1, pvec);
	if (det == 0) return false;
	float invDet = 1 / det;
	glm::vec3 tvec = origin - m_V[0];
	u = glm::dot(tvec, pvec) * invDet;
	if (u < 0 || u > 1){
		return false;
	}

	glm::vec3 qvec = glm::cross(tvec, edge1);
	v = glm::dot(dir, qvec) * invDet;

	if (v < 0 || u + v > 1) {
		return false;
	}

	t = glm::dot(edge2, qvec) * invDet;
	distance = t;
	intersection = origin + t*dir;
	return true;
}
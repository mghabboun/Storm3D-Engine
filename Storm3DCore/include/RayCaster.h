#ifndef RAY_CASTER
#define RAY_CASTER
#include <glm/glm.hpp>

class RayCaster
{
public:
	RayCaster(){}
	~RayCaster(){ }

	static glm::vec3 GenerateRay( int mouseX, int mouseY, int scrnWidth, int scrnHeight,  const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
	{
		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, scrnWidth, scrnHeight);
		glm::vec3 screenPos = glm::vec3(mouseX, scrnHeight-mouseY - 1, 0.0f);
	    glm::vec3 worldPos = glm::unProject( screenPos, viewMatrix, projMatrix, viewport );
		return worldPos;
	}

	void CastRay( glm::vec3 origin, glm::vec3 dir, Node* root )
	{
		//Ray r();

	}

};

#endif
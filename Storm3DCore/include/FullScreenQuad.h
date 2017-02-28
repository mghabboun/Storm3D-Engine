#ifndef STORM3D_FULLSCREEN_QUAD
#define STORM3D_FULLSCREEN_QUAD

#include "Storm3DRendering/include/HardwareBuffer.h"
#include "Storm3DRendering/include/Shader.h"

class Mesh;

class FullScreenQuad
{
public:
	FullScreenQuad();
	void Init();
	void DrawFullScreenQuad();

	Mesh* quad;
	//HardwareBuffer buffer;
    Shader*         shader;
};

#endif

#ifndef DRAW_ATTRIBS
#define DRAW_ATTRIBS

enum DrawMode
{	
		Lines			= 0x0001,
		LineLoop		= 0x0002,
		LineStrip		= 0x0003,
		Triangles		= 0x0004,
		TriangleStrip	= 0x0005,
		TriangleFan		= 0x0006
};

	const unsigned int ResetPrimitiveIdx = 2147483647;

#endif
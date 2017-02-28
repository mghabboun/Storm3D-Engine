#ifndef STORM_3D_FRAME_BUFFER_OBJECT
#define STORM_3D_FRAME_BUFFER_OBJECT

class FrameBufferObject
{

public:
    FrameBufferObject();
	~FrameBufferObject();

	unsigned int GenTexture(unsigned int width, unsigned int height);

public:

    void GenerateFrameBuffer( unsigned int width, unsigned int height);
    void BindFrameBuffer();
	void UnBindFrameBuffer();
    void AttachRenderTarget();
 
private:
	unsigned int m_id;
	unsigned int depthBufferName;
	unsigned int renderBufferName;
	unsigned int fboName;
	unsigned int m_texName;	
};

#endif 
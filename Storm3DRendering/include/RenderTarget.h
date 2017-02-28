#ifndef APP_WORLD_RENDER_TARGET
#define APP_WORLD_RENDER_TARGET


class FrameBufferObject; 
class RenderTarget
{
public: 

    RenderTarget();
    void GenRenderTarget();
    void AttachToFrameBuffer( FrameBufferObject* fb);
    void BindRenderTarget();
    
private: 
    unsigned int m_width; 
    unsigned int m_height;
   
    unsigned int m_id;
    bool m_isAttached; 
};


#endif 
#ifndef STORM_3D_TEXTURE
#define STORM_3D_TEXTURE

class Texture
{

public: 
    Texture(unsigned int handle); 
    void ActivateTexture();
    unsigned int GetID(){ return m_id; }
private:
    //std::string m_name; 

    unsigned int m_id; 
};


#endif 
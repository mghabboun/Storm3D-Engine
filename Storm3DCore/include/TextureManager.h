#ifndef STORM_3D_TEXTURE_MANAGER
#define STORM_3D_TEXTURE_MANAGER

#include "Storm3DRendering/include/Texture.h" 
#include "Storm3DCore/include/Handle.h" 

#include <vector> 
#include <map> 


class TextureManager;

typedef Handle<Texture, TextureManager> TextureHandle;

class TextureManager
{
	
public:
	static TextureManager& GetInstance(); 
	
	TextureManager();
	TextureHandle			LoadTextureFromFile(const std::string& filename);
	void					Initialize();
	const std::string&		GetName();
	//Texture*				CheckIfTextureLoaded(  const std::string& filename );
	TextureHandle			CheckIfTextureLoaded( const std::string& filename );
    TextureHandle           LoadTexture();

	Texture*				GetResource(int i){ return m_textures[i]; }

	Texture*				CreateTexture();
	Texture*				CreateTextureHandle();
    TextureHandle           GetDefaultTexture();
private: 
     
	void                    LoadDefaultTexture();
	//void   CreateTexture(unsigned int m_id);
	//AddTexture();
	std::map< std::string , TextureHandle> m_texturesMap; // lookup table by name
	std::vector< Texture* > m_textures;
	std::string m_name;
};

#endif 
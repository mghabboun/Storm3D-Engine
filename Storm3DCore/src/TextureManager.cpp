#include "Storm3DCore/include/TextureManager.h" 

#include "Storm3DRendering/include/OpenGL.h"
#include "DevIL-SDK-x64-1.7.8/include/IL/il.h" 
#include "DevIL-SDK-x64-1.7.8/include/IL/ilut.h" 

#include <string> 
#include <algorithm>


//=================================================
TextureManager::TextureManager()
{
  ilInit();
  GLenum err2 = glGetError();

  /*     bool t = ilutRenderer( ILUT_OPENGL );
  GLenum err = glGetError();

  ilutInit();*/

  GLenum err1 = glGetError();

}

//=================================================
TextureManager& TextureManager::GetInstance()
{
  static TextureManager manager;
  return manager;
}

//=================================================
std::string  ExtractFileName( const std::string& filepath )
{
  std::string finalFilename(filepath);
  //std::for_each ( finalFilename.begin(), finalFilename.end(), ::tolower );
  std::transform(finalFilename.begin(), finalFilename.end(), finalFilename.begin(), ::tolower);  

  return finalFilename;
}

//=================================================
TextureHandle TextureManager::LoadTextureFromFile(const std::string& filename)
{	
  std::string texFilename = ExtractFileName(filename);
  TextureHandle t =  CheckIfTextureLoaded( texFilename.c_str() );
  if( t.IsValid() )
  {
    return t;
  }

  unsigned int imageName; 
  ilGenImages( 1, &imageName );
  ilBindImage(imageName);
  bool loaded = ilLoadImage( filename.c_str() );  
  if ( !loaded )
  {   
    ilBindImage(0);
    ilDeleteImage(imageName);
    return TextureHandle();
  }

  unsigned int texId;
  glGenTextures( 1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId );
  /* Create and load textures to OpenGL */
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //bool x = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

  /* Create and load textures to OpenGL */
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //GLenum e3 =  glGetError();

  int w = ilGetInteger(IL_IMAGE_WIDTH);
  int h = ilGetInteger(IL_IMAGE_HEIGHT);  
  glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
  ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

  Texture* texture = new Texture( texId );
  m_textures.push_back( texture );
  TextureHandle handle( this, m_textures.size()-1 );
  m_texturesMap[texFilename] = handle;

  glBindTexture(GL_TEXTURE_2D, 0);
  ilBindImage(0);
  ilDeleteImage(imageName);

  GLenum e = glGetError();
  return handle;
}

//=================================================
TextureHandle TextureManager::LoadTexture()
{
  return TextureHandle();
}

//=================================================
TextureHandle  TextureManager::CheckIfTextureLoaded( const std::string& filename )
{
  auto it = m_texturesMap.find( filename );
  if ( it != m_texturesMap.end() )
  {
    return it->second;
  }

  return TextureHandle();
}

//=================================================
TextureHandle  TextureManager::GetDefaultTexture()
{
  static bool loaded = false;
  if (!loaded )
  {
  unsigned char whitePixel[] = { 255, 255, 255, 255,
                                 255, 255, 255, 255, 
                                 255, 255, 255, 255,
                                 255, 255, 255, 255 };
  unsigned int texId;
  glGenTextures( 1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId );  

  /* Create and load textures to OpenGL */
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  

 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &whitePixel[0]);

  //glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
  //ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
  Texture* texture = new Texture( texId );
  m_textures.push_back( texture );
  TextureHandle handle( this, m_textures.size()-1 );

  glBindTexture(GL_TEXTURE_2D, 0); 
  GLenum e = glGetError();
  }

  return   m_texturesMap["default"]; 
}

//================================================= 
void  TextureManager::LoadDefaultTexture()
{

}


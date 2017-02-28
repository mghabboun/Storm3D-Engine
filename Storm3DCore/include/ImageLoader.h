#ifndef STORM_3D_IMAGE_LOADER_H
#define STORM_3D_IMAGE_LOADER_H

#include "IL/il.h"
#include "IL/ilut.h"


//#include "DevIL-SDK-x64-1.7.8/include/IL/il.h" 
//#include "DevIL-SDK-x64-1.7.8/include/IL/ilut.h" 

#include <string>
#include <algorithm>

static std::string  ExtractFileName( const std::string& filepath )
{
	std::string finalFilename(filepath);
	//std::for_each ( finalFilename.begin(), finalFilename.end(), ::tolower );
	std::transform(finalFilename.begin(), finalFilename.end(), finalFilename.begin(), ::tolower);

	return finalFilename;
}

class Image
{
public:
	Image(unsigned int imageHandle, unsigned int width, unsigned int height, ILubyte* data):m_imageHandle(), m_width(width), m_height(height),bytes(data)
	{

	}

	~Image()
	{
		ilBindImage(0);
		ilDeleteImage(m_imageHandle);
	}

	unsigned int	Width(){ return m_width;}
	unsigned int	Height(){ return m_height;}
	ILubyte*		GetData(){return bytes;};

	unsigned int	m_imageHandle;
	unsigned int	m_width;
	unsigned int	m_height; 
	ILubyte*		bytes;
};

class ImageLoader
{
public:
	//=================================================
	Image* LoadImage(const std::string& filename)
	{
		std::string texFilename = ExtractFileName(filename);

		unsigned int imageName; 
		ilGenImages( 1, &imageName );
		ilBindImage(imageName);
		bool loaded = ilLoadImage(filename.c_str() );
		if ( !loaded )
		{   
			ilBindImage(0);
			ilDeleteImage(imageName);
		}

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		Image* image = new Image(imageName, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetData() );
		
		return image;
	}

};


#endif

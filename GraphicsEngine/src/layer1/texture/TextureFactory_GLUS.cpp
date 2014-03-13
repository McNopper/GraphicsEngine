/*
 * TextureFactory.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactory.h"

using namespace std;
using namespace boost;

TextureFactory::TextureFactory() :
		TextureFactoryBase()
{
}

TextureFactory::~TextureFactory()
{
}

GLuint TextureFactory::loadImage(const string& filename, string& identifier) const
{
	// TODO Implement

	return 0;
}

Texture2DSP TextureFactory::loadTexture2D(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	// TODO Implement

	return Texture2DSP();
}

TextureCubeMapSP TextureFactory::loadTextureCubeMap(const string& identifier, const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	// TODO Implement

	return TextureCubeMapSP();
}

TextureCubeMapSP TextureFactory::loadTextureCubeMap(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	// TODO Implement

	return TextureCubeMapSP();
}

//
// Saving
//

bool TextureFactory::saveImage(const string& identifier, const PixelData& pixelData) const
{
	// TODO Implement

	return false;
}

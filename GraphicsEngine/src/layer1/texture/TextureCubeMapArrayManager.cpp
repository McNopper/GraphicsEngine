/*
 * TextureCubeMapArrayManager.cpp
 *
 *  Created on: 14.06.2014
 *      Author: nopper
 */

#include "TextureFactory.h"

#include "TextureCubeMapArrayManager.h"

using namespace std;

TextureCubeMapArrayManager::TextureCubeMapArrayManager() :
	Singleton<TextureCubeMapArrayManager>(), allTextures()
{
}

TextureCubeMapArrayManager::~TextureCubeMapArrayManager()
{
}

void TextureCubeMapArrayManager::addTexture(const string& identifier, const TextureCubeMapArraySP& texture)
{
	allTextures[identifier] = texture;
}

TextureCubeMapArraySP TextureCubeMapArrayManager::createTexture(const string& identifier, const string filename[], int32_t sizeOfArray, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(identifier))
	{
		allTextures[identifier] = textureFactory.loadTextureCubeMapArray(identifier, filename, sizeOfArray, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[identifier];
	}

	return allTextures[identifier];
}



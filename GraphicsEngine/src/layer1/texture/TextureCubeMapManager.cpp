/*
 * TextureCubeMapManager.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactory.h"

#include "TextureCubeMapManager.h"

using namespace std;

TextureCubeMapManager::TextureCubeMapManager() :
		Singleton<TextureCubeMapManager>(), allTextures()
{
}

TextureCubeMapManager::~TextureCubeMapManager()
{
}

void TextureCubeMapManager::addTexture(const string& identifier, const TextureCubeMapSP& texture)
{
	allTextures[identifier] = texture;
}

TextureCubeMapSP TextureCubeMapManager::createTexture(const string& identifier, const string& posX, const string& negX, const string& posY, const string& negY, const string& posZ, const string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(posX))
	{
		allTextures[posX] = textureFactory.loadTextureCubeMap(identifier, posX, negX, posY, negY, posZ, negZ, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[posX];
	}

	return allTextures[posX];
}

TextureCubeMapSP TextureCubeMapManager::createTexture(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(filename))
	{
		allTextures[filename] = textureFactory.loadTextureCubeMap(filename, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[filename];
	}

	return allTextures[filename];
}

/*
 * Texture1DArrayManager.cpp
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#include "TextureFactory.h"

#include "Texture1DArrayManager.h"

using namespace std;

Texture1DArrayManager::Texture1DArrayManager() :
		Singleton<Texture1DArrayManager>(), allTextures()
{
}

Texture1DArrayManager::~Texture1DArrayManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

void Texture1DArrayManager::addTexture(const string& key, const Texture1DArraySP& texture)
{
	allTextures[key] = texture;
}

Texture1DArraySP Texture1DArrayManager::createTexture(const string& key, int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture1DArray(key, width, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture1DArraySP Texture1DArrayManager::createTexture(const string& key, GLint internalFormat, int32_t width, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture1DArray(key, internalFormat, width, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}


/*
 * Texture2DArrayManager.cpp
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#include "TextureFactory.h"

#include "Texture2DArrayManager.h"

using namespace std;

Texture2DArrayManager::Texture2DArrayManager() :
		Singleton<Texture2DArrayManager>(), allTextures()
{
}

Texture2DArrayManager::~Texture2DArrayManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

void Texture2DArrayManager::addTexture(const string& key, const Texture2DArraySP& texture)
{
	allTextures[key] = texture;
}

Texture2DArraySP Texture2DArrayManager::createTexture(const string& key, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2DArray(key, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture2DArraySP Texture2DArrayManager::createTexture(const string& key, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2DArray(key, internalFormat, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}



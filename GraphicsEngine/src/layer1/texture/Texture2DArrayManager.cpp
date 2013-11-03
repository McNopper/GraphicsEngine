/*
 * Texture2DArrayManager.cpp
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#include "TextureFactory.h"

#include "Texture2DArrayManager.h"

using namespace std;
using namespace boost;

Texture2DArrayManager* Texture2DArrayManager::instance;

Texture2DArrayManager::Texture2DArrayManager() :
		allTextures()
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

Texture2DArrayManager* Texture2DArrayManager::getInstance()
{
	if (!instance)
	{
		instance = new Texture2DArrayManager();
	}

	return instance;
}

void Texture2DArrayManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void Texture2DArrayManager::addTexture(const string& key, const Texture2DArraySP& texture)
{
	allTextures[key] = texture;
}

Texture2DArraySP Texture2DArrayManager::createTexture(const string& key, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture2DArray(width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture2DArraySP Texture2DArrayManager::createTexture(const string& key, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture2DArray(internalFormat, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT);

		return allTextures[key];
	}

	return allTextures[key];
}



/*
 * Texture2DManager.cpp
 *
 *  Created on: 31.05.2011
 *      Author: Norbert Nopper
 */

#include "TextureFactory.h"

#include "Texture2DManager.h"

using namespace std;
using namespace boost;

Texture2DManager* Texture2DManager::instance;

Texture2DManager::Texture2DManager() :
	allTextures()
{
}

Texture2DManager::~Texture2DManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

Texture2DManager* Texture2DManager::getInstance()
{
	if (!instance)
	{
		instance = new Texture2DManager();
	}

	return instance;
}

void Texture2DManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void Texture2DManager::addTexture(const string& key, const Texture2DSP& texture)
{
	allTextures[key] = texture;
}

Texture2DSP Texture2DManager::createTexture(const string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	auto walker = allTextures.find(filename);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[filename] = textureFactory.loadTexture2D(filename, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[filename];
	}

	return allTextures[filename];
}

Texture2DSP Texture2DManager::createTexture(const string& key, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture2D(key, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[key];
	}

	return allTextures[key];
}

Texture2DSP Texture2DManager::createTexture(const string& key, GLint internalFormat, int32_t width, int32_t height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	auto walker = allTextures.find(key);

	TextureFactory textureFactory;

	if (walker == allTextures.end())
	{
		allTextures[key] = textureFactory.createTexture2D(key, internalFormat, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[key];
	}

	return allTextures[key];
}

/*
 * Texture2DMultisampleManager.cpp
 *
 *  Created on: 04.02.2013
 *      Author: nopper
 */

#include "TextureFactory.h"

#include "Texture2DMultisampleManager.h"

using namespace std;

Texture2DMultisampleManager::Texture2DMultisampleManager() :
		Singleton<Texture2DMultisampleManager>(), allTextures()
{
}

Texture2DMultisampleManager::~Texture2DMultisampleManager()
{
	auto walker = allTextures.begin();
	while (walker != allTextures.end())
	{
		walker->second.reset();

		walker++;
	}
	allTextures.clear();
}

void Texture2DMultisampleManager::addTexture(const string& key, const Texture2DMultisampleSP& texture)
{
	allTextures[key] = texture;
}

Texture2DMultisampleSP Texture2DMultisampleManager::createTexture(const string& key, int32_t samples, GLint internalFormat, int32_t width, int32_t height, bool fixedsamplelocations)
{
	TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2DMultisample(key, samples, internalFormat, width, height, fixedsamplelocations);

		return allTextures[key];
	}

	return allTextures[key];
}



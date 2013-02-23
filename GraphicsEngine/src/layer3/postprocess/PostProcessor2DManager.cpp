/*
 * PostProcessor2DManager.cpp
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#include "PostProcessor2DManager.h"

using namespace std;

PostProcessor2DManager* PostProcessor2DManager::instance = nullptr;

PostProcessor2DManager::PostProcessor2DManager() :
	allPostProcessors()
{
}

PostProcessor2DManager::~PostProcessor2DManager()
{
	auto walker = allPostProcessors.begin();
	while (walker != allPostProcessors.end())
	{
		walker->second.reset();
		walker++;
	}
	allPostProcessors.clear();
}

PostProcessor2DManager* PostProcessor2DManager::getInstance()
{
	if (!instance)
	{
		instance = new PostProcessor2DManager();
	}

	return instance;
}

void PostProcessor2DManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool PostProcessor2DManager::containsPostProcessor(const string& key) const
{
	return allPostProcessors.at(key);
}

const PostProcessor2DSP& PostProcessor2DManager::getPostProcessor(const string& key) const
{
	return allPostProcessors.at(key);
}

void PostProcessor2DManager::addPostProcessor(const string& key, const PostProcessor2DSP& postProcessor)
{
	allPostProcessors[key] = postProcessor;
}

PostProcessor2DSP PostProcessor2DManager::createPostProcessor(const string& key, GLenum internalFormat, GLenum format, GLenum type)
{
	auto walker = allPostProcessors.find(key);

	if (walker == allPostProcessors.end())
	{
		allPostProcessors[key] = PostProcessor2DSP(new PostProcessor2D(internalFormat, format, type));

		return allPostProcessors[key];
	}

	return allPostProcessors[key];
}


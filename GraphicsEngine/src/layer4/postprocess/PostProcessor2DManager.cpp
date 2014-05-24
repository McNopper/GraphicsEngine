/*
 * PostProcessor2DManager.cpp
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#include "PostProcessor2DManager.h"

using namespace std;

PostProcessor2DManager::PostProcessor2DManager() :
	Singleton<PostProcessor2DManager>(), allPostProcessors()
{
}

PostProcessor2DManager::~PostProcessor2DManager()
{
}

bool PostProcessor2DManager::containsPostProcessor(const string& key) const
{
	return allPostProcessors.contains(key);
}

const PostProcessor2DSP& PostProcessor2DManager::getPostProcessor(const string& key) const
{
	return allPostProcessors.at(key);
}

void PostProcessor2DManager::addPostProcessor(const string& key, const PostProcessor2DSP& postProcessor)
{
	allPostProcessors.add(key, postProcessor);
}

PostProcessor2DSP PostProcessor2DManager::createPostProcessor(const string& key, GLenum internalFormat, GLenum format, GLenum type)
{
	if (!allPostProcessors.contains(key))
	{
		PostProcessor2DSP value = PostProcessor2DSP(new PostProcessor2D(internalFormat, format, type));

		allPostProcessors.add(key, value);

		return value;
	}

	return allPostProcessors.at(key);
}


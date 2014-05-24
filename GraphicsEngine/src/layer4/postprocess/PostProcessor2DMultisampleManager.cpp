/*
 * PostProcessor2DMultisampleManager.cpp
 *
 *  Created on: 06.02.2013
 *      Author: nopper
 */

#include "PostProcessor2DMultisampleManager.h"

using namespace std;

PostProcessor2DMultisampleManager::PostProcessor2DMultisampleManager() :
	Singleton<PostProcessor2DMultisampleManager>(), allPostProcessors()
{
}

PostProcessor2DMultisampleManager::~PostProcessor2DMultisampleManager()
{
}

bool PostProcessor2DMultisampleManager::containsPostProcessor(const string& key) const
{
	return allPostProcessors.contains(key);
}

const PostProcessor2DMultisampleSP& PostProcessor2DMultisampleManager::getPostProcessor(const string& key) const
{
	return allPostProcessors.at(key);
}

void PostProcessor2DMultisampleManager::addPostProcessor(const string& key, const PostProcessor2DMultisampleSP& postProcessorMultisample)
{
	allPostProcessors.add(key, postProcessorMultisample);
}

PostProcessor2DMultisampleSP PostProcessor2DMultisampleManager::createPostProcessor(const string& key, int32_t samples, GLenum internalFormat, bool fixedsamplelocations)
{
	if (!allPostProcessors.contains(key))
	{
		PostProcessor2DMultisampleSP value = PostProcessor2DMultisampleSP(new PostProcessor2DMultisample(samples, internalFormat, fixedsamplelocations));

		allPostProcessors.add(key, value);

		return value;
	}

	return allPostProcessors.at(key);
}


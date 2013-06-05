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
	auto walker = allPostProcessors.begin();
	while (walker != allPostProcessors.end())
	{
		walker->second.reset();
		walker++;
	}
	allPostProcessors.clear();
}

bool PostProcessor2DMultisampleManager::containsPostProcessor(const string& key) const
{
	return allPostProcessors.find(key) != allPostProcessors.end();
}

const PostProcessor2DMultisampleSP& PostProcessor2DMultisampleManager::getPostProcessor(const string& key) const
{
	return allPostProcessors.at(key);
}

void PostProcessor2DMultisampleManager::addPostProcessor(const string& key, const PostProcessor2DMultisampleSP& postProcessorMultisample)
{
	allPostProcessors[key] = postProcessorMultisample;
}

PostProcessor2DMultisampleSP PostProcessor2DMultisampleManager::createPostProcessor(const string& key, int32_t samples, GLenum internalFormat, bool fixedsamplelocations)
{
	auto walker = allPostProcessors.find(key);

	if (walker == allPostProcessors.end())
	{
		allPostProcessors[key] = PostProcessor2DMultisampleSP(new PostProcessor2DMultisample(samples, internalFormat, fixedsamplelocations));

		return allPostProcessors[key];
	}

	return allPostProcessors[key];
}


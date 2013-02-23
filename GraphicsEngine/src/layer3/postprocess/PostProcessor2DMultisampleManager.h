/*
 * PostProcessor2DMultisampleManager.h
 *
 *  Created on: 06.02.2013
 *      Author: nopper
 */

#ifndef POSTPROCESSOR2DMULTISAMPLEMANAGER_H_
#define POSTPROCESSOR2DMULTISAMPLEMANAGER_H_

#include "../../UsedLibs.h"

#include "PostProcessor2DMultisample.h"

class PostProcessor2DMultisampleManager
{

private:

	static PostProcessor2DMultisampleManager* instance;

	std::map<std::string, PostProcessor2DMultisampleSP> allPostProcessors;

	PostProcessor2DMultisampleManager();
	virtual ~PostProcessor2DMultisampleManager();

public:

	static PostProcessor2DMultisampleManager* getInstance();

	static void terminate();

	bool containsPostProcessor(const std::string& key) const;

	const PostProcessor2DMultisampleSP& getPostProcessor(const std::string& key) const;

	void addPostProcessor(const std::string& key, const PostProcessor2DMultisampleSP& postProcessorMultisample);

	PostProcessor2DMultisampleSP createPostProcessor(const std::string& key, boost::int32_t samples, GLenum internalFormat, bool fixedsamplelocations);

};

#endif /* POSTPROCESSOR2DMULTISAMPLEMANAGER_H_ */

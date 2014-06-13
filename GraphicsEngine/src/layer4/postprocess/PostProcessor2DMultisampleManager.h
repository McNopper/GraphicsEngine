/*
 * PostProcessor2DMultisampleManager.h
 *
 *  Created on: 06.02.2013
 *      Author: nopper
 */

#ifndef POSTPROCESSOR2DMULTISAMPLEMANAGER_H_
#define POSTPROCESSOR2DMULTISAMPLEMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "PostProcessor2DMultisample.h"

class PostProcessor2DMultisampleManager : public Singleton<PostProcessor2DMultisampleManager>
{

	friend class Singleton<PostProcessor2DMultisampleManager>;

protected:

	KeyValueMap<std::string, PostProcessor2DMultisampleSP> allPostProcessors;

	PostProcessor2DMultisampleManager();
	virtual ~PostProcessor2DMultisampleManager();

public:

	bool containsPostProcessor(const std::string& key) const;

	const PostProcessor2DMultisampleSP& getPostProcessor(const std::string& key) const;

	void addPostProcessor(const std::string& key, const PostProcessor2DMultisampleSP& postProcessorMultisample);

	PostProcessor2DMultisampleSP createPostProcessor(const std::string& key, std::int32_t samples, GLenum internalFormat, bool fixedsamplelocations);

};

#endif /* POSTPROCESSOR2DMULTISAMPLEMANAGER_H_ */

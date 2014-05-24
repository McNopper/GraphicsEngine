/*
 * PostProcessorManager.h
 *
 *  Created on: 29.11.2012
 *      Author: nopper
 */

#ifndef POSTPROCESSOR2DMANAGER_H_
#define POSTPROCESSOR2DMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "PostProcessor2D.h"

class PostProcessor2DManager : public Singleton<PostProcessor2DManager>
{

	friend class Singleton<PostProcessor2DManager>;

protected:

	KeyValueMap<std::string, PostProcessor2DSP> allPostProcessors;

	PostProcessor2DManager();
	virtual ~PostProcessor2DManager();

public:

	bool containsPostProcessor(const std::string& key) const;

	const PostProcessor2DSP& getPostProcessor(const std::string& key) const;

	void addPostProcessor(const std::string& key, const PostProcessor2DSP& postProcessor);

	PostProcessor2DSP createPostProcessor(const std::string& key, GLenum internalFormat, GLenum format, GLenum type);

};

#endif /* POSTPROCESSOR2DMANAGER_H_ */

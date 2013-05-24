/*
 * RenderBufferMultisampleManager.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef RENDERBUFFERMULTISAMPLEMANAGER_H_
#define RENDERBUFFERMULTISAMPLEMANAGER_H_

#include "../../UsedLibs.h"

#include "RenderBufferMultisample.h"

class RenderBufferMultisampleManager
{

private:

	static RenderBufferMultisampleManager* instance;

	std::map<std::string, RenderBufferMultisampleSP> allRenderBuffers;

	RenderBufferMultisampleManager();
	virtual ~RenderBufferMultisampleManager();

public:

	static RenderBufferMultisampleManager* getInstance();

	static void terminate();

	void addRenderBuffer(const std::string& key, const RenderBufferMultisampleSP& renderBufferMultisample);

	RenderBufferMultisampleSP createRenderBuffer(const std::string& key, boost::int32_t samples, GLenum internalFormat, boost::int32_t width, boost::int32_t height);

};

#endif /* RENDERBUFFERMULTISAMPLEMANAGER_H_ */

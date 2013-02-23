/*
 * RenderBufferManager.h
 *
 *  Created on: 27.11.2012
 *      Author: nopper
 */

#ifndef RENDERBUFFERMANAGER_H_
#define RENDERBUFFERMANAGER_H_

#include "../../UsedLibs.h"

#include "RenderBuffer.h"

class RenderBufferManager
{
private:

	static RenderBufferManager* instance;

	std::map<std::string, RenderBufferSP> allRenderBuffers;

	RenderBufferManager();
	virtual ~RenderBufferManager();

public:

	static RenderBufferManager* getInstance();

	static void terminate();

	void addRenderBuffer(const std::string& key, const RenderBufferSP& renderBuffer);

	RenderBufferSP createRenderBuffer(const std::string& key, GLenum internalFormat, boost::int32_t width, boost::int32_t height);

};

#endif /* RENDERBUFFERMANAGER_H_ */

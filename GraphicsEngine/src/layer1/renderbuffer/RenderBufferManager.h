/*
 * RenderBufferManager.h
 *
 *  Created on: 27.11.2012
 *      Author: nopper
 */

#ifndef RENDERBUFFERMANAGER_H_
#define RENDERBUFFERMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "RenderBuffer.h"

class RenderBufferManager : public Singleton<RenderBufferManager>
{

	friend class Singleton<RenderBufferManager>;

private:

	KeyValueMap<std::string, RenderBufferSP> allRenderBuffers;

	RenderBufferManager();
	virtual ~RenderBufferManager();

public:

	void addRenderBuffer(const std::string& key, const RenderBufferSP& renderBuffer);

	RenderBufferSP createRenderBuffer(const std::string& key, GLenum internalFormat, std::int32_t width, std::int32_t height);

};

#endif /* RENDERBUFFERMANAGER_H_ */

/*
 * RenderBufferMultisampleManager.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef RENDERBUFFERMULTISAMPLEMANAGER_H_
#define RENDERBUFFERMULTISAMPLEMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/Singleton.h"

#include "RenderBufferMultisample.h"

class RenderBufferMultisampleManager : public Singleton<RenderBufferMultisampleManager>
{

	friend class Singleton<RenderBufferMultisampleManager>;

private:

	std::map<std::string, RenderBufferMultisampleSP> allRenderBuffers;

	RenderBufferMultisampleManager();
	virtual ~RenderBufferMultisampleManager();

public:

	void addRenderBuffer(const std::string& key, const RenderBufferMultisampleSP& renderBufferMultisample);

	RenderBufferMultisampleSP createRenderBuffer(const std::string& key, boost::int32_t samples, GLenum internalFormat, boost::int32_t width, boost::int32_t height);

};

#endif /* RENDERBUFFERMULTISAMPLEMANAGER_H_ */

/*
 * FrameBufferCubeMapManager.h
 *
 *  Created on: 21.04.2013
 *      Author: nopper
 */

#ifndef FRAMEBUFFERCUBEMAPMANAGER_H_
#define FRAMEBUFFERCUBEMAPMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "FrameBufferCubeMap.h"

class FrameBufferCubeMapManager : public Singleton<FrameBufferCubeMapManager>
{

	friend class Singleton<FrameBufferCubeMapManager>;

private:

	KeyValueMap<std::string, FrameBufferCubeMapSP> allFrameBuffers;

	FrameBufferCubeMapManager();
	virtual ~FrameBufferCubeMapManager();

public:

	bool containsFrameBuffer(const std::string& key) const;

	const FrameBufferCubeMapSP& getFrameBuffer(const std::string& key) const;

	void addFrameBuffer(const std::string& key, const FrameBufferCubeMapSP& framBufferCubeMap);

	FrameBufferCubeMapSP createFrameBuffer(const std::string& key, std::int32_t width, std::int32_t height);

};

#endif /* FRAMEBUFFERCUBEMAPMANAGER_H_ */

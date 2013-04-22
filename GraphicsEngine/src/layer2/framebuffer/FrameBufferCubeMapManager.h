/*
 * FrameBufferCubeMapManager.h
 *
 *  Created on: 21.04.2013
 *      Author: nopper
 */

#ifndef FRAMEBUFFERCUBEMAPMANAGER_H_
#define FRAMEBUFFERCUBEMAPMANAGER_H_

#include "../../UsedLibs.h"

#include "FrameBufferCubeMap.h"

class FrameBufferCubeMapManager
{
private:

	static FrameBufferCubeMapManager* instance;

	std::map<std::string, FrameBufferCubeMapSP> allFrameBuffers;

	FrameBufferCubeMapManager();
	virtual ~FrameBufferCubeMapManager();

public:

	static FrameBufferCubeMapManager* getInstance();

	static void terminate();

	bool containsFrameBuffer(const std::string& key) const;

	const FrameBufferCubeMapSP& getFrameBuffer(const std::string& key) const;

	void addFrameBuffer(const std::string& key, const FrameBufferCubeMapSP& framBufferCubeMap);

	FrameBufferCubeMapSP createFrameBuffer(const std::string& key, boost::int32_t width, boost::int32_t height);

};

#endif /* FRAMEBUFFERCUBEMAPMANAGER_H_ */

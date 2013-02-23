/*
 * FrameBuffer2DManager.h
 *
 *  Created on: 28.11.2012
 *      Author: nopper
 */

#ifndef FRAMEBUFFER2DMANAGER_H_
#define FRAMEBUFFER2DMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer1/camera/Viewport.h"

#include "FrameBuffer2D.h"

class FrameBuffer2DManager
{
private:

	static FrameBuffer2DManager* instance;

	std::map<std::string, FrameBuffer2DSP> allFrameBuffers;

	std::map<std::string, FrameBuffer2DSP> allWindowFrameBuffers;

	FrameBuffer2DManager();
	virtual ~FrameBuffer2DManager();

public:

	static FrameBuffer2DManager* getInstance();

	static void terminate();

	bool containsFrameBuffer(const std::string& key) const;

	const FrameBuffer2DSP& getFrameBuffer(const std::string& key) const;

	void addFrameBuffer(const std::string& key, const FrameBuffer2DSP& framBuffer2D, bool windowFrameBuffer);

	FrameBuffer2DSP createFrameBuffer(const std::string& key, boost::int32_t width, boost::int32_t height, bool windowFrameBuffer);

	void updateWidthHeight(boost::int32_t width, boost::int32_t height);

};



#endif /* FRAMEBUFFER2DMANAGER_H_ */

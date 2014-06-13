/*
 * FrameBuffer2DManager.h
 *
 *  Created on: 28.11.2012
 *      Author: nopper
 */

#ifndef FRAMEBUFFER2DMANAGER_H_
#define FRAMEBUFFER2DMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "FrameBuffer2D.h"

class FrameBuffer2DManager : public Singleton<FrameBuffer2DManager>
{

	friend class Singleton<FrameBuffer2DManager>;

private:

	KeyValueMap<std::string, FrameBuffer2DSP> allFrameBuffers;

	KeyValueMap<std::string, FrameBuffer2DSP> allWindowFrameBuffers;

	FrameBuffer2DManager();
	virtual ~FrameBuffer2DManager();

public:

	bool containsFrameBuffer(const std::string& key) const;

	const FrameBuffer2DSP& getFrameBuffer(const std::string& key) const;

	void addFrameBuffer(const std::string& key, const FrameBuffer2DSP& framBuffer2D, bool windowFrameBuffer);

	FrameBuffer2DSP createFrameBuffer(const std::string& key, std::int32_t width, std::int32_t height, bool windowFrameBuffer);

	void updateWidthHeight(std::int32_t width, std::int32_t height);

};



#endif /* FRAMEBUFFER2DMANAGER_H_ */

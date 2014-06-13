/*
 * FrameBufferBase.h
 *
 *  Created on: 10.04.2013
 *      Author: nopper
 */

#ifndef FRAMEBUFFERBASE_H_
#define FRAMEBUFFERBASE_H_

#include "../../UsedLibs.h"

class FrameBufferBase
{

protected:

	GLuint fbo;

	std::int32_t width;
	std::int32_t height;

	GLenum drawBufferMode;
	GLenum readBufferMode;

public:
	FrameBufferBase(std::int32_t width, std::int32_t height);
	virtual ~FrameBufferBase();

	virtual bool init() = 0;
	void destroy();
	virtual void use(bool enable) = 0;

	GLuint getFBO() const;

	std::int32_t getWidth() const;
	void setWidth(std::int32_t width);
	std::int32_t getHeight() const;
	void setHeight(std::int32_t height);

	void setWidthHeight(std::int32_t width, std::int32_t height);

	GLenum getDrawBufferMode() const;
	void setDrawBufferMode(GLenum drawBufferMode);
	GLenum getReadBufferMode() const;
	void setReadBufferMode(GLenum readBufferMode);

	bool isValid() const;

};

typedef std::shared_ptr<FrameBufferBase> FrameBufferBaseSP;

#endif /* FRAMEBUFFERBASE_H_ */

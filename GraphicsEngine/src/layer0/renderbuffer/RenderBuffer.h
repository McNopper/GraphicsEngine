/*
 * RenderBuffer.h
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#ifndef RENDERBUFFER_H_
#define RENDERBUFFER_H_

#include "../../UsedLibs.h"

class RenderBuffer
{

protected:

	GLenum internalFormat;

	boost::int32_t width;
	boost::int32_t height;

	GLuint rb;

	bool valid;

public:
	RenderBuffer(GLenum internalFormat, boost::int32_t width, boost::int32_t height);
	virtual ~RenderBuffer();

	virtual bool init();
	void destroy();

	virtual bool isMultisample() const;

	GLenum getInternalFormat() const;
	void setInternalFormat(GLenum internalFormat);

	boost::int32_t getWidth() const;
	void setWidth(boost::int32_t width);
	boost::int32_t getHeight() const;
	void setHeight(boost::int32_t height);

	void setWidthHeight(boost::int32_t width, boost::int32_t height);

	GLuint getRb() const;

	bool isValid() const;
};

typedef boost::shared_ptr<RenderBuffer> RenderBufferSP;

#endif /* RENDERBUFFER_H_ */

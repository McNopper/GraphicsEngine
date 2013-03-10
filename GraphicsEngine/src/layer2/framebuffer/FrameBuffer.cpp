/*
 * FrameBuffer.cpp
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#include "FrameBuffer.h"

using namespace boost;

FrameBuffer::FrameBuffer(int32_t width, int32_t height) :
	fbo(0), width(width), height(height), drawBufferMode(GL_FRONT), readBufferMode(GL_FRONT),
	color0Texture(), color0RenderBuffer(), color1Texture(), color1RenderBuffer(), depthTexture(), depthRenderBuffer(), depthStencilTexture(), depthStencilRenderBuffer()
{
	init();
}

FrameBuffer::~FrameBuffer()
{
	destroy();
}

bool FrameBuffer::init()
{
	if (width < 1 || height < 1)
	{
		return false;
	}

	if (!fbo)
	{
	    glGenFramebuffers(1, &fbo);

	    if (!fbo)
	    {
	    	return false;
	    }
	}
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glDrawBuffer(drawBufferMode);
	glReadBuffer(readBufferMode);

	// Attach textures and render buffers

	if (color0Texture.get())
	{
		color0Texture->setWidthHeight(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color0Texture->getTarget(), color0Texture->getTextureName(), 0);
	}
	else if (color0RenderBuffer.get())
	{
		color0RenderBuffer->setWidthHeight(width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, color0RenderBuffer->getRb());
	}

	if (color1Texture.get())
	{
		color1Texture->setWidthHeight(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, color1Texture->getTarget(), color1Texture->getTextureName(), 0);
	}
	else if (color1RenderBuffer.get())
	{
		color1RenderBuffer->setWidthHeight(width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, color1RenderBuffer->getRb());
	}

	if (depthTexture.get())
	{
		depthTexture->setWidthHeight(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture->getTarget(), depthTexture->getTextureName(), 0);
	}
	else if (depthRenderBuffer.get())
	{
		depthRenderBuffer->setWidthHeight(width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer->getRb());
	}
	else if (depthStencilTexture.get())
	{
		depthStencilTexture->setWidthHeight(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depthStencilTexture->getTarget(), depthStencilTexture->getTextureName(), 0);
	}
	else if (depthStencilRenderBuffer.get())
	{
		depthStencilRenderBuffer->setWidthHeight(width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRenderBuffer->getRb());
	}

	return isValid();
}

void FrameBuffer::destroy()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (fbo)
	{
    	glDeleteFramebuffers(1, &fbo);

	    fbo = 0;
	}
}

void FrameBuffer::use(bool enable)
{
	static const GLenum attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

	if (enable && fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glDrawBuffers(getDrawBuffersCount(), attachments);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDrawBuffers(1, attachments);
	}
}

GLuint FrameBuffer::getFBO() const
{
	return fbo;
}

int32_t FrameBuffer::getDrawBuffersCount() const
{
	int32_t count = 0;

	if (color0Texture.get() || color0RenderBuffer.get())
	{
		count++;
	}
	if (color1Texture.get() || color1RenderBuffer.get())
	{
		count++;
	}

	return count;
}

const TextureSP& FrameBuffer::getColor0Texture() const
{
	return color0Texture;
}

const TextureSP& FrameBuffer::getColor1Texture() const
{
	return color1Texture;
}

const TextureSP& FrameBuffer::getDepthTexture() const
{
	return depthTexture;
}

const TextureSP& FrameBuffer::getDepthStencilTexture() const
{
	return depthStencilTexture;
}

const RenderBufferSP& FrameBuffer::getColor0RenderBuffer() const
{
	return color0RenderBuffer;
}

const RenderBufferSP& FrameBuffer::getColor1RenderBuffer() const
{
	return color1RenderBuffer;
}

const RenderBufferSP& FrameBuffer::getDepthRenderBuffer() const
{
	return depthRenderBuffer;
}

const RenderBufferSP& FrameBuffer::getDepthStencilRenderBuffer() const
{
	return depthStencilRenderBuffer;
}

boost::int32_t FrameBuffer::getWidth() const
{
	return width;
}

void FrameBuffer::setWidth(int32_t width)
{
	if (this->width != width)
	{
		this->width = width;
		destroy();

		init();
	}
}

boost::int32_t FrameBuffer::getHeight() const
{
	return height;
}

void FrameBuffer::setHeight(int32_t height)
{
	if (this->height != height)
	{
		this->height = height;
		destroy();

		init();
	}
}

void FrameBuffer::setWidthHeight(int32_t width, int32_t height)
{
	if (this->width != width || this->height != height)
	{
		this->width = width;
		this->height = height;
		destroy();

		init();
	}
}

GLenum FrameBuffer::getDrawBufferMode() const
{
	return drawBufferMode;
}

void FrameBuffer::setDrawBufferMode(GLenum drawBufferMode)
{
	this->drawBufferMode = drawBufferMode;

	init();
}

GLenum FrameBuffer::getReadBufferMode() const
{
	return readBufferMode;
}

void FrameBuffer::setReadBufferMode(GLenum readBufferMode)
{
	this->readBufferMode = readBufferMode;

	init();
}

bool FrameBuffer::isValid() const
{
	if (!fbo)
	{
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	bool valid = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return valid;
}

void FrameBuffer::setColorAttachment0(const TextureSP& texture)
{
	color0Texture = texture;
	color0RenderBuffer.reset();

	init();
}

void FrameBuffer::setColorAttachment0(const RenderBufferSP& renderBuffer)
{
	color0Texture.reset();
	color0RenderBuffer = renderBuffer;

	init();
}

void FrameBuffer::setColorAttachment1(const TextureSP& texture)
{
	color1Texture = texture;
	color1RenderBuffer.reset();

	init();
}

void FrameBuffer::setColorAttachment1(const RenderBufferSP& renderBuffer)
{
	color1Texture.reset();
	color1RenderBuffer = renderBuffer;

	init();
}

void FrameBuffer::setDepthAttachment(const TextureSP& texture)
{
	depthTexture = texture;
	depthRenderBuffer.reset();
	depthStencilTexture.reset();
	depthStencilRenderBuffer.reset();

	init();
}

void FrameBuffer::setDepthAttachment(const RenderBufferSP& renderBuffer)
{
	depthTexture.reset();
	depthRenderBuffer = renderBuffer;
	depthStencilTexture.reset();
	depthStencilRenderBuffer.reset();

	init();
}


void FrameBuffer::setDepthStencilAttachment(const TextureSP& texture)
{
	depthTexture.reset();
	depthRenderBuffer.reset();
	depthStencilTexture = texture;
	depthStencilRenderBuffer.reset();

	init();
}

void FrameBuffer::setDepthStencilAttachment(const RenderBufferSP& renderBuffer)
{
	depthTexture.reset();
	depthRenderBuffer.reset();
	depthStencilTexture.reset();
	depthStencilRenderBuffer = renderBuffer;

	init();
}


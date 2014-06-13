/*
 * FrameBufferCubeMap.cpp
 *
 *  Created on: 14.04.2013
 *      Author: nopper
 */

#include "FrameBufferCubeMap.h"

using namespace std;

FrameBufferCubeMap::FrameBufferCubeMap(int32_t width, int32_t height) :
		FrameBufferBase(width, height), cubeMapTexture(), depthCubeMapTexture(), depthTexture(), depthRenderBuffer(), depthStencilCubeMapTexture(), depthStencilTexture(), depthStencilRenderBuffer(), activeSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X), enabled(false)
{
	init();
}

FrameBufferCubeMap::~FrameBufferCubeMap()
{
}

bool FrameBufferCubeMap::init()
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

	if (cubeMapTexture.get() && (depthCubeMapTexture.get() || depthStencilCubeMapTexture.get()))
	{
		cubeMapTexture->setWidthHeight(width, height);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cubeMapTexture->getTextureName(), 0);

		//

		if (depthCubeMapTexture.get())
		{
			depthCubeMapTexture->setWidthHeight(width, height);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeMapTexture->getTextureName(), 0);
		}
		else if (depthStencilCubeMapTexture.get())
		{
			depthStencilCubeMapTexture->setWidthHeight(width, height);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depthStencilCubeMapTexture->getTextureName(), 0);
		}
	}
	else if (cubeMapTexture.get() && (depthTexture.get() || depthRenderBuffer.get() || depthStencilTexture.get() || depthStencilRenderBuffer.get()))
	{
		cubeMapTexture->setWidthHeight(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, activeSide, cubeMapTexture->getTextureName(), 0);

		//

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
	}

	return isValid();
}

void FrameBufferCubeMap::use(bool enable)
{
	if (enable && fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	enabled = enable;
}

void FrameBufferCubeMap::setActiveSide(GLenum activeSide)
{
	if (activeSide >= GL_TEXTURE_CUBE_MAP_POSITIVE_X && activeSide <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
	{
		this->activeSide = activeSide;

		if (enabled && isValid() && !renderAtOnce())
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, activeSide, cubeMapTexture->getTextureName(), 0);
		}
	}
}

bool FrameBufferCubeMap::renderAtOnce() const
{
	return depthCubeMapTexture.get() != nullptr || depthStencilCubeMapTexture.get() != nullptr;
}

const TextureCubeMapSP& FrameBufferCubeMap::getCubeMapTexture() const
{
	return cubeMapTexture;
}

const TextureCubeMapSP& FrameBufferCubeMap::getDepthCubeMapTexture() const
{
	return depthCubeMapTexture;
}

const TextureCubeMapSP& FrameBufferCubeMap::getDepthStencilCubeMapTexture() const
{
	return depthStencilCubeMapTexture;
}

const Texture2DSP& FrameBufferCubeMap::getDepthTexture() const
{
	return depthTexture;
}

const Texture2DSP& FrameBufferCubeMap::getDepthStencilTexture() const
{
	return depthStencilTexture;
}

const RenderBufferSP& FrameBufferCubeMap::getDepthRenderBuffer() const
{
	return depthRenderBuffer;
}

const RenderBufferSP& FrameBufferCubeMap::getDepthStencilRenderBuffer() const
{
	return depthStencilRenderBuffer;
}

void FrameBufferCubeMap::setCubeMapAttachment(const TextureCubeMapSP& cubeMapTexture)
{
	this->cubeMapTexture = cubeMapTexture;

	init();
}

void FrameBufferCubeMap::setDepthAttachment(const TextureCubeMapSP& cubeMapTexture)
{
	depthCubeMapTexture = cubeMapTexture;
	depthTexture.reset();
	depthRenderBuffer.reset();

	depthStencilCubeMapTexture.reset();
	depthStencilTexture.reset();
	depthStencilRenderBuffer.reset();

	init();
}

void FrameBufferCubeMap::setDepthStencilAttachment(const TextureCubeMapSP& cubeMapTexture)
{
	depthCubeMapTexture.reset();
	depthTexture.reset();
	depthRenderBuffer.reset();

	depthStencilCubeMapTexture = cubeMapTexture;
	depthStencilTexture.reset();
	depthStencilRenderBuffer.reset();

	init();
}

void FrameBufferCubeMap::setDepthAttachment(const Texture2DSP& texture)
{
	depthCubeMapTexture.reset();
	depthTexture = texture;
	depthRenderBuffer.reset();

	depthStencilCubeMapTexture.reset();
	depthStencilTexture.reset();
	depthStencilRenderBuffer.reset();

	init();
}

void FrameBufferCubeMap::setDepthStencilAttachment(const Texture2DSP& texture)
{
	depthCubeMapTexture.reset();
	depthTexture.reset();
	depthRenderBuffer.reset();

	depthStencilCubeMapTexture.reset();
	depthStencilTexture = texture;
	depthStencilRenderBuffer.reset();

	init();
}

void FrameBufferCubeMap::setDepthAttachment(const RenderBufferSP& renderBuffer)
{
	depthCubeMapTexture.reset();
	depthTexture.reset();
	depthRenderBuffer = renderBuffer;

	depthStencilCubeMapTexture.reset();
	depthStencilTexture.reset();
	depthStencilRenderBuffer.reset();

	init();
}

void FrameBufferCubeMap::setDepthStencilAttachment(const RenderBufferSP& renderBuffer)
{
	depthCubeMapTexture.reset();
	depthTexture.reset();
	depthRenderBuffer.reset();

	depthStencilCubeMapTexture.reset();
	depthStencilTexture.reset();
	depthStencilRenderBuffer = renderBuffer;

	init();
}

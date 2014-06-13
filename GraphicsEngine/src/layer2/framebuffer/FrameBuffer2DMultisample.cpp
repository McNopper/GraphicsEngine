/*
 * FrameBuffer2DMultisample.cpp
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#include "FrameBuffer2DMultisample.h"

using namespace std;

FrameBuffer2DMultisample::FrameBuffer2DMultisample(int32_t width, int32_t height) :
		FrameBuffer(width, height)
{
}

FrameBuffer2DMultisample::~FrameBuffer2DMultisample()
{
}

void FrameBuffer2DMultisample::setColorAttachment0(const TextureSP& texture)
{
	FrameBuffer::setColorAttachment0(texture);
}

void FrameBuffer2DMultisample::setColorAttachment0(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setColorAttachment0(renderBuffer);
}

void FrameBuffer2DMultisample::setColorAttachment1(const TextureSP& texture)
{
	FrameBuffer::setColorAttachment1(texture);
}

void FrameBuffer2DMultisample::setColorAttachment1(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setColorAttachment1(renderBuffer);
}

void FrameBuffer2DMultisample::setDepthAttachment(const TextureSP& texture)
{
	FrameBuffer::setDepthAttachment(texture);
}

void FrameBuffer2DMultisample::setDepthAttachment(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setDepthAttachment(renderBuffer);
}

void FrameBuffer2DMultisample::setDepthStencilAttachment(const TextureSP& texture)
{
	FrameBuffer::setDepthStencilAttachment(texture);
}

void FrameBuffer2DMultisample::setDepthStencilAttachment(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setDepthStencilAttachment(renderBuffer);
}

void FrameBuffer2DMultisample::setColorAttachment0(const Texture2DMultisampleSP& texture2DMultisample)
{
	FrameBuffer::setColorAttachment0(static_cast<TextureSP>(texture2DMultisample));
}

void FrameBuffer2DMultisample::setColorAttachment0(const RenderBufferMultisampleSP& renderBufferMultisample)
{
	FrameBuffer::setColorAttachment0(static_cast<RenderBufferSP>(renderBufferMultisample));
}

void FrameBuffer2DMultisample::setColorAttachment1(const Texture2DMultisampleSP& texture2DMultisample)
{
	FrameBuffer::setColorAttachment1(static_cast<TextureSP>(texture2DMultisample));
}

void FrameBuffer2DMultisample::setColorAttachment1(const RenderBufferMultisampleSP& renderBufferMultisample)
{
	FrameBuffer::setColorAttachment1(static_cast<RenderBufferSP>(renderBufferMultisample));
}

void FrameBuffer2DMultisample::setDepthAttachment(const Texture2DMultisampleSP& texture2DMultisample)
{
	FrameBuffer::setDepthAttachment(static_cast<TextureSP>(texture2DMultisample));
}

void FrameBuffer2DMultisample::setDepthAttachment(const RenderBufferMultisampleSP& renderBufferMultisample)
{
	FrameBuffer::setDepthAttachment(static_cast<RenderBufferSP>(renderBufferMultisample));
}

void FrameBuffer2DMultisample::setDepthStencilAttachment(const Texture2DMultisampleSP& texture2DMultisample)
{
	FrameBuffer::setDepthStencilAttachment(static_cast<TextureSP>(texture2DMultisample));
}

void FrameBuffer2DMultisample::setDepthStencilAttachment(const RenderBufferMultisampleSP& renderBufferMultisample)
{
	FrameBuffer::setDepthStencilAttachment(static_cast<RenderBufferSP>(renderBufferMultisample));
}

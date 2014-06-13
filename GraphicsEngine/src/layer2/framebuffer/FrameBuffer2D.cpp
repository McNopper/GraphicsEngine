/*
 * FrameBuffer2D.cpp
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#include "FrameBuffer2D.h"

using namespace std;

FrameBuffer2D::FrameBuffer2D(int32_t width, int32_t height) :
		FrameBuffer(width, height)
{
}

FrameBuffer2D::~FrameBuffer2D()
{
}

void FrameBuffer2D::setColorAttachment0(const TextureSP& texture)
{
	FrameBuffer::setColorAttachment0(texture);
}

void FrameBuffer2D::setColorAttachment0(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setColorAttachment0(renderBuffer);
}

void FrameBuffer2D::setColorAttachment1(const TextureSP& texture)
{
	FrameBuffer::setColorAttachment1(texture);
}

void FrameBuffer2D::setColorAttachment1(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setColorAttachment1(renderBuffer);
}

void FrameBuffer2D::setDepthAttachment(const TextureSP& texture)
{
	FrameBuffer::setDepthAttachment(texture);
}

void FrameBuffer2D::setDepthAttachment(const TextureSP& texture, int32_t layer)
{
	FrameBuffer::setDepthAttachment(texture, layer);
}

void FrameBuffer2D::setDepthAttachment(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setDepthAttachment(renderBuffer);
}

void FrameBuffer2D::setDepthStencilAttachment(const TextureSP& texture)
{
	FrameBuffer::setDepthStencilAttachment(texture);
}

void FrameBuffer2D::setDepthStencilAttachment(const RenderBufferSP& renderBuffer)
{
	FrameBuffer::setDepthStencilAttachment(renderBuffer);
}

void FrameBuffer2D::setColorAttachment0(const Texture2DSP& texture2D)
{
	FrameBuffer::setColorAttachment0(static_cast<TextureSP>(texture2D));
}

void FrameBuffer2D::setColorAttachment1(const Texture2DSP& texture2D)
{
	FrameBuffer::setColorAttachment1(static_cast<TextureSP>(texture2D));
}

void FrameBuffer2D::setDepthAttachment(const Texture2DSP& texture2D)
{
	FrameBuffer::setDepthAttachment(static_cast<TextureSP>(texture2D));
}

void FrameBuffer2D::setDepthStencilAttachment(const Texture2DSP& texture2D)
{
	FrameBuffer::setDepthStencilAttachment(static_cast<TextureSP>(texture2D));
}

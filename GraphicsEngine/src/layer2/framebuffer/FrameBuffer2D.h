/*
 * FrameBuffer2D.h
 *
 *  Created on: 22.11.2012
 *      Author: nopper
 */

#ifndef FRAMEBUFFER2D_H_
#define FRAMEBUFFER2D_H_

#include "../../UsedLibs.h"

#include "../../layer1/texture/Texture2D.h"
#include "../../layer1/renderbuffer/RenderBuffer.h"

#include "FrameBuffer.h"

class FrameBuffer2D : public FrameBuffer
{

public:

	FrameBuffer2D(std::int32_t width, std::int32_t height);
	virtual ~FrameBuffer2D();

	virtual void setColorAttachment0(const TextureSP& texture);
	virtual void setColorAttachment0(const RenderBufferSP& renderBuffer);

	virtual void setColorAttachment1(const TextureSP& texture);
	virtual void setColorAttachment1(const RenderBufferSP& renderBuffer);

	virtual void setDepthAttachment(const TextureSP& texture);
	virtual void setDepthAttachment(const TextureSP& texture, std::int32_t layer);
	virtual void setDepthAttachment(const RenderBufferSP& renderBuffer);

	virtual void setDepthStencilAttachment(const TextureSP& texture);
	virtual void setDepthStencilAttachment(const RenderBufferSP& renderBuffer);

	virtual void setColorAttachment0(const Texture2DSP& texture2D);

	virtual void setColorAttachment1(const Texture2DSP& texture2D);

	virtual void setDepthAttachment(const Texture2DSP& texture2D);

	virtual void setDepthStencilAttachment(const Texture2DSP& texture2D);

};

typedef std::shared_ptr<FrameBuffer2D> FrameBuffer2DSP;

#endif /* FRAMEBUFFER2D_H_ */

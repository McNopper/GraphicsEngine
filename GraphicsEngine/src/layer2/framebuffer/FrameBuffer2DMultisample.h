/*
 * FrameBuffer2DMultisample.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef FRAMEBUFFER2DMULTISAMPLE_H_
#define FRAMEBUFFER2DMULTISAMPLE_H_

#include "../../UsedLibs.h"

#include "../../layer1/texture/Texture2DMultisample.h"
#include "../../layer1/renderbuffer/RenderBufferMultisample.h"

#include "FrameBuffer.h"

class FrameBuffer2DMultisample : public FrameBuffer
{

public:

	FrameBuffer2DMultisample(std::int32_t width, std::int32_t height);
	virtual ~FrameBuffer2DMultisample();

	virtual void setColorAttachment0(const TextureSP& texture);
	virtual void setColorAttachment0(const RenderBufferSP& renderBuffer);

	virtual void setColorAttachment1(const TextureSP& texture);
	virtual void setColorAttachment1(const RenderBufferSP& renderBuffer);

	virtual void setDepthAttachment(const TextureSP& texture);
	virtual void setDepthAttachment(const RenderBufferSP& renderBuffer);

	virtual void setDepthStencilAttachment(const TextureSP& texture);
	virtual void setDepthStencilAttachment(const RenderBufferSP& renderBuffer);

	virtual void setColorAttachment0(const Texture2DMultisampleSP& texture2DMultisample);
	virtual void setColorAttachment0(const RenderBufferMultisampleSP& renderBufferMultisample);

	virtual void setColorAttachment1(const Texture2DMultisampleSP& texture2DMultisample);
	virtual void setColorAttachment1(const RenderBufferMultisampleSP& renderBufferMultisample);

	virtual void setDepthAttachment(const Texture2DMultisampleSP& texture2DMultisample);
	virtual void setDepthAttachment(const RenderBufferMultisampleSP& renderBufferMultisample);

	virtual void setDepthStencilAttachment(const Texture2DMultisampleSP& texture2DMultisample);
	virtual void setDepthStencilAttachment(const RenderBufferMultisampleSP& renderBufferMultisample);

};

typedef std::shared_ptr<FrameBuffer2DMultisample> FrameBuffer2DMultisampleSP;

#endif /* FRAMEBUFFER2DMULTISAMPLE_H_ */

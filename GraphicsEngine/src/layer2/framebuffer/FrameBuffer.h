/*
 * FrameBuffer.h
 *
 *  Created on: 05.02.2013
 *      Author: nopper
 */

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include "../../layer0/texture/Texture.h"
#include "../../layer0/renderbuffer/RenderBuffer.h"

#include "FrameBufferBase.h"

class FrameBuffer : public FrameBufferBase
{

private:

	TextureSP color0Texture;
	RenderBufferSP color0RenderBuffer;

	TextureSP color1Texture;
	RenderBufferSP color1RenderBuffer;

	TextureSP depthTexture;
	RenderBufferSP depthRenderBuffer;

	TextureSP depthStencilTexture;
	RenderBufferSP depthStencilRenderBuffer;

	boost::int32_t getDrawBuffersCount() const;

public:

	FrameBuffer(boost::int32_t width, boost::int32_t height);
	virtual ~FrameBuffer();

	virtual bool init();

	virtual void use(bool enable);

	virtual void setColorAttachment0(const TextureSP& texture);
	virtual void setColorAttachment0(const RenderBufferSP& renderBuffer);

	virtual void setColorAttachment1(const TextureSP& texture);
	virtual void setColorAttachment1(const RenderBufferSP& renderBuffer);

	virtual void setDepthAttachment(const TextureSP& texture);
	virtual void setDepthAttachment(const RenderBufferSP& renderBuffer);

	virtual void setDepthStencilAttachment(const TextureSP& texture);
	virtual void setDepthStencilAttachment(const RenderBufferSP& renderBuffer);

	const RenderBufferSP& getColor0RenderBuffer() const;
	const TextureSP& getColor0Texture() const;
	const RenderBufferSP& getColor1RenderBuffer() const;
	const TextureSP& getColor1Texture() const;
	const RenderBufferSP& getDepthRenderBuffer() const;
	const TextureSP& getDepthTexture() const;
	const RenderBufferSP& getDepthStencilRenderBuffer() const;
	const TextureSP& getDepthStencilTexture() const;

};

typedef boost::shared_ptr<FrameBuffer> FrameBufferSP;

#endif /* FRAMEBUFFER_H_ */

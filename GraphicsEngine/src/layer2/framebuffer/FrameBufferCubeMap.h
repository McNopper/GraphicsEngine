/*
 * FrameBufferCubeMap.h
 *
 *  Created on: 14.04.2013
 *      Author: nopper
 */

#ifndef FRAMEBUFFERCUBEMAP_H_
#define FRAMEBUFFERCUBEMAP_H_

#include "../../layer0/renderbuffer/RenderBuffer.h"
#include "../../layer0/texture/Texture2D.h"
#include "../../layer0/texture/TextureCubeMap.h"

#include "FrameBufferBase.h"

class FrameBufferCubeMap : public FrameBufferBase
{

private:

	TextureCubeMapSP cubeMapTexture;

	TextureCubeMapSP depthCubeMapTexture;
	Texture2DSP depthTexture;
	RenderBufferSP depthRenderBuffer;

	TextureCubeMapSP depthStencilCubeMapTexture;
	Texture2DSP depthStencilTexture;
	RenderBufferSP depthStencilRenderBuffer;

	GLenum activeSide;

	bool enabled;

public:
	FrameBufferCubeMap(boost::int32_t width, boost::int32_t height);
	virtual ~FrameBufferCubeMap();

	virtual bool init();
	virtual void use(bool enable);
	void setActiveSide(GLenum side);

	bool renderAtOnce() const;

	void setCubeMapAttachment(const TextureCubeMapSP& cubeMapTexture);

	void setDepthAttachment(const TextureCubeMapSP& cubeMapTexture);
	void setDepthAttachment(const Texture2DSP& texture);
	void setDepthAttachment(const RenderBufferSP& renderBuffer);

	void setDepthStencilAttachment(const TextureCubeMapSP& cubeMapTexture);
	void setDepthStencilAttachment(const Texture2DSP& texture);
	void setDepthStencilAttachment(const RenderBufferSP& renderBuffer);

	const TextureCubeMapSP& getCubeMapTexture() const;

	const TextureCubeMapSP& getDepthCubeMapTexture() const;
	const Texture2DSP& getDepthTexture() const;
	const RenderBufferSP& getDepthRenderBuffer() const;

	const TextureCubeMapSP& getDepthStencilCubeMapTexture() const;
	const Texture2DSP& getDepthStencilTexture() const;
	const RenderBufferSP& getDepthStencilRenderBuffer() const;

};

#endif /* FRAMEBUFFERCUBEMAP_H_ */

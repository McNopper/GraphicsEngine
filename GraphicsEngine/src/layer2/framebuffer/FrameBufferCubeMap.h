/*
 * FrameBufferCubeMap.h
 *
 *  Created on: 14.04.2013
 *      Author: nopper
 */

#ifndef FRAMEBUFFERCUBEMAP_H_
#define FRAMEBUFFERCUBEMAP_H_

#include "../../layer1/renderbuffer/RenderBuffer.h"
#include "../../layer1/texture/Texture2D.h"
#include "../../layer1/texture/TextureCubeMap.h"

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
	FrameBufferCubeMap(std::int32_t width, std::int32_t height);
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

typedef std::shared_ptr<FrameBufferCubeMap> FrameBufferCubeMapSP;

#endif /* FRAMEBUFFERCUBEMAP_H_ */

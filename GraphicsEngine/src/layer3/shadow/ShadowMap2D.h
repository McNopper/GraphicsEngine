/*
 * ShadowMap2S.h
 *
 *  Created on: 06.06.2013
 *      Author: nopper
 */

#ifndef SHADOWMAP2D_H_
#define SHADOWMAP2D_H_

#include "../../UsedLibs.h"

#include "../../layer1/texture/Texture2DArray.h"
#include "../../layer2/framebuffer/FrameBuffer2D.h"

class ShadowMap2D
{

private:

	std::int32_t size;

	Texture2DArraySP depthTexture2D;

	std::vector<FrameBuffer2DSP> allShadowMaps;

public:

	ShadowMap2D(std::int32_t size, std::int32_t number);

	virtual ~ShadowMap2D();

	bool use(bool enable, std::int32_t element) const;

	GLuint getDepthTextureName() const;

	std::int32_t getSize() const;

};

typedef std::shared_ptr<ShadowMap2D> ShadowMap2DSP;

#endif /* SHADOWMAP2D_H_ */

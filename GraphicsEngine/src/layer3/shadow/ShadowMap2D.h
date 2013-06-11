/*
 * ShadowMap2S.h
 *
 *  Created on: 06.06.2013
 *      Author: nopper
 */

#ifndef SHADOWMAP2D_H_
#define SHADOWMAP2D_H_

#include "../../UsedLibs.h"

#include "../../layer2/framebuffer/FrameBuffer2D.h"

class ShadowMap2D
{

private:

	boost::int32_t size;

	std::vector<FrameBuffer2DSP> allShadowMaps;

public:

	ShadowMap2D(boost::int32_t size, boost::int32_t number);

	virtual ~ShadowMap2D();

	bool use(bool enable, boost::int32_t element) const;

	GLuint getDepthTextureName(boost::int32_t element) const;

	boost::int32_t getSize() const;

};

typedef boost::shared_ptr<ShadowMap2D> ShadowMap2DSP;

#endif /* SHADOWMAP2D_H_ */

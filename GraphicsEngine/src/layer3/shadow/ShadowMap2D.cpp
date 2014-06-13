/*
 * ShadowMap2D.cpp
 *
 *  Created on: 06.06.2013
 *      Author: nopper
 */

#include "../../layer1/texture/Texture2DArrayManager.h"
#include "../../layer2/framebuffer/FrameBuffer2DManager.h"

#include "ShadowMap2D.h"

using namespace std;

ShadowMap2D::ShadowMap2D(int32_t size, int32_t number) :
		size(size)
{
	char buffer[256];
	sprintf(buffer, "%p", this);
	string uniqueID(buffer);

	if (size < 1 || number < 1)
	{
		return;
	}

	depthTexture2D = Texture2DArrayManager::getInstance()->createTexture("ShadowMap" + uniqueID, GL_DEPTH_COMPONENT, size, size, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, false, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	for (int32_t i = 0; i < number; i++)
	{
		depthTexture2D->addPixelData(PixelDataSP(new PixelData(size, size, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0, 0)));
	}

	depthTexture2D->init();

	glBindTexture(GL_TEXTURE_2D_ARRAY, depthTexture2D->getTextureName());

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	for (int32_t i = 0; i < number; i++)
	{
		FrameBuffer2DSP depthFramebuffer2D = FrameBuffer2DManager::getInstance()->createFrameBuffer("ShadowMap" + uniqueID + "-" + to_string(i), size, size, false);

		depthFramebuffer2D->setDrawBufferMode(GL_NONE);
		depthFramebuffer2D->setReadBufferMode(GL_NONE);

		depthFramebuffer2D->setDepthAttachment(depthTexture2D, i);

		depthFramebuffer2D->init();

		assert(depthFramebuffer2D->isValid());

		allShadowMaps.push_back(depthFramebuffer2D);
	}
}

ShadowMap2D::~ShadowMap2D()
{
	depthTexture2D.reset();
	allShadowMaps.clear();
}

bool ShadowMap2D::use(bool enable, int32_t element) const
{
	if (element < 0 || element >= static_cast<int32_t>(allShadowMaps.size()))
	{
		return false;
	}

	allShadowMaps[element]->use(enable);

	return true;
}

GLuint ShadowMap2D::getDepthTextureName() const
{
	return depthTexture2D->getTextureName();
}

int32_t ShadowMap2D::getSize() const
{
	return size;
}

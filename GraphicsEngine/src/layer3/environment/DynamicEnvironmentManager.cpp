/*
 * DynamicEnvironmentManager.cpp
 *
 *  Created on: 21.04.2013
 *      Author: nopper
 */

#include "../../layer0/texture/TextureCubeMap.h"
#include "../../layer0/texture/TextureFactory.h"
#include "../../layer2/framebuffer/FrameBufferCubeMapManager.h"

#include "DynamicEnvironmentManager.h"

using namespace boost;

using namespace std;

DynamicEnvironmentManager::DynamicEnvironmentManager() :
		Manager<EntitySP, FrameBufferCubeMapSP>()
{
}

DynamicEnvironmentManager::~DynamicEnvironmentManager()
{
}

FrameBufferCubeMapSP DynamicEnvironmentManager::createCubeMap(const EntitySP& entity, int32_t length)
{
	FrameBufferCubeMapSP result = findElement(entity);

	if (result.get())
	{
		return result;
	}

	char buffer[256];
	sprintf(buffer, "%p", entity.get());
	string uniqueID(buffer);

	result = FrameBufferCubeMapManager::getInstance()->createFrameBuffer("DynamicEnvironment" + uniqueID, length, length);

	TextureFactory textureFactory;

	TextureCubeMapSP color = textureFactory.createTextureCubeMap(length, length, GL_RGBA, GL_UNSIGNED_BYTE);
	result->setCubeMapAttachment(color);

	TextureCubeMapSP depth = textureFactory.createTextureCubeMap(length, length, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);
	result->setDepthAttachment(depth);

	return result;
}

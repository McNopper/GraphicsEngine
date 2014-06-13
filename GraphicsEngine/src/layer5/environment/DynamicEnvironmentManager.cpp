/*
 * DynamicEnvironmentManager.cpp
 *
 *  Created on: 21.04.2013
 *      Author: nopper
 */

#include "../../layer1/texture/TextureCubeMap.h"
#include "../../layer1/texture/TextureFactory.h"
#include "../../layer2/framebuffer/FrameBufferCubeMapManager.h"

#include "DynamicEnvironmentManager.h"

using namespace std;

DynamicEnvironmentManager::DynamicEnvironmentManager() :
		Singleton<DynamicEnvironmentManager>(), allDynamicEnvironments()
{
}

DynamicEnvironmentManager::~DynamicEnvironmentManager()
{
}

FrameBufferCubeMapSP DynamicEnvironmentManager::createCubeMap(const EntitySP& entity, int32_t length)
{
	DynamicEnvironmentSP dynamicEnvironment = allDynamicEnvironments.search(entity);

	if (dynamicEnvironment.get())
	{
		return dynamicEnvironment->getFrameBufferCubeMap();
	}

	char buffer[256];
	sprintf(buffer, "%p", entity.get());
	string uniqueID(buffer);

	FrameBufferCubeMapSP result = FrameBufferCubeMapManager::getInstance()->createFrameBuffer("DynamicEnvironment" + uniqueID, length, length);

	TextureFactory textureFactory;

	TextureCubeMapSP color = textureFactory.createTextureCubeMap("DynamicEnvironmentColor" + uniqueID, length, length, GL_RGBA, GL_UNSIGNED_BYTE);
	result->setCubeMapAttachment(color);

	TextureCubeMapSP depth = textureFactory.createTextureCubeMap("DynamicEnvironmentDepth" + uniqueID, length, length, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);
	result->setDepthAttachment(depth);

	dynamicEnvironment = DynamicEnvironmentSP(new DynamicEnvironment(entity->getBoundingSphere().getCenter(), result));

	allDynamicEnvironments.add(entity, dynamicEnvironment);

	return result;
}

const KeyValueMap<EntitySP, DynamicEnvironmentSP>& DynamicEnvironmentManager::getKeyValueMap() const
{
	return allDynamicEnvironments;
}

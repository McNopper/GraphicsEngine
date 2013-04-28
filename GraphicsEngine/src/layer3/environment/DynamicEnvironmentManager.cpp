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

DynamicEnvironmentManager* DynamicEnvironmentManager::instance = nullptr;

DynamicEnvironmentManager::DynamicEnvironmentManager() :
		Manager<EntitySP, DynamicEnvironmentSP>()
{
}

DynamicEnvironmentManager::~DynamicEnvironmentManager()
{
}

DynamicEnvironmentManager* DynamicEnvironmentManager::getInstance()
{
	if (!instance)
	{
		instance = new DynamicEnvironmentManager();
	}

	return instance;
}

void DynamicEnvironmentManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

FrameBufferCubeMapSP DynamicEnvironmentManager::createCubeMap(const EntitySP& entity, int32_t length)
{
	DynamicEnvironmentSP dynamicEnvironment = findElement(entity);

	if (dynamicEnvironment.get())
	{
		return dynamicEnvironment->getFrameBufferCubeMap();
	}

	char buffer[256];
	sprintf(buffer, "%p", entity.get());
	string uniqueID(buffer);

	FrameBufferCubeMapSP result = FrameBufferCubeMapManager::getInstance()->createFrameBuffer("DynamicEnvironment" + uniqueID, length, length);

	TextureFactory textureFactory;

	TextureCubeMapSP color = textureFactory.createTextureCubeMap(length, length, GL_RGBA, GL_UNSIGNED_BYTE);
	result->setCubeMapAttachment(color);

	TextureCubeMapSP depth = textureFactory.createTextureCubeMap(length, length, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);
	result->setDepthAttachment(depth);

	dynamicEnvironment = DynamicEnvironmentSP(new DynamicEnvironment(entity->getBoundingSphere().getCenter(), result));

	addElement(entity, dynamicEnvironment);

	return result;
}

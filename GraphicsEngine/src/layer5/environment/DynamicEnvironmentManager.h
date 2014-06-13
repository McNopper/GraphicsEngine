/*
 * DynamicEnvironmentManager.h
 *
 *  Created on: 21.04.2013
 *      Author: nopper
 */

#ifndef DYNAMICENVIRONMENTMANAGER_H_
#define DYNAMICENVIRONMENTMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"
#include "../../layer2/framebuffer/FrameBufferCubeMap.h"
#include "../../layer3/camera/PerspectiveCamera.h"
#include "../../layer4/entity/Entity.h"

#include "DynamicEnvironment.h"

class DynamicEnvironmentManager : public Singleton<DynamicEnvironmentManager>
{

	friend class Singleton<DynamicEnvironmentManager>;

protected:

	KeyValueMap<EntitySP, DynamicEnvironmentSP> allDynamicEnvironments;

	DynamicEnvironmentManager();
	virtual ~DynamicEnvironmentManager();

public:

	FrameBufferCubeMapSP createCubeMap(const EntitySP& entity, std::int32_t length);

	const KeyValueMap<EntitySP, DynamicEnvironmentSP>& getKeyValueMap() const;

};

#endif /* DYNAMICENVIRONMENTMANAGER_H_ */

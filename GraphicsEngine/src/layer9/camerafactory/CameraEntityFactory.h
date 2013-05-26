/*
 * CameraEntityFactory.h
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#ifndef CAMERAENTITYFACTORY_H_
#define CAMERAENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer3/camera/Camera.h"
#include "../../layer8/modelentity/ModelEntity.h"

class CameraEntityFactory
{
public:
	CameraEntityFactory();
	virtual ~CameraEntityFactory();

	ModelEntitySP createCameraEntity(const std::string& name, const CameraSP& camera);

	ModelEntitySP createCameraEntity(const std::string& name, const CameraSP& camera, const std::vector<AnimationStackSP>& allAnimStacks);

};

#endif /* CAMERAENTITYFACTORY_H_ */

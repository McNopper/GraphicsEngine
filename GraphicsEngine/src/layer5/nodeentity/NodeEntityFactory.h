/*
 * LightEntityFactory.h
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#ifndef NODEENTITYFACTORY_H_
#define NODEENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer1/light/Light.h"
#include "../../layer5/nodeentity/NodeEntity.h"

class NodeEntityFactory
{
public:
	NodeEntityFactory();
	virtual ~NodeEntityFactory();

	NodeEntitySP createLightEntity(const std::string& name, const LightSP& light);

	NodeEntitySP createLightEntity(const std::string& name, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);

	NodeEntitySP createCameraEntity(const std::string& name, const CameraSP& camera);

	NodeEntitySP createCameraEntity(const std::string& name, const CameraSP& camera, const std::vector<AnimationStackSP>& allAnimStacks);

};

#endif /* NODEENTITYFACTORY_H_ */

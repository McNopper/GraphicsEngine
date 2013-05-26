/*
 * LightEntityFactory.h
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#ifndef LIGHTENTITYFACTORY_H_
#define LIGHTENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer3/light/Light.h"
#include "../../layer8/modelentity/ModelEntity.h"

class LightEntityFactory
{

public:

	LightEntityFactory();
	virtual ~LightEntityFactory();

	ModelEntitySP createLightEntity(const std::string& name, const LightSP& light);

	ModelEntitySP createLightEntity(const std::string& name, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);

};

#endif /* LIGHTENTITYFACTORY_H_ */

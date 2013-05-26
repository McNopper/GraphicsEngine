/*
 * GroundEntityFactory.h
 *
 *  Created on: 18.05.2013
 *      Author: nopper
 */

#ifndef GROUNDENTITYFACTORY_H_
#define GROUNDENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer8/groundentity/GroundEntity.h"

class GroundEntityFactory
{

public:

	GroundEntityFactory();
	virtual ~GroundEntityFactory();

	GroundEntitySP createGroundEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

};

#endif /* GROUNDENTITYFACTORY_H_ */

/*
 * PrimitiveEntityFactory.h
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#ifndef PRIMITIVEENTITYFACTORY_H_
#define PRIMITIVEENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer3/animation/AnimationStack.h"
#include "../../layer8/modelentity/ModelEntity.h"

class PrimitiveEntityFactory
{

public:

	PrimitiveEntityFactory();
	virtual ~PrimitiveEntityFactory();

	ModelEntitySP createCubePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createCubePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createSpherePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createSpherePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createDomePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createDomePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createTorusPrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createTorusPrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createConePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createConePrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createCylinderPrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createCylinderPrimitiveEntity(const std::string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

};

#endif /* PRIMITIVEENTITYFACTORY_H_ */

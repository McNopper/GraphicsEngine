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
#include "../../layer1/material/SurfaceMaterial.h"
#include "../../layer2/animation/AnimationStack.h"
#include "../../layer5/modelentity/ModelEntity.h"

class PrimitiveEntityFactory
{

public:

	PrimitiveEntityFactory();
	virtual ~PrimitiveEntityFactory();

	ModelEntitySP createCubePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createCubePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createSpherePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createSpherePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createDomePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createDomePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createTorusPrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createTorusPrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createConePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createConePrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelEntitySP createCylinderPrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelEntitySP createCylinderPrimitiveEntity(float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

};

#endif /* PRIMITIVEENTITYFACTORY_H_ */

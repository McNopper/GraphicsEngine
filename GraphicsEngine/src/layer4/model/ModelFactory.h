/*
 * ModelFactory.h
 *
 *  Created on: 04.09.2012
 *      Author: nopper
 */

#ifndef MODELFACTORY_H_
#define MODELFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer1/collision/BoundingSphere.h"
#include "../../layer1/material/SurfaceMaterial.h"
#include "../../layer2/animation/AnimationStack.h"
#include "Model.h"

class ModelFactory
{

public:

	ModelFactory();
	virtual ~ModelFactory();

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

};

#endif /* MODELFACTORY_H_ */

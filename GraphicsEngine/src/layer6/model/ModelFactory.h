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
#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer3/animation/AnimationStack.h"
#include "../../layer3/camera/Camera.h"
#include "../../layer3/light/Light.h"
#include "Model.h"

class ModelFactory
{

public:

	ModelFactory();
	virtual ~ModelFactory();

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const CameraSP& camera) const;

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const CameraSP& camera, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const LightSP& light) const;

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks) const;

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial) const;

	ModelSP createModel(const std::string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial, const std::vector<AnimationStackSP>& allAnimStacks) const;

};

#endif /* MODELFACTORY_H_ */

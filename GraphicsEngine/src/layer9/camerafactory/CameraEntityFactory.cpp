/*
 * CameraEntityFactory.cpp
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#include "../../layer6/model/ModelFactory.h"

#include "CameraEntityFactory.h"

using namespace std;

CameraEntityFactory::CameraEntityFactory()
{
}

CameraEntityFactory::~CameraEntityFactory()
{
}

ModelEntitySP CameraEntityFactory::createCameraEntity(const string& name, const CameraSP& camera)
{
	vector<AnimationStackSP> allAnimStacks;

	ModelFactory modelFactory;

	ModelSP model = modelFactory.createModel(name, BoundingSphere(Point4(), Camera::getDebugRadius()), camera);

	ModelEntitySP modelEntity = ModelEntitySP(new ModelEntity(name, model, 1.0f, 1.0f, 1.0f));

	return modelEntity;
}

ModelEntitySP CameraEntityFactory::createCameraEntity(const string& name, const CameraSP& camera, const vector<AnimationStackSP>& allAnimStacks)
{
	ModelFactory modelFactory;

	ModelSP model = modelFactory.createModel(name, BoundingSphere(Point4(), Camera::getDebugRadius()), camera, allAnimStacks);

	ModelEntitySP modelEntity = ModelEntitySP(new ModelEntity(name, model, 1.0f, 1.0f, 1.0f));

	return modelEntity;
}

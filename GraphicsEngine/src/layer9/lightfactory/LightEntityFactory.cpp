/*
 * LightEntityFactory.cpp
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#include "../../layer6/model/ModelFactory.h"

#include "LightEntityFactory.h"

using namespace std;

LightEntityFactory::LightEntityFactory()
{
}

LightEntityFactory::~LightEntityFactory()
{
}

ModelEntitySP LightEntityFactory::createLightEntity(const string& name, const LightSP& light)
{
	vector<AnimationStackSP> allAnimStacks;

	ModelFactory modelFactory;

	ModelSP model = modelFactory.createModel(name, BoundingSphere(Point4(), Light::getDebugRadius()), light);

	ModelEntitySP modelEntity = ModelEntitySP(new ModelEntity(name, model, 1.0f, 1.0f, 1.0f));

	return modelEntity;
}

ModelEntitySP LightEntityFactory::createLightEntity(const string& name, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks)
{
	ModelFactory modelFactory;

	ModelSP model = modelFactory.createModel(name, BoundingSphere(Point4(), Light::getDebugRadius()), light, allAnimStacks);

	ModelEntitySP modelEntity = ModelEntitySP(new ModelEntity(name, model, 1.0f, 1.0f, 1.0f));

	return modelEntity;
}

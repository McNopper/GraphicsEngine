/*
 * PrimitiveEntityFactory.cpp
 *
 *  Created on: 28.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer6/model/Model.h"
#include "../../layer6/model/ModelFactory.h"

#include "PrimitiveEntityFactory.h"

using namespace std;

PrimitiveEntityFactory::PrimitiveEntityFactory()
{
}

PrimitiveEntityFactory::~PrimitiveEntityFactory()
{
}

ModelEntitySP PrimitiveEntityFactory::createCubePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float halfExtend = 0.5f;

	glusShapeCreateCubef(&shape, halfExtend);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(glusMathLengthf(halfExtend, halfExtend, halfExtend));

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createCubePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float halfExtend = 0.5f;

	glusShapeCreateCubef(&shape, halfExtend);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(glusMathLengthf(halfExtend, halfExtend, halfExtend));

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial, allAnimStacks), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createSpherePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float radius = 0.5f;

	uint32_t numberSlices = 32;

	glusShapeCreateSpheref(&shape, radius, numberSlices);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(radius);

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createSpherePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float radius = 0.5f;

	uint32_t numberSlices = 32;

	glusShapeCreateSpheref(&shape, radius, numberSlices);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(radius);

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial, allAnimStacks), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createDomePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float radius = 0.5f;

	uint32_t numberSlices = 32;

	glusShapeCreateDomef(&shape, radius, numberSlices);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(radius);

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createDomePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float radius = 0.5f;

	uint32_t numberSlices = 32;

	glusShapeCreateDomef(&shape, radius, numberSlices);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(radius);

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial, allAnimStacks), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createTorusPrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float innerRadius = 0.25f;
	float outerRadius = 0.5f;
	uint32_t numberSlices = 32;
	uint32_t numberStacks = 32;

	glusShapeCreateTorusf(&shape, innerRadius, outerRadius, numberSlices, numberStacks);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(outerRadius);

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createTorusPrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float innerRadius = 0.25f;
	float outerRadius = 0.5f;
	uint32_t numberSlices = 32;
	uint32_t numberStacks = 32;

	glusShapeCreateTorusf(&shape, innerRadius, outerRadius, numberSlices, numberStacks);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(outerRadius);

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial, allAnimStacks), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createConePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float halfExtend = 0.5f;
	float radius = 0.5f;
	uint32_t numberSlices = 32;
	uint32_t numberStacks = 32;

	glusShapeCreateConef(&shape, halfExtend, radius, numberSlices, numberStacks);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(glusMathLengthf(halfExtend, radius, 0.0f));

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createConePrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float halfExtend = 0.5f;
	float radius = 0.5f;
	uint32_t numberSlices = 32;
	uint32_t numberStacks = 32;

	glusShapeCreateConef(&shape, halfExtend, radius, numberSlices, numberStacks);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(glusMathLengthf(halfExtend, radius, 0.0f));

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial, allAnimStacks), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createCylinderPrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float halfExtend = 0.5f;
	float radius = 0.5f;
	uint32_t numberSlices = 32;

	glusShapeCreateCylinderf(&shape, halfExtend, radius, numberSlices);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(glusMathLengthf(halfExtend, radius, 0.0f));

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial), scaleX, scaleY, scaleZ));
}

ModelEntitySP PrimitiveEntityFactory::createCylinderPrimitiveEntity(const string& name, float scaleX, float scaleY, float scaleZ, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	ModelFactory modelFactory;

	GLUSshape shape;

	float halfExtend = 0.5f;
	float radius = 0.5f;
	uint32_t numberSlices = 32;

	glusShapeCreateCylinderf(&shape, halfExtend, radius, numberSlices);

	BoundingSphere boundingSphere;

	boundingSphere.setRadius(glusMathLengthf(halfExtend, radius, 0.0f));

	return ModelEntitySP(new ModelEntity(name, modelFactory.createModel(name, boundingSphere, shape, surfaceMaterial, allAnimStacks), scaleX, scaleY, scaleZ));
}

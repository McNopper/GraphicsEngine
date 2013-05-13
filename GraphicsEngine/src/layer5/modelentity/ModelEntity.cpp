/*
 * ModelEntity.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/debug/DebugDraw.h"
#include "../../layer1/event/EventManager.h"
#include "../../layer1/material/RefractiveIndices.h"

#include "ModelEntity.h"

using namespace std;

using namespace boost;

const string& ModelEntity::getCurrentProgramType() const
{
	return GeneralEntity::currentProgramType;
}

int32_t ModelEntity::getNumberJoints() const
{
	return model->getNumberJoints();
}

ModelEntity::ModelEntity(const string& name, const ModelSP& model, float scaleX, float scaleY, float scaleZ) :
	GeneralEntity(name, scaleX, scaleY, scaleZ), NodeOwner(), writeBrightColor(false), brightColorLimit(1.0f), refractiveIndex(RI_AIR), model(model), time(0.0f), animStackIndex(-1), animLayerIndex(-1), rootInstanceNode(), jointIndex(-1)
{
	float maxScale = glusMaxf(scaleX, scaleY);
	maxScale = glusMaxf(maxScale, scaleZ);

	setBoundingSphere(BoundingSphere(model->getBoundingSphere().getCenter(), model->getBoundingSphere().getRadius() * maxScale));

	setUpdateable(model->isAnimated());

	if (model->isAnimated() && model->isSkinned())
	{
		jointIndex = model->getRootNode()->getSkinningRootIndex();

		model->getRootNode()->updateBindMatrix(bindMatrices, bindNormalMatrices);
		model->getRootNode()->updateJointMatrix(jointMatrices, jointNormalMatrices, Matrix4x4(), 0.0f, getAnimStackIndex(), getAnimLayerIndex());
	}

	rootInstanceNode = InstanceNodeSP(new InstanceNode(model->getRootNode()->getName()));
	model->getRootNode()->updateInstanceNode(rootInstanceNode);

	updateBoundingSphereCenter(true);
}

ModelEntity::~ModelEntity()
{
}

void ModelEntity::setAnimation(int32_t animStackIndex, int32_t animLayerIndex) {
	this->animStackIndex = animStackIndex;
	this->animLayerIndex = animLayerIndex;
}

int32_t ModelEntity::getAnimStackIndex() const {
	return animStackIndex;
}

int32_t ModelEntity::getAnimLayerIndex() const {
	return animLayerIndex;
}

void ModelEntity::updateBoundingSphereCenter(bool force)
{
	bool doUpdateBoundingSphereCenter = force;

	if (model->isAnimated())
	{
		doUpdateBoundingSphereCenter = true;
	}

	if (doUpdateBoundingSphereCenter)
	{
		Matrix4x4 skinningMatrix;
		if (model->isSkinned())
		{
			skinningMatrix = jointMatrices[jointIndex] * bindMatrices[jointIndex];
		}

		Matrix4x4 renderingMatrix;
		model->getRootNode()->updateRenderingMatrix(renderingMatrix, getModelMatrix(), time, getAnimStackIndex(), getAnimLayerIndex());

		Point4 center = renderingMatrix * skinningMatrix * Point4();

		setBoundingSphereCenter(center);
	}
}

void ModelEntity::update()
{
	if (model->isAnimated())
	{
		time += ModelEntity::currentDeltaTime;

		float stopTime = model->getRootNode()->getStopTime(getAnimStackIndex(), getAnimLayerIndex());
		if (time > stopTime)
		{
			time -= stopTime;
		}

		// Calculate skinning and pass later to shader
		if (model->isSkinned() && getAnimStackIndex() >= 0 && getAnimLayerIndex() >= 0)
		{
			model->getRootNode()->updateJointMatrix(jointMatrices, jointNormalMatrices, Matrix4x4(), time, getAnimStackIndex(), getAnimLayerIndex());
		}
	}
}

void ModelEntity::render() const
{
	model->getRootNode()->render(*this, *rootInstanceNode, getModelMatrix(), time, getAnimStackIndex(), getAnimLayerIndex());

	if (isDebug())
	{
		DebugDraw::drawer.draw(getBoundingSphere(), Color::RED, isDebugAsMesh());
	}
}

const Matrix4x4* ModelEntity::getBindMatrices() const {
	return bindMatrices;
}

const Matrix3x3* ModelEntity::getBindNormalMatrices() const {
	return bindNormalMatrices;
}

const Matrix4x4* ModelEntity::getJointMatrices() const {
	return jointMatrices;
}

const Matrix3x3* ModelEntity::getJointNormalMatrices() const {
	return jointNormalMatrices;
}

bool ModelEntity::isWriteBrightColor() const
{
	return writeBrightColor;
}

float ModelEntity::getBrightColorLimit() const
{
	return brightColorLimit;
}

float ModelEntity::getRefractiveIndex() const
{
	return refractiveIndex;
}

void ModelEntity::setWriteBrightColor(bool writeBrightColor)
{
	this->writeBrightColor = writeBrightColor;
}

void ModelEntity::setBrightColorLimit(float brightColorLimit)
{
	this->brightColorLimit = brightColorLimit;
}

void ModelEntity::setRefractiveIndex(float refractiveIndex)
{
	this->refractiveIndex = refractiveIndex;
}

const ModelSP& ModelEntity::getModel() const
{
	return model;
}

const InstanceNodeSP& ModelEntity::getRootInstanceNode() const
{
	return rootInstanceNode;
}

InstanceNodeSP ModelEntity::findInstanceNodeRecursive(const string& name) const
{
	return rootInstanceNode->findChildRecursive(name);
}

ModelEntitySP ModelEntity::getNewInstance(const string& name) const
{
	return ModelEntitySP(new ModelEntity(name, model, getScaleX(), getScaleY(), getScaleZ()));
}

/*
 * NodeEntity.cpp
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#include "NodeEntity.h"

using namespace std;

using namespace boost;

NodeEntity::NodeEntity(const std::string& name, const NodeSP& rootNode, float scaleX, float scaleY, float scaleZ, bool updateable) :
		GeneralEntity(name, scaleX, scaleY, scaleZ), NodeOwner(), rootNode(rootNode), time(0.0f), animStackIndex(-1), animLayerIndex(-1), dirty(true)
{
	setUpdateable(updateable);

	setBoundingSphere(BoundingSphere(getPosition(), 0.0f));

	this->rootInstanceNode = InstanceNodeSP(new InstanceNode(this->rootNode->getName()));
	this->rootNode->updateInstanceNode(this->rootInstanceNode);

	updateBoundingSphereCenter(true);
}

NodeEntity::~NodeEntity()
{
	rootInstanceNode.reset();
	rootNode.reset();
}

void NodeEntity::setAnimation(int32_t animStackIndex, int32_t animLayerIndex) {
	this->animStackIndex = animStackIndex;
	this->animLayerIndex = animLayerIndex;
}

int32_t NodeEntity::getAnimStackIndex() const {
	return animStackIndex;
}

int32_t NodeEntity::getAnimLayerIndex() const {
	return animLayerIndex;
}

void NodeEntity::updateBoundingSphereCenter(bool force)
{
	setBoundingSphereCenter(getPosition());
}

void NodeEntity::update()
{
	if (isUpdateable())
	{
		time += GeneralEntity::currentDeltaTime;

		float stopTime = rootNode->getStopTime(getAnimStackIndex(), getAnimLayerIndex());
		if (time > stopTime)
		{
			time -= stopTime;
		}

		dirty = true;
	}

	if (dirty)
	{
		rootNode->updateRenderMatrix(*this, *rootInstanceNode, getModelMatrix(), time, getAnimStackIndex(), getAnimLayerIndex());

		dirty = false;
	}
}

void NodeEntity::render() const
{
	// Nothing to do
}

const string& NodeEntity::getCurrentProgramType() const
{
	return GeneralEntity::currentProgramType;
}

int32_t NodeEntity::getNumberJoints() const
{
	return 0;
}

const Matrix4x4* NodeEntity::getBindMatrices() const
{
	return nullptr;
}

const Matrix3x3* NodeEntity::getBindNormalMatrices() const
{
	return nullptr;
}

const Matrix4x4* NodeEntity::getJointMatrices() const
{
	return nullptr;
}

const Matrix3x3* NodeEntity::getJointNormalMatrices() const
{
	return nullptr;
}

bool NodeEntity::isWriteBrightColor() const
{
	return false;
}

float NodeEntity::getBrightColorLimit() const
{
	return 0.0f;
}

float NodeEntity::getRefractiveIndex() const
{
	return 0.0f;
}

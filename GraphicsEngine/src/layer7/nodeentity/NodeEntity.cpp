/*
 * NodeEntity.cpp
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#include "../../layer2/debug/DebugDraw.h"

#include "NodeEntity.h"

using namespace std;

using namespace boost;

NodeEntity::NodeEntity(const std::string& name, const NodeSP& rootNode, float scaleX, float scaleY, float scaleZ, bool updateable) :
		GeneralEntity(name, scaleX, scaleY, scaleZ), NodeOwner(), rootNode(rootNode), time(0.0f), animStackIndex(-1), animLayerIndex(-1), dirty(true)
{
	setUpdateable(updateable);

	setBoundingSphere(BoundingSphere(getPosition(), 2.0f));

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
	bool doUpdateBoundingSphereCenter = force;

	if (isUpdateable())
	{
		doUpdateBoundingSphereCenter = true;
	}

	if (doUpdateBoundingSphereCenter)
	{
		Matrix4x4 renderingMatrix;
		rootNode->updateRenderingMatrix(renderingMatrix, getModelMatrix(), time, animStackIndex, animLayerIndex);

		Point4 center = renderingMatrix * Point4();

		setBoundingSphereCenter(center);
	}
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
		rootNode->updateRenderMatrix(*rootInstanceNode, getModelMatrix(), time, getAnimStackIndex(), getAnimLayerIndex());

		dirty = false;
	}
}

void NodeEntity::render() const
{
	if (isDebug())
	{
		rootNode->render(*this, *rootInstanceNode, time, animStackIndex, animLayerIndex);
	}
}

void NodeEntity::renderNode(const Node& node, const InstanceNode& instanceNode, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	if (isDebug())
	{
		if (node.getCamera().get())
		{
			node.getCamera()->debugDraw();
		}

		if (node.getLight().get())
		{
			node.getLight()->debugDraw();
		}
	}
}


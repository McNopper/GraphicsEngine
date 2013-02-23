/*
 * Model.cpp
 *
 *  Created on: 24.05.2011
 *      Author: Norbert Nopper
 */

#include "Model.h"

using namespace std;

using namespace boost;

Model::Model(const BoundingSphere& boundingSphere, const NodeSP& node, int32_t numberJoints, bool animationData, bool skinned) :
	boundingSphere(boundingSphere), rootNode(node), numberJoints(numberJoints), animated(animationData), skinned(skinned), allNodesByIndex(), allNodesByName()
{
}

Model::~Model()
{
	allNodesByIndex.clear();
	allNodesByName.clear();

	rootNode.reset();
}

const BoundingSphere& Model::getBoundingSphere() const
{
	return boundingSphere;
}

const NodeSP& Model::getRootNode() const
{
	return rootNode;
}

int32_t Model::getNumberJoints() const
{
	return numberJoints;
}

bool Model::isAnimated() const
{
	return animated;
}

bool Model::isSkinned() const
{
	return skinned;
}

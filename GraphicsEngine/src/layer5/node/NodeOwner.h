/*
 * NodeOwner.h
 *
 *  Created on: 12.09.2012
 *      Author: nopper
 */

#ifndef NODEOWNER_H_
#define NODEOWNER_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix3x3.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer3/animation/AnimationStack.h"

class InstanceNode;
class Node;

class NodeOwner {
public:
	NodeOwner()
	{
	}

	virtual ~NodeOwner()
	{
	}

    virtual void renderNode(const Node& node, const InstanceNode& instanceNode, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const = 0;

    virtual void addLightNode(const InstanceNodeSP& lightNode) = 0;

    virtual void addCameraNode(const InstanceNodeSP& cameraNode) = 0;

};

#endif /* NODEOWNER_H_ */

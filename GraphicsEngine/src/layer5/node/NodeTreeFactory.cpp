/*
 * NodeTreeFactory.cpp
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#include "NodeTreeFactory.h"

using namespace std;

NodeTreeFactory::NodeTreeFactory() : rootNode()
{
}

NodeTreeFactory::~NodeTreeFactory()
{
}

NodeSP NodeTreeFactory::findNode(const string& name, const NodeSP& node) const
{
	if (!node.get())
	{
		return NodeSP();
	}

	if (name.compare(node->getName()) == 0)
	{
		return node;
	}
	else
	{
		auto walker = node->allChilds.begin();

		while (walker != node->allChilds.end())
		{
			NodeSP foundNode = findNode(name, *walker);

			if (foundNode.get())
			{
				return foundNode;
			}

			walker++;
		}
	}

	return NodeSP();
}

void NodeTreeFactory::reset()
{
	if (rootNode.get())
	{
		rootNode.reset();
	}
}

NodeSP NodeTreeFactory::getRootNode() const
{
	return rootNode;
}

NodeSP NodeTreeFactory::createNode(const string& nodeName, const string& parentNodeName, const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks, bool joint)
{
	float translate[3] = {0.0f, 0.0f, 0.0f};
	float rotateOffset[3] = {0.0f, 0.0f, 0.0f};
	float rotatePivot[3] = {0.0f, 0.0f, 0.0f};
	float preRotate[3] = {0.0f, 0.0f, 0.0f};
	float rotate[3] = {0.0f, 0.0f, 0.0f};
	float postRotate[3] = {0.0f, 0.0f, 0.0f};
	float scaleOffset[3] = {0.0f, 0.0f, 0.0f};
	float scalePivot[3] = {0.0f, 0.0f, 0.0f};
	float scale[3] = {1.0f, 1.0f, 1.0f};
	float geoTranslate[3] = {0.0f, 0.0f, 0.0f};
	float geoRotate[3] = {0.0f, 0.0f, 0.0f};
	float geoScale[3] = {1.0f, 1.0f, 1.0f};

	return createNode(nodeName, parentNodeName, translate, rotateOffset, rotatePivot, preRotate, rotate, postRotate, scaleOffset, scalePivot, scale, geoTranslate, geoRotate, geoScale, mesh, camera, light, allAnimStacks, joint);
}

NodeSP NodeTreeFactory::createNode(const string& nodeName, const string& parentNodeName, float translate[3], float rotateOffset[3], float rotatePivot[3], float preRotate[3], float rotate[3], float postRotate[3], float scaleOffset[3], float scalePivot[3], float scale[3], float geoTranslate[3], float geoRotate[3], float geoScale[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks, bool joint)
{
	NodeSP parentNode = findNode(parentNodeName, rootNode);

	NodeSP node = NodeSP(new Node(nodeName, parentNode, translate, rotateOffset, rotatePivot, preRotate, rotate, postRotate, scaleOffset, scalePivot, scale, geoTranslate, geoRotate, geoScale, mesh, camera, light, allAnimStacks, joint));

	if (parentNode.get())
	{
		addChild(parentNode, node);
	}
	else
	{
		rootNode = node;
	}

	return node;
}

int32_t NodeTreeFactory::createIndex() const
{
	if (rootNode.get())
	{
		return rootNode->createIndex(0);
	}

	return -1;
}

int32_t NodeTreeFactory::getIndex(const string& name) const
{
	if (rootNode.get())
	{
		return rootNode->getIndexRecursive(name);
	}

	return -1;
}

bool NodeTreeFactory::setTransformMatrix(const string& jointName, const Matrix4x4& matrix) const
{
	NodeSP node = findNode(jointName, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setTransformMatrix(jointName, matrix);

	return true;
}

bool NodeTreeFactory::setTransformLinkMatrix(const string& jointName, const Matrix4x4& matrix) const
{
	NodeSP node = findNode(jointName, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setTransformLinkMatrix(jointName, matrix);

	return true;
}

bool NodeTreeFactory::addChild(const NodeSP& parentNode, const NodeSP& child) const
{
	if (!parentNode.get() || !child.get())
	{
		return false;
	}

	parentNode->addChild(child);

	return true;
}

bool NodeTreeFactory::setTranslationLimits(const string& name, bool minActive, float min, bool maxActive, float max, int32_t index) const
{
	NodeSP node = findNode(name, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setTranslationLimits(minActive, min, maxActive, max, index);

	return true;
}

bool NodeTreeFactory::setRotationLimits(const string& name, bool minActive, float min, bool maxActive, float max, int32_t index) const
{
	NodeSP node = findNode(name, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setRotationLimits(minActive, min, maxActive, max, index);

	return true;
}

bool NodeTreeFactory::setScalingLimits(const string& name, bool minActive, float min, bool maxActive, float max, int32_t index) const
{
	NodeSP node = findNode(name, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setScalingLimits(minActive, min, maxActive, max, index);

	return true;
}

bool NodeTreeFactory::setUsedJoint(const string& jointName) const
{
	NodeSP node = findNode(jointName, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setUsedJoint(jointName);

	return true;
}


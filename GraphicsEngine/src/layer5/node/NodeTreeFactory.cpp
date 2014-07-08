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

NodeSP NodeTreeFactory::createNode(const string& nodeName, const string& parentNodeName, const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks)
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

	return createNode(nodeName, parentNodeName, translate, rotateOffset, rotatePivot, preRotate, rotate, postRotate, scaleOffset, scalePivot, scale, geoTranslate, geoRotate, geoScale, mesh, camera, light, allAnimStacks);
}

NodeSP NodeTreeFactory::createNode(const string& nodeName, const string& parentNodeName, const float translate[3], const float rotateOffset[3], const float rotatePivot[3], const float preRotate[3], const float rotate[3], const float postRotate[3], const float scaleOffset[3], const float scalePivot[3], const float scale[3], const float geoTranslate[3], const float geoRotate[3], const float geoScale[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks)
{
	NodeSP parentNode = findNode(parentNodeName, rootNode);

	NodeSP node = NodeSP(new Node(nodeName, parentNode, translate, rotateOffset, rotatePivot, preRotate, rotate, postRotate, scaleOffset, scalePivot, scale, geoTranslate, geoRotate, geoScale, mesh, camera, light, allAnimStacks));

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

NodeSP NodeTreeFactory::createNode(const string& nodeName, const string& parentNodeName, const float translate[3], const Matrix4x4& postTranslation, const float rotate[3], const Matrix4x4& postRotation, const float scale[3], const Matrix4x4& postScaling, const Matrix4x4& geometricTransform, const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks)
{
	NodeSP parentNode = findNode(parentNodeName, rootNode);

	NodeSP node = NodeSP(new Node(nodeName, parentNode, translate, postTranslation, rotate, postRotation, scale, postScaling, geometricTransform, mesh, camera, light, allAnimStacks));

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
		return rootNode->createJointIndex(0);
	}

	return -1;
}

int32_t NodeTreeFactory::getIndex(const string& name) const
{
	if (rootNode.get())
	{
		return rootNode->getJointIndexRecursive(name);
	}

	return -1;
}

bool NodeTreeFactory::setInverseBindMatrix(const string& jointName, const Matrix4x4& inverseBindMatrix) const
{
	NodeSP node = findNode(jointName, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setInverseBindMatrix(jointName, inverseBindMatrix);

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

bool NodeTreeFactory::setJoint(const string& jointName) const
{
	NodeSP node = findNode(jointName, rootNode);

	if (!node.get())
	{
		return false;
	}

	node->setJoint(jointName);

	return true;
}


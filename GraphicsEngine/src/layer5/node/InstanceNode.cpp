/*
 * InstanceNode.cpp
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#include "Node.h"

#include "InstanceNode.h"

using namespace std;

InstanceNode::InstanceNode(const Node* node) :
	node(node), visible(true), visibleActive(false), transparent(false), transparentActive(false), modelMatrix(), normalModelMatrix(), position(), rotation(), allChilds()
{
	name = node->getName();
}

InstanceNode::~InstanceNode()
{
	auto walkerNode = allChilds.begin();

	while (walkerNode != allChilds.end())
	{
		walkerNode->reset();

		walkerNode++;
	}

	allChilds.clear();
}

void InstanceNode::addChild(const InstanceNodeSP& instanceNode)
{
	allChilds.push_back(instanceNode);
}

const InstanceNodeSP& InstanceNode::getChild(int32_t i) const
{
	return allChilds[i];
}

InstanceNodeSP InstanceNode::findChildRecursive(const string& name) const
{
	auto walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		if ((*walker)->name.compare(name) == 0)
		{
			return *walker;
		}
		else
		{
			InstanceNodeSP child = (*walker)->findChildRecursive(name);

			if (child.get())
			{
				return child;
			}
		}

		walker++;
	}

	return InstanceNodeSP();
}

bool InstanceNode::isVisible() const
{
	return visible;
}

bool InstanceNode::isVisibleActive() const
{
	return visibleActive;
}

void InstanceNode::setVisible(bool visible, bool visibleActive)
{
		this->visible = visible;
		this->visibleActive = visibleActive;
}

void InstanceNode::setVisibleRecursive(bool visible, bool visibleActive)
{
		this->visible = visible;
		this->visibleActive = visibleActive;

		auto walkerNode = allChilds.begin();

		while (walkerNode != allChilds.end())
		{
			(*walkerNode)->setVisibleRecursive(visible, visibleActive);

			walkerNode++;
		}
}

bool InstanceNode::isTransparent() const
{
	return transparent;
}

bool InstanceNode::isTransparentActive() const
{
	return transparentActive;
}

void InstanceNode::setTransparent(bool transparent, bool transparentActive)
{
	this->transparent = transparent;
	this->transparentActive = transparentActive;
}

void InstanceNode::setTransparentRecursive(bool transparent, bool transparentActive)
{
	this->transparent = transparent;
	this->transparentActive = transparentActive;

	auto walkerNode = allChilds.begin();

	while (walkerNode != allChilds.end())
	{
		(*walkerNode)->setTransparentRecursive(visible, visibleActive);

		walkerNode++;
	}
}

const Matrix4x4& InstanceNode::getModelMatrix() const
{
	return modelMatrix;
}

const Matrix3x3& InstanceNode::getNormalModelMatrix() const
{
	return normalModelMatrix;
}

const Point4& InstanceNode::getPosition() const
{
	return position;
}

const Quaternion& InstanceNode::getRotation() const
{
	return rotation;
}

const Node* InstanceNode::getNode() const
{
	return node;
}


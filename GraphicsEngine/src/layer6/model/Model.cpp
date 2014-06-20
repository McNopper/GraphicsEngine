/*
 * Model.cpp
 *
 *  Created on: 24.05.2011
 *      Author: Norbert Nopper
 */

#include "Model.h"

using namespace std;

Model::Model(const BoundingSphere& boundingSphere, const NodeSP& node, int32_t numberJoints, bool animationData, bool skinned) :
	boundingSphere(boundingSphere), rootNode(node), numberJoints(numberJoints), animated(animationData), skinned(skinned), allNodesByName(), allSurfaceMaterialsByName()
{
	updateSurfaceMaterialsRecursive(rootNode);
}

Model::~Model()
{
	allNodesByName.clear();
	allSurfaceMaterialsByName.clear();

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

void Model::updateSurfaceMaterialsRecursive(const NodeSP& node)
{
	if (node.get())
	{
		allNodesByName[node->getName()] = node;

		if (node->getMesh().get())
		{
			const MeshSP& mesh = node->getMesh();

			for (uint32_t i = 0; i < mesh->getSurfaceMaterialsCount(); i++)
			{
				const SurfaceMaterialSP& surfaceMaterial = mesh->getSurfaceMaterialAt(i);

				auto result = allSurfaceMaterialsByName.find(surfaceMaterial->getName());

				if (result == allSurfaceMaterialsByName.end())
				{
					allSurfaceMaterialsByName[surfaceMaterial->getName()] = surfaceMaterial;
				}
			}
		}

		for (uint32_t i = 0; i < node->getChildCount(); i++)
		{
			updateSurfaceMaterialsRecursive(node->getChild(i));
		}
	}
}

SurfaceMaterialSP Model::findSurfaceMaterial(const string& name) const
{
	auto result = allSurfaceMaterialsByName.find(name);

	if (result != allSurfaceMaterialsByName.end())
	{
		return result->second;
	}

	return SurfaceMaterialSP();
}

int32_t Model::getNodeCount() const
{
	return static_cast<int32_t>(allNodesByName.size());
}

NodeSP Model::getNodeAt(int32_t index) const
{
	if (index >= 0 && index < getNodeCount())
	{
		auto walker = allNodesByName.begin();

		while (index > 0)
		{
			walker++;

			index--;
		}

		return walker->second;
	}

	return NodeSP();
}

int32_t Model::getSurfaceMaterialCount() const
{
	return static_cast<int32_t>(allSurfaceMaterialsByName.size());
}

SurfaceMaterialSP Model::getSurfaceMaterialAt(int32_t index) const
{
	if (index >= 0 && index < getSurfaceMaterialCount())
	{
		auto walker = allSurfaceMaterialsByName.begin();

		while (index > 0)
		{
			walker++;

			index--;
		}

		return walker->second;
	}

	return SurfaceMaterialSP();
}

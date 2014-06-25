/*
 * ModelFactory.cpp
 *
 *  Created on: 04.09.2012
 *      Author: nopper
 */

#include "../../layer3/camera/Camera.h"
#include "../../layer3/light/Light.h"
#include "../../layer3/mesh/MeshFactory.h"
#include "../../layer5/node/Node.h"
#include "../../layer5/node/NodeTreeFactory.h"

#include "ModelFactory.h"

using namespace std;

ModelFactory::ModelFactory()
{
}

ModelFactory::~ModelFactory()
{
}

ModelSP ModelFactory::createModel(const std::string& name, const BoundingSphere& boundingSphere, const CameraSP& camera) const
{
	vector<AnimationStackSP> allAnimStacks;

	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", MeshSP(), camera, LightSP(), allAnimStacks);

	return ModelSP(new Model(boundingSphere, node, 0, false, false));
}

ModelSP ModelFactory::createModel(const std::string& name, const BoundingSphere& boundingSphere, const CameraSP& camera, const std::vector<AnimationStackSP>& allAnimStacks) const
{
	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", MeshSP(), camera, LightSP(), allAnimStacks);

	return ModelSP(new Model(boundingSphere, node, 0, true, false));
}

ModelSP ModelFactory::createModel(const std::string& name, const BoundingSphere& boundingSphere, const LightSP& light) const
{
	vector<AnimationStackSP> allAnimStacks;

	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", MeshSP(), CameraSP(), light, allAnimStacks);

	return ModelSP(new Model(boundingSphere, node, 0, false, false));
}

ModelSP ModelFactory::createModel(const std::string& name, const BoundingSphere& boundingSphere, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks) const
{
	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", MeshSP(), CameraSP(), light, allAnimStacks);

	return ModelSP(new Model(boundingSphere, node, 0, true, false));
}

ModelSP ModelFactory::createModel(const string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial) const
{
	vector<AnimationStackSP> allAnimStacks;
	MeshFactory meshFactory;

	MeshSP mesh = meshFactory.createMesh(name, shape, surfaceMaterial);

	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", mesh, CameraSP(), LightSP(), allAnimStacks);

	return ModelSP(new Model(boundingSphere, node, 0, false, false));
}

ModelSP ModelFactory::createModel(const string& name, const BoundingSphere& boundingSphere, const GLUSshape& shape, const SurfaceMaterialSP& surfaceMaterial, const vector<AnimationStackSP>& allAnimStacks) const
{
	MeshFactory meshFactory;

	MeshSP mesh = meshFactory.createMesh(name, shape, surfaceMaterial);

	NodeTreeFactory nodeTreeFactory;

	NodeSP node = nodeTreeFactory.createNode(name, "", mesh, CameraSP(), LightSP(), allAnimStacks);

	return ModelSP(new Model(boundingSphere, node, 0, true, false));
}

/*
 * NodeEntityFactory.cpp
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#include "../../layer5/node/NodeTreeFactory.h"

#include "NodeEntityFactory.h"

using namespace std;

NodeEntityFactory::NodeEntityFactory()
{
}

NodeEntityFactory::~NodeEntityFactory()
{
}

NodeEntitySP NodeEntityFactory::createLightEntity(const string& name, const LightSP& light)
{
	vector<AnimationStackSP> allAnimStacks;

	NodeTreeFactory nodeTreeFactory;

	NodeSP rootNode = nodeTreeFactory.createNode("root", "", MeshSP(), CameraSP(), light, allAnimStacks, false);

	NodeEntitySP nodeEntity = NodeEntitySP(new NodeEntity(name, rootNode, 1.0f, 1.0f, 1.0f, false));

	return nodeEntity;
}

NodeEntitySP NodeEntityFactory::createLightEntity(const string& name, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks)
{
	NodeTreeFactory nodeTreeFactory;

	NodeSP rootNode = nodeTreeFactory.createNode("root", "", MeshSP(), CameraSP(), light, allAnimStacks, false);

	NodeEntitySP nodeEntity = NodeEntitySP(new NodeEntity(name, rootNode, 1.0f, 1.0f, 1.0f, true));

	return nodeEntity;
}

NodeEntitySP NodeEntityFactory::createCameraEntity(const string& name, const CameraSP& camera)
{
	vector<AnimationStackSP> allAnimStacks;

	NodeTreeFactory nodeTreeFactory;

	NodeSP rootNode = nodeTreeFactory.createNode("root", "", MeshSP(), camera, LightSP(), allAnimStacks, false);

	NodeEntitySP nodeEntity = NodeEntitySP(new NodeEntity(name, rootNode, 1.0f, 1.0f, 1.0f, false));

	return nodeEntity;
}

NodeEntitySP NodeEntityFactory::createCameraEntity(const string& name, const CameraSP& camera, const vector<AnimationStackSP>& allAnimStacks)
{
	NodeTreeFactory nodeTreeFactory;

	NodeSP rootNode = nodeTreeFactory.createNode("root", "", MeshSP(), camera, LightSP(), allAnimStacks, false);

	NodeEntitySP nodeEntity = NodeEntitySP(new NodeEntity(name, rootNode, 1.0f, 1.0f, 1.0f, true));

	return nodeEntity;
}

/*
 * Node.cpp
 *
 *  Created on: 14.05.2012
 *      Author: nopper
 */

#include "../../layer0/math/Quaternion.h"
#include "../../layer1/shader/Program.h"
#include "../../layer1/shader/VAO.h"
#include "../../layer1/shader/Variables.h"
#include "../../layer2/environment/SkyManager.h"
#include "../../layer2/material/RefractiveIndices.h"
#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer3/animation/AnimationLayer.h"
#include "../../layer3/animation/AnimationStack.h"
#include "../../layer3/mesh/Mesh.h"
#include "../../layer4/entity/Entity.h"
#include "Node.h"

using namespace std;

Node::Node(const string& name, const shared_ptr<Node>& parent, const float LclTranslation[3], const float RotationOffset[3], const float RotationPivot[3], const float PreRotation[3], const float LclRotation[3], const float PostRotation[3], const float ScalingOffset[3], const float ScalingPivot[3], const float LclScaling[3], const float GeometricTranslation[3], const float GeometricRotation[3], const float GeometricScaling[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks) :
	name(name), parentNode(parent), postTranslationMatrix(), postRotationMatrix(), postScalingMatrix(), geometricTransformMatrix(), mesh(mesh), camera(camera), light(light), visible(true), transparent(false), joint(false), jointIndex(-1), inverseBindMatrix(), allAnimStacks(allAnimStacks), allChilds()
{
	this->LclTranslation[0] = LclTranslation[0];
	this->LclTranslation[1] = LclTranslation[1];
	this->LclTranslation[2] = LclTranslation[2];

	this->LclRotation[0] = LclRotation[0];
	this->LclRotation[1] = LclRotation[1];
	this->LclRotation[2] = LclRotation[2];

	this->LclScaling[0] = LclScaling[0];
	this->LclScaling[1] = LclScaling[1];
	this->LclScaling[2] = LclScaling[2];

	Matrix4x4 rotationOffsetMatrix;
	Matrix4x4 rotationPivotMatrix;
	Matrix4x4 preRotationMatrix;
	Matrix4x4 postRotationMatrix;
	Matrix4x4 inverseRotationPivotMatrix;
	Matrix4x4 scalingOffsetMatrix;
	Matrix4x4 scalingPivotMatrix;
	Matrix4x4 inverseScalingPivotMatrix;

	rotationOffsetMatrix.translate(RotationOffset[0], RotationOffset[1], RotationOffset[2]);
	rotationPivotMatrix.translate(RotationPivot[0], RotationPivot[1], RotationPivot[2]);
	preRotationMatrix.rotateRzRyRx(PreRotation[2], PreRotation[1], PreRotation[0]);
	postRotationMatrix.rotateRzRyRx(PostRotation[2], PostRotation[1], PostRotation[0]);
	inverseRotationPivotMatrix = rotationPivotMatrix;
	inverseRotationPivotMatrix.inverseRigidBody();

	scalingOffsetMatrix.translate(ScalingOffset[0], ScalingOffset[1], ScalingOffset[2]);
	scalingPivotMatrix.translate(ScalingPivot[0], ScalingPivot[1], ScalingPivot[2]);
	inverseScalingPivotMatrix = scalingPivotMatrix;
	inverseScalingPivotMatrix.inverseRigidBody();


	this->postTranslationMatrix.multiply(rotationOffsetMatrix);
	this->postTranslationMatrix.multiply(rotationPivotMatrix);
	this->postTranslationMatrix.multiply(preRotationMatrix);

	this->postRotationMatrix.multiply(postRotationMatrix);
	this->postRotationMatrix.multiply(inverseRotationPivotMatrix);
	this->postRotationMatrix.multiply(scalingOffsetMatrix);
	this->postRotationMatrix.multiply(scalingPivotMatrix);

	this->postScalingMatrix.multiply(inverseScalingPivotMatrix);

	this->geometricTransformMatrix.translate(GeometricTranslation[0], GeometricTranslation[1], GeometricTranslation[2]);
	this->geometricTransformMatrix.rotateRzRyRx(GeometricRotation[2], GeometricRotation[1], GeometricRotation[0]);
	this->geometricTransformMatrix.scale(GeometricScaling[0], GeometricScaling[1], GeometricScaling[2]);
}

Node::Node(const string& name, const shared_ptr<Node>& parent, const float LclTranslation[3], const Matrix4x4& postTranslation, const float LclRotation[3], const Matrix4x4& postRotation, const float LclScaling[3], const Matrix4x4& postScaling, const Matrix4x4& geometricTransform, const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks) :
		name(name), parentNode(parent), postTranslationMatrix(postTranslation), postRotationMatrix(postRotation), postScalingMatrix(postScaling), geometricTransformMatrix(geometricTransform), mesh(mesh), camera(camera), light(light), visible(true), transparent(false), joint(false), jointIndex(-1), inverseBindMatrix(), allAnimStacks(allAnimStacks), allChilds()
{
	this->LclTranslation[0] = LclTranslation[0];
	this->LclTranslation[1] = LclTranslation[1];
	this->LclTranslation[2] = LclTranslation[2];

	this->LclRotation[0] = LclRotation[0];
	this->LclRotation[1] = LclRotation[1];
	this->LclRotation[2] = LclRotation[2];

	this->LclScaling[0] = LclScaling[0];
	this->LclScaling[1] = LclScaling[1];
	this->LclScaling[2] = LclScaling[2];
}

Node::~Node()
{
	vector<AnimationStackSP>::iterator walkerAnimationStack = allAnimStacks.begin();

	while (walkerAnimationStack != allAnimStacks.end())
	{
		walkerAnimationStack->reset();

		walkerAnimationStack++;
	}

	allAnimStacks.clear();

	if (mesh.get())
	{
		mesh.reset();
	}

	if (camera.get())
	{
		camera.reset();
	}

	if (light.get())
	{
		light.reset();
	}

	vector<NodeSP>::iterator walkerNode = allChilds.begin();

	while (walkerNode != allChilds.end())
	{
		walkerNode->reset();

		walkerNode++;
	}

	allChilds.clear();
}

int32_t Node::createJointIndex(int32_t index)
{
	if (joint)
	{
		this->jointIndex = index;

		index++;
	}
	else
	{
		this->jointIndex = -1;
	}

	vector<NodeSP>::iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		index = (*walker)->createJointIndex(index);

		walker++;
	}

	return index;
}

int32_t Node::countJointIndex(int32_t index)
{
	if (joint)
	{
		index++;
	}

	vector<NodeSP>::iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		index = (*walker)->countJointIndex(index);

		walker++;
	}

	return index;
}

int32_t Node::getJointIndexRecursive(const string& name) const
{
	if (this->name.compare(name) == 0)
	{
		return jointIndex;
	}

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t childIndex;

	while (walker != allChilds.end())
	{
		childIndex = (*walker)->getJointIndexRecursive(name);

		if (childIndex != -1)
		{
			return childIndex;
		}

		walker++;
	}

	return -1;
}

void Node::setInverseBindMatrix(const std::string& jointName, const Matrix4x4& inverseBindMatrix)
{
	if (jointName.compare(name) == 0)
	{
		this->inverseBindMatrix = inverseBindMatrix;
	}
	else
	{
		vector<NodeSP>::iterator walker = allChilds.begin();

		while (walker != allChilds.end())
		{
			(*walker)->setInverseBindMatrix(jointName, inverseBindMatrix);

			walker++;
		}
	}
}

const MeshSP& Node::getMesh() const
{
	return mesh;
}

const CameraSP& Node::getCamera() const
{
	return camera;
}

const LightSP& Node::getLight() const
{
	return light;
}

void Node::addChild(const NodeSP& child)
{
	allChilds.push_back(child);
}

std::uint32_t Node::getChildCount() const
{
	return allChilds.size();
}

const NodeSP& Node::getChild(int32_t i) const
{
	return allChilds.at(i);
}

const NodeSP& Node::getChild(const string& name) const
{
	vector<NodeSP>::const_iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		if ((*walker)->getName().compare(name) == 0)
		{
			return *walker;
		}

		walker++;
	}

	throw "Child '" + name + "' does not exist";
}

NodeSP Node::findChildRecursive(const string& name) const
{
	vector<NodeSP>::const_iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		if ((*walker)->getName().compare(name) == 0)
		{
			return *walker;
		}
		else
		{
			NodeSP child = (*walker)->findChildRecursive(name);

			if (child.get())
			{
				return child;
			}
		}

		walker++;
	}

	return NodeSP();
}

void Node::setJoint(const std::string& jointName)
{
	if (jointName.compare(name) == 0)
	{
		joint = true;
	}
	else
	{
		vector<NodeSP>::iterator walker = allChilds.begin();

		while (walker != allChilds.end())
		{
			(*walker)->setJoint(jointName);

			walker++;
		}
	}
}

const NodeSP& Node::getParentNode() const
{
	return parentNode;
}

int32_t Node::getJointIndex() const
{
	return jointIndex;
}

const std::string& Node::getName() const
{
	return name;
}

bool Node::isAnimated() const
{
	return allAnimStacks.size() != 0;
}

int32_t Node::getRootJointIndex() const
{
	if (joint)
	{
		return jointIndex;
	}

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	int32_t result = -1;
	while (walker != allChilds.end())
	{
		result = (*walker)->getRootJointIndex();

		if (result != -1)
		{
			return result;
		}

		walker++;
		i++;
	}

	return -1;
}

bool Node::updateBoundingSphereMatrix(Matrix4x4& matrix, const Matrix4x4& parentMatrix, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	if (joint)
	{
		return false;
	}

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	calculateAnimation(currentTranslate, currentRotate, currentScale, time, animStackIndex, animLayerIndex);

	Matrix4x4 localMatrix;

	calculateLocalMatrix(localMatrix, currentTranslate, currentRotate, currentScale);

	Matrix4x4 newParentMatrix = parentMatrix * localMatrix;

	if (mesh.get() || camera.get() || light.get())
	{
		matrix = newParentMatrix * geometricTransformMatrix;

		return true;
	}

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	bool result = false;
	while (walker != allChilds.end())
	{
		result = (*walker)->updateBoundingSphereMatrix(matrix, newParentMatrix, time, animStackIndex, animLayerIndex);

		if (result)
		{
			return true;
		}

		walker++;
		i++;
	}

	return false;
}

void Node::updateInverseBindMatrix(Matrix4x4* allInverseBindMatrices, Matrix3x3* allInverseBindNormalMatrices) const
{
	assert(allInverseBindMatrices);
	assert(allInverseBindNormalMatrices);

	if (joint)
	{
		allInverseBindMatrices[jointIndex] = inverseBindMatrix * geometricTransformMatrix;

		allInverseBindNormalMatrices[jointIndex] = allInverseBindMatrices[jointIndex].extractMatrix3x3();
		allInverseBindNormalMatrices[jointIndex].inverse();
	}

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		(*walker)->updateInverseBindMatrix(allInverseBindMatrices, allInverseBindNormalMatrices);

		walker++;
	}
}

void Node::updateBindMatrix(Matrix4x4* allBindMatrices, Matrix3x3* allBindNormalMatrices, const Matrix4x4& parentMatrix, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	assert(allBindMatrices);
	assert(allBindNormalMatrices);

	Matrix4x4 newParentMatrix = parentMatrix;

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	calculateAnimation(currentTranslate, currentRotate, currentScale, time, animStackIndex, animLayerIndex);

	Matrix4x4 jointLocalMatrix;

	if (joint)
	{
		calculateLocalMatrix(jointLocalMatrix, currentTranslate, currentRotate, currentScale);
	}
	else
	{
		jointLocalMatrix.translate(currentTranslate[0], currentTranslate[1], currentTranslate[2]);
		jointLocalMatrix.rotateRzRyRx(currentRotate[2], currentRotate[1], currentRotate[0]);
		jointLocalMatrix.scale(currentScale[0], currentScale[1], currentScale[2]);
	}

	newParentMatrix = parentMatrix * jointLocalMatrix;

	if (joint)
	{
		allBindMatrices[jointIndex] = newParentMatrix * geometricTransformMatrix;

		allBindNormalMatrices[jointIndex] = allBindMatrices[jointIndex].extractMatrix3x3();
		allBindNormalMatrices[jointIndex].inverse();
	}

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		(*walker)->updateBindMatrix(allBindMatrices, allBindNormalMatrices, newParentMatrix, time, animStackIndex, animLayerIndex);

		walker++;
	}
}

void Node::updateRenderMatrix(const NodeOwner& nodeOwner, InstanceNode& instanceNode, const Matrix4x4& parentMatrix, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const
{
	if (joint || (instanceNode.isVisibleActive() && !instanceNode.isVisible()) || (!instanceNode.isVisibleActive() && !visible))
	{
		return;
	}

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	calculateAnimation(currentTranslate, currentRotate, currentScale, time, animStackIndex, animLayerIndex);

	Matrix4x4 localMatrix;

	calculateLocalMatrix(localMatrix, currentTranslate, currentRotate, currentScale);

	Matrix4x4 newParentMatrix = parentMatrix * localMatrix;

	instanceNode.modelMatrix = newParentMatrix * geometricTransformMatrix;

	instanceNode.normalModelMatrix = instanceNode.modelMatrix.extractMatrix3x3();
	instanceNode.normalModelMatrix.inverse();

	//

	instanceNode.position = instanceNode.modelMatrix * Point4();
	instanceNode.rotation = instanceNode.modelMatrix.extractMatrix3x3();

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	while (walker != allChilds.end())
	{
		(*walker)->updateRenderMatrix(nodeOwner, *instanceNode.getChild(i), newParentMatrix, time, animStackIndex, animLayerIndex);

		walker++;
		i++;
	}
}

void Node::render(const NodeOwner& nodeOwner, const InstanceNode& instanceNode, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	if (joint || (instanceNode.isVisibleActive() && !instanceNode.isVisible()) || (!instanceNode.isVisibleActive() && !visible))
	{
		return;
	}

	//

	nodeOwner.renderNode(*this, instanceNode, time, animStackIndex, animLayerIndex);

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	while (walker != allChilds.end())
	{
		(*walker)->render(nodeOwner, *instanceNode.getChild(i), time, animStackIndex, animLayerIndex);

		walker++;
		i++;
	}
}

const Matrix4x4& Node::getPostTranslationMatrix() const
{
	return postTranslationMatrix;
}

const Matrix4x4& Node::getPostRotationMatrix() const
{
	return postRotationMatrix;
}

const Matrix4x4& Node::getPostScalingMatrix() const
{
	return postScalingMatrix;
}

const Matrix4x4& Node::getGeometricTransformMatrix() const
{
	return geometricTransformMatrix;
}

void Node::calculateAnimation(float* currentTranslation, float* currentRotation, float* currentScaling, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	for (int32_t i = 0; i < 3; i++)
	{
		if (currentTranslation)
		{
			currentTranslation[i] = LclTranslation[i];
		}
		if (currentRotation)
		{
			currentRotation[i] = LclRotation[i];
		}
		if (currentScaling)
		{
			currentScaling[i] = LclScaling[i];
		}
	}

	if (animStackIndex >= 0 && animLayerIndex >= 0 && static_cast<decltype(allAnimStacks.size())>(animStackIndex) < allAnimStacks.size() && animLayerIndex < allAnimStacks[animStackIndex]->getAnimationLayersCount())
	{
		// Animate values depending on time
		const AnimationLayerSP& animLayer = allAnimStacks[animStackIndex]->getAnimationLayer(animLayerIndex);

		for (enum AnimationLayer::eCHANNELS_XYZ i = AnimationLayer::X; i <= AnimationLayer::Z; i = static_cast<enum AnimationLayer::eCHANNELS_XYZ>(i + 1))
		{
			if (currentTranslation && animLayer->hasTranslationValue(i))
			{
				currentTranslation[i] = animLayer->getTranslationValue(i, time);
			}
			if (currentRotation && animLayer->hasRotationValue(i))
			{
				currentRotation[i] = animLayer->getRotationValue(i, time);
			}
			if (currentScaling && animLayer->hasScalingValue(i))
			{
				currentScaling[i] = animLayer->getScalingValue(i, time);
			}
		}
	}
}

void Node::calculateLocalMatrix(Matrix4x4& matrix, const float* translation, const float* rotation, const float* scaling) const
{
	const float* currentTranslation = LclTranslation;
	const float* currentRotation = LclRotation;
	const float* currentScaling = LclScaling;

	if (translation)
	{
		currentTranslation = translation;
	}
	if (rotation)
	{
		currentRotation = rotation;
	}
	if (scaling)
	{
		currentScaling = scaling;
	}

	matrix.identity();
	matrix.translate(currentTranslation[0], currentTranslation[1], currentTranslation[2]);
	matrix.multiply(postTranslationMatrix);
	matrix.rotateRzRyRx(currentRotation[2], currentRotation[1], currentRotation[0]);
	matrix.multiply(postRotationMatrix);
	matrix.scale(currentScaling[0], currentScaling[1], currentScaling[2]);
	matrix.multiply(postScalingMatrix);
}

float Node::getStopTime(int32_t animStackIndex, int32_t animLayerIndex) const
{
	if (animStackIndex >= -1 && animLayerIndex >= -1 && static_cast<decltype(allAnimStacks.size())>(animStackIndex) < allAnimStacks.size() && animLayerIndex < allAnimStacks[animStackIndex]->getAnimationLayersCount())
	{
		return allAnimStacks[animStackIndex]->getStopTime();
	}

	return 0.0f;
}

void Node::updateInstanceNode(NodeOwner& nodeOwner, const InstanceNodeSP& instanceNode) const
{
	if (light.get())
	{
		nodeOwner.addLightNode(instanceNode);
	}

	if (camera.get())
	{
		nodeOwner.addCameraNode(instanceNode);
	}

	auto walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		NodeSP childNode = *walker;

		InstanceNodeSP childInstanceNode = InstanceNodeSP(new InstanceNode(childNode.get()));

		instanceNode->addChild(childInstanceNode);

		childNode->updateInstanceNode(nodeOwner, childInstanceNode);

		walker++;
	}
}

bool Node::isTransparent() const
{
	return transparent;
}

void Node::setTransparent(bool transparent)
{
	this->transparent = transparent;
}

void Node::setTransparentRecursive(bool transparent)
{
	this->transparent = transparent;

	auto walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		(*walker)->setTransparentRecursive(transparent);

		walker++;
	}
}

bool Node::isVisible() const
{
	return visible;
}

void Node::setVisible(bool visible)
{
	this->visible = visible;
}

void Node::setVisibleRecursive(bool visible)
{
	this->visible = visible;

	auto walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		(*walker)->setVisibleRecursive(transparent);

		walker++;
	}
}

const std::vector<std::shared_ptr<AnimationStack> >& Node::getAllAnimStacks() const
{
	return allAnimStacks;
}

const float* Node::getLclRotation() const
{
	return LclRotation;
}

const float* Node::getLclScaling() const
{
	return LclScaling;
}

const float* Node::getLclTranslation() const
{
	return LclTranslation;
}

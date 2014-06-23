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

Node::Node(const std::string& name, const std::shared_ptr<Node>& parent, float LclTranslation[3], float RotationOffset[3], float RotationPivot[3], float PreRotation[3], float LclRotation[3], float PostRotation[3], float ScalingOffset[3], float ScalingPivot[3], float LclScaling[3], float GeometricTranslation[3], float GeometricRotation[3], float GeometricScaling[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const vector<AnimationStackSP>& allAnimStacks, bool joint) :
	name(name), parentNode(parent), transformMatrix(), transformLinkMatrix(), rotationOffsetMatrix(), rotationPivotMatrix(), preRotationMatrix(), postRotationMatrix(), inverseRotationPivotMatrix(), scalingOffsetMatrix(), scalingPivotMatrix(), inverseScalingPivotMatrix(), geometricTransformMatrix(), localFinalMatrix(), mesh(mesh), camera(camera), light(light), allAnimStacks(allAnimStacks), allChilds(), index(-1), joint(joint), usedJoint(false), visible(true), transparent(false)
{
	this->LclTranslation[0] = LclTranslation[0];
	this->LclTranslation[1] = LclTranslation[1];
	this->LclTranslation[2] = LclTranslation[2];

	this->RotationOffset[0] = RotationOffset[0];
	this->RotationOffset[1] = RotationOffset[1];
	this->RotationOffset[2] = RotationOffset[2];

	this->RotationPivot[0] = RotationPivot[0];
	this->RotationPivot[1] = RotationPivot[1];
	this->RotationPivot[2] = RotationPivot[2];

	this->PreRotation[0] = PreRotation[0];
	this->PreRotation[1] = PreRotation[1];
	this->PreRotation[2] = PreRotation[2];

	this->LclRotation[0] = LclRotation[0];
	this->LclRotation[1] = LclRotation[1];
	this->LclRotation[2] = LclRotation[2];

	this->PostRotation[0] = PostRotation[0];
	this->PostRotation[1] = PostRotation[1];
	this->PostRotation[2] = PostRotation[2];

	this->ScalingOffset[0] = ScalingOffset[0];
	this->ScalingOffset[1] = ScalingOffset[1];
	this->ScalingOffset[2] = ScalingOffset[2];

	this->ScalingPivot[0] = ScalingPivot[0];
	this->ScalingPivot[1] = ScalingPivot[1];
	this->ScalingPivot[2] = ScalingPivot[2];

	this->LclScaling[0] = LclScaling[0];
	this->LclScaling[1] = LclScaling[1];
	this->LclScaling[2] = LclScaling[2];

	this->GeometricTranslation[0] = GeometricTranslation[0];
	this->GeometricTranslation[1] = GeometricTranslation[1];
	this->GeometricTranslation[2] = GeometricTranslation[2];

	this->GeometricRotation[0] = GeometricRotation[0];
	this->GeometricRotation[1] = GeometricRotation[1];
	this->GeometricRotation[2] = GeometricRotation[2];

	this->GeometricScaling[0] = GeometricScaling[0];
	this->GeometricScaling[1] = GeometricScaling[1];
	this->GeometricScaling[2] = GeometricScaling[2];

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

	geometricTransformMatrix.translate(GeometricTranslation[0], GeometricTranslation[1], GeometricTranslation[2]);
	geometricTransformMatrix.rotateRzRyRx(GeometricRotation[2], GeometricRotation[1], GeometricRotation[0]);
	geometricTransformMatrix.scale(GeometricScaling[0], GeometricScaling[1], GeometricScaling[2]);

	for (int32_t i = 0; i < 3; i++)
	{
		translationMinActive[i] = false;
		translationMin[i] = 0.0f;
		translationMaxActive[i] = false;
		translationMax[i] = 0.0f;
		rotationMinActive[i] = false;
		rotationMin[i] = 0.0f;
		rotationMaxActive[i] = false;
		rotationMax[i] = 0.0f;
		scalingMinActive[i] = false;
		scalingMin[i] = 0.0f;
		scalingMaxActive[i] = false;
		scalingMax[i] = 0.0f;
	}

	updateLocalFinalMatrix();
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

int32_t Node::createIndex(int32_t index)
{
	if (joint && usedJoint)
	{
		this->index = index;

		index++;
	}
	else
	{
		this->index = -1;
	}

	vector<NodeSP>::iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		index = (*walker)->createIndex(index);

		walker++;
	}

	return index;
}

int32_t Node::countIndex(int32_t index)
{
	if (joint && usedJoint)
	{
		index++;
	}

	vector<NodeSP>::iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		index = (*walker)->countIndex(index);

		walker++;
	}

	return index;
}

int32_t Node::getIndexRecursive(const string& name) const
{
	if (this->name.compare(name) == 0)
	{
		return index;
	}

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t childIndex;

	while (walker != allChilds.end())
	{
		childIndex = (*walker)->getIndexRecursive(name);

		if (childIndex != -1)
		{
			return childIndex;
		}

		walker++;
	}

	return -1;
}

void Node::setTransformMatrix(const std::string& jointName, const Matrix4x4& matrix)
{
	if (jointName.compare(name) == 0)
	{
		transformMatrix = matrix;
	}
	else
	{
		vector<NodeSP>::iterator walker = allChilds.begin();

		while (walker != allChilds.end())
		{
			(*walker)->setTransformMatrix(jointName, matrix);

			walker++;
		}
	}
}

void Node::setTransformLinkMatrix(const std::string& jointName, const Matrix4x4& matrix)
{
	if (jointName.compare(name) == 0)
	{
		transformLinkMatrix = matrix;
	}
	else
	{
		vector<NodeSP>::iterator walker = allChilds.begin();

		while (walker != allChilds.end())
		{
			(*walker)->setTransformLinkMatrix(jointName, matrix);

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

float Node::getLimit(const float value[], const bool minActive[], const float min[], const bool maxActive[], const float max[], int32_t index) const
{
	float newValue = value[index];

	if (minActive[index] && newValue < min[index])
	{
		newValue = min[index];
	}
	if (maxActive[index] && newValue > max[index])
	{
		newValue = max[index];
	}

	return newValue;
}

void Node::setTranslationLimits(bool minActive, float min, bool maxActive, float max, int32_t index)
{
	translationMinActive[index] = minActive;
	translationMin[index] = min;
	translationMaxActive[index] = maxActive;
	translationMax[index] = max;

	updateLocalFinalMatrix();
}

void Node::setRotationLimits(bool minActive, float min, bool maxActive, float max, int32_t index)
{
	rotationMinActive[index] = minActive;
	rotationMin[index] = min;
	rotationMaxActive[index] = maxActive;
	rotationMax[index] = max;

	updateLocalFinalMatrix();
}

void Node::setScalingLimits(bool minActive, float min, bool maxActive, float max, int32_t index)
{
	scalingMinActive[index] = minActive;
	scalingMin[index] = min;
	scalingMaxActive[index] = maxActive;
	scalingMax[index] = max;

	updateLocalFinalMatrix();
}

void Node::setUsedJoint(const std::string& jointName)
{
	if (jointName.compare(name) == 0)
	{
		usedJoint = true;
	}
	else
	{
		vector<NodeSP>::iterator walker = allChilds.begin();

		while (walker != allChilds.end())
		{
			(*walker)->setUsedJoint(jointName);

			walker++;
		}
	}
}

void Node::updateLocalFinalMatrix()
{
	localFinalMatrix.identity();
	localFinalMatrix.translate(getLimit(LclTranslation, translationMinActive, translationMin, translationMaxActive, translationMax, 0), getLimit(LclTranslation, translationMinActive, translationMin, translationMaxActive, translationMax, 1), getLimit(LclTranslation, translationMinActive, translationMin, translationMaxActive, translationMax, 2));
	localFinalMatrix.multiply(rotationOffsetMatrix);
	localFinalMatrix.multiply(rotationPivotMatrix);
	localFinalMatrix.multiply(preRotationMatrix);
	localFinalMatrix.rotateRzRyRx(getLimit(LclRotation, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 2), getLimit(LclRotation, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 1), getLimit(LclRotation, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 0));
	localFinalMatrix.multiply(postRotationMatrix);
	localFinalMatrix.multiply(inverseRotationPivotMatrix);
	localFinalMatrix.multiply(scalingOffsetMatrix);
	localFinalMatrix.multiply(scalingPivotMatrix);
	localFinalMatrix.scale(getLimit(LclScaling, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 0), getLimit(LclScaling, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 1), getLimit(LclScaling, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 2));
	localFinalMatrix.multiply(inverseScalingPivotMatrix);
}

const NodeSP& Node::getParentNode() const
{
	return parentNode;
}

int32_t Node::getIndex() const
{
	return index;
}

const std::string& Node::getName() const
{
	return name;
}

bool Node::isAnimated() const
{
	return allAnimStacks.size() != 0;
}

int32_t Node::getSkinningRootIndex() const
{
	if (joint && usedJoint)
	{
		return index;
	}

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	int32_t result = -1;
	while (walker != allChilds.end())
	{
		result = (*walker)->getSkinningRootIndex();

		if (result != -1)
		{
			return result;
		}

		walker++;
		i++;
	}

	return -1;
}

bool Node::updateRenderingMatrix(Matrix4x4& matrix, const Matrix4x4& parentMatrix, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	if (joint)
	{
		return false;
	}

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	for (int32_t i = 0; i < 3; i++)
	{
		currentTranslate[i] = LclTranslation[i];
		currentRotate[i] = LclRotation[i];
		currentScale[i] = LclScaling[i];
	}

	if (animStackIndex >= 0 && animLayerIndex >= 0 && static_cast<decltype(allAnimStacks.size())>(animStackIndex) < allAnimStacks.size() && animLayerIndex < allAnimStacks[animStackIndex]->getAnimationLayersCount())
	{
		// Animate values depending on time
		const AnimationLayerSP& animLayer = allAnimStacks[animStackIndex]->getAnimationLayer(animLayerIndex);

		for (enum AnimationLayer::eCHANNELS_XYZ i = AnimationLayer::X; i <= AnimationLayer::Z; i = static_cast<enum AnimationLayer::eCHANNELS_XYZ>(i + 1))
		{
			if (animLayer->hasTranslationValue(i))
			{
				currentTranslate[i] = animLayer->getTranslationValue(i, time);
			}
			if (animLayer->hasRotationValue(i))
			{
				currentRotate[i] = animLayer->getRotationValue(i, time);
			}
			if (animLayer->hasScalingValue(i))
			{
				currentScale[i] = animLayer->getScalingValue(i, time);
			}
		}
	}

	Matrix4x4 localMatrix;

	localMatrix.translate(getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 0), getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 1), getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 2));
	localMatrix.multiply(rotationOffsetMatrix);
	localMatrix.multiply(rotationPivotMatrix);
	localMatrix.multiply(preRotationMatrix);
	localMatrix.rotateRzRyRx(getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 2), getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 1), getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 0));
	localMatrix.multiply(postRotationMatrix);
	localMatrix.multiply(inverseRotationPivotMatrix);
	localMatrix.multiply(scalingOffsetMatrix);
	localMatrix.multiply(scalingPivotMatrix);
	localMatrix.scale(getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 0), getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 1), getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 2));
	localMatrix.multiply(inverseScalingPivotMatrix);

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
		result = (*walker)->updateRenderingMatrix(matrix, newParentMatrix, time, animStackIndex, animLayerIndex);

		if (result)
		{
			return true;
		}

		walker++;
		i++;
	}

	return false;
}

void Node::updateBindMatrix(Matrix4x4* allBindMatrices, Matrix3x3* allBindNormalMatrices) const
{
	assert(allBindMatrices);
	assert(allBindNormalMatrices);

	if (joint && usedJoint)
	{
		Matrix4x4 transformFinalMatrix = transformMatrix * geometricTransformMatrix;
		Matrix4x4 transformLinkInverseMatrix = transformLinkMatrix;
		transformLinkInverseMatrix.inverseRigidBody();

		allBindMatrices[index] = transformLinkInverseMatrix * transformFinalMatrix;

		allBindNormalMatrices[index] = allBindMatrices[index].extractMatrix3x3();
		allBindNormalMatrices[index].inverse();
	}

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		(*walker)->updateBindMatrix(allBindMatrices, allBindNormalMatrices);

		walker++;
	}
}

void Node::updateJointMatrix(Matrix4x4* allJointMatrices, Matrix3x3* allJointNormalMatrices, const Matrix4x4& parentMatrix, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	assert(allJointMatrices);
	assert(allJointNormalMatrices);

	Matrix4x4 newParentMatrix = parentMatrix;

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	for (int32_t i = 0; i < 3; i++)
	{
		currentTranslate[i] = LclTranslation[i];
		currentRotate[i] = LclRotation[i];
		currentScale[i] = LclScaling[i];
	}

	if (animStackIndex >= 0 && animLayerIndex >= 0 && static_cast<decltype(allAnimStacks.size())>(animStackIndex) < allAnimStacks.size() && animLayerIndex < allAnimStacks[animStackIndex]->getAnimationLayersCount())
	{
		// Animate values depending on time
		const AnimationLayerSP& animLayer = allAnimStacks[animStackIndex]->getAnimationLayer(animLayerIndex);

		for (enum AnimationLayer::eCHANNELS_XYZ i = AnimationLayer::X; i <= AnimationLayer::Z; i = static_cast<enum AnimationLayer::eCHANNELS_XYZ>(i + 1))
		{
			if (animLayer->hasTranslationValue(i))
			{
				currentTranslate[i] = animLayer->getTranslationValue(i, time);
			}
			if (animLayer->hasRotationValue(i))
			{
				currentRotate[i] = animLayer->getRotationValue(i, time);
			}
			if (animLayer->hasScalingValue(i))
			{
				currentScale[i] = animLayer->getScalingValue(i, time);
			}
		}
	}

	Matrix4x4 jointLocalMatrix;

	if (usedJoint)
	{
		jointLocalMatrix.translate(getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 0), getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 1), getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 2));
		jointLocalMatrix.multiply(rotationOffsetMatrix);
		jointLocalMatrix.multiply(rotationPivotMatrix);
		jointLocalMatrix.multiply(preRotationMatrix);
		jointLocalMatrix.rotateRzRyRx(getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 2), getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 1), getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 0));
		jointLocalMatrix.multiply(postRotationMatrix);
		jointLocalMatrix.multiply(inverseRotationPivotMatrix);
		jointLocalMatrix.multiply(scalingOffsetMatrix);
		jointLocalMatrix.multiply(scalingPivotMatrix);
		jointLocalMatrix.scale(getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 0), getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 1), getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 2));
		jointLocalMatrix.multiply(inverseScalingPivotMatrix);
	}
	else
	{
		jointLocalMatrix.translate(currentTranslate[0], currentTranslate[1], currentTranslate[2]);
		jointLocalMatrix.rotateRzRyRx(currentRotate[2], currentRotate[1], currentRotate[0]);
		jointLocalMatrix.scale(currentScale[0], currentScale[1], currentScale[2]);
	}

	newParentMatrix = parentMatrix * jointLocalMatrix;

	if (joint && usedJoint)
	{
		allJointMatrices[index] = newParentMatrix * geometricTransformMatrix;

		allJointNormalMatrices[index] = allJointMatrices[index].extractMatrix3x3();
		allJointNormalMatrices[index].inverse();
	}

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		(*walker)->updateJointMatrix(allJointMatrices, allJointNormalMatrices, newParentMatrix, time, animStackIndex, animLayerIndex);

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

	for (int32_t i = 0; i < 3; i++)
	{
		currentTranslate[i] = LclTranslation[i];
		currentRotate[i] = LclRotation[i];
		currentScale[i] = LclScaling[i];
	}

	if (animStackIndex >= 0 && animLayerIndex >= 0 && static_cast<decltype(allAnimStacks.size())>(animStackIndex) < allAnimStacks.size() && animLayerIndex < allAnimStacks[animStackIndex]->getAnimationLayersCount())
	{
		// Animate values depending on time
		const AnimationLayerSP& animLayer = allAnimStacks[animStackIndex]->getAnimationLayer(animLayerIndex);

		for (enum AnimationLayer::eCHANNELS_XYZ i = AnimationLayer::X; i <= AnimationLayer::Z; i = static_cast<enum AnimationLayer::eCHANNELS_XYZ>(i + 1))
		{
			if (animLayer->hasTranslationValue(i))
			{
				currentTranslate[i] = animLayer->getTranslationValue(i, time);
			}
			if (animLayer->hasRotationValue(i))
			{
				currentRotate[i] = animLayer->getRotationValue(i, time);
			}
			if (animLayer->hasScalingValue(i))
			{
				currentScale[i] = animLayer->getScalingValue(i, time);
			}
		}
	}

	Matrix4x4 localMatrix;

	localMatrix.translate(getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 0), getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 1), getLimit(currentTranslate, translationMinActive, translationMin, translationMaxActive, translationMax, 2));
	localMatrix.multiply(rotationOffsetMatrix);
	localMatrix.multiply(rotationPivotMatrix);
	localMatrix.multiply(preRotationMatrix);
	localMatrix.rotateRzRyRx(getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 2), getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 1), getLimit(currentRotate, rotationMinActive, rotationMin, rotationMaxActive, rotationMax, 0));
	localMatrix.multiply(postRotationMatrix);
	localMatrix.multiply(inverseRotationPivotMatrix);
	localMatrix.multiply(scalingOffsetMatrix);
	localMatrix.multiply(scalingPivotMatrix);
	localMatrix.scale(getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 0), getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 1), getLimit(currentScale, scalingMinActive, scalingMin, scalingMaxActive, scalingMax, 2));
	localMatrix.multiply(inverseScalingPivotMatrix);

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

const Matrix4x4& Node::getGeometricTransform() const {
	return geometricTransformMatrix;
}

const Matrix4x4& Node::getLocalFinalMatrix() const {
	return localFinalMatrix;
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

const float* Node::getGeometricRotation() const
{
	return GeometricRotation;
}

const float* Node::getGeometricScaling() const
{
	return GeometricScaling;
}

const float* Node::getGeometricTranslation() const
{
	return GeometricTranslation;
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

const float* Node::getPostRotation() const
{
	return PostRotation;
}

const float* Node::getPreRotation() const
{
	return PreRotation;
}

const float* Node::getRotationMax() const
{
	return rotationMax;
}

const bool* Node::getRotationMaxActive() const
{
	return rotationMaxActive;
}

const float* Node::getRotationMin() const
{
	return rotationMin;
}

const bool* Node::getRotationMinActive() const
{
	return rotationMinActive;
}

const float* Node::getRotationOffset() const
{
	return RotationOffset;
}

const float* Node::getRotationPivot() const
{
	return RotationPivot;
}

const float* Node::getScalingMax() const
{
	return scalingMax;
}

const bool* Node::getScalingMaxActive() const
{
	return scalingMaxActive;
}

const float* Node::getScalingMin() const
{
	return scalingMin;
}

const bool* Node::getScalingMinActive() const
{
	return scalingMinActive;
}

const float* Node::getScalingOffset() const
{
	return ScalingOffset;
}

const float* Node::getScalingPivot() const
{
	return ScalingPivot;
}

const float* Node::getTranslationMax() const
{
	return translationMax;
}

const bool* Node::getTranslationMaxActive() const
{
	return translationMaxActive;
}

const float* Node::getTranslationMin() const
{
	return translationMin;
}

const bool* Node::getTranslationMinActive() const
{
	return translationMinActive;
}

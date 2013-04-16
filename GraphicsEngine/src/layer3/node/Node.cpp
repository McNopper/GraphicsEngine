/*
 * Node.cpp
 *
 *  Created on: 14.05.2012
 *      Author: nopper
 */

#include "../../layer0/math/Quaternion.h"
#include "../../layer0/shader/Program.h"
#include "../../layer0/shader/VAO.h"
#include "../../layer0/shader/Variables.h"
#include "../../layer1/material/SurfaceMaterial.h"
#include "../../layer2/animation/AnimationLayer.h"
#include "../../layer2/animation/AnimationStack.h"
#include "../../layer2/environment/SkyManager.h"
#include "../../layer2/entity/Entity.h"
#include "../../layer2/mesh/Mesh.h"

#include "Node.h"

using namespace std;
using namespace boost;

Node::Node(const std::string& name, const boost::shared_ptr<Node>& parent, float translate[3], float rotateOffset[3], float rotatePivot[3], float preRotate[3], float rotate[3], float postRotate[3], float scaleOffset[3], float scalePivot[3], float scale[3], float geoTranslate[3], float geoRotate[3], float geoScale[3], const MeshSP& mesh, const vector<AnimationStackSP>& allAnimStacks, bool joint) :
	name(name), parentNode(parent), transformMatrix(), transformLinkMatrix(), rotateOffsetMatrix(), rotatePivotMatrix(), preRotateMatrix(), postRotateMatrix(), inverseRotatePivotMatrix(), scaleOffsetMatrix(), scalePivotMatrix(), inverseScalePivotMatrix(), geometricTransformMatrix(), localFinalMatrix(), mesh(mesh), allAnimStacks(allAnimStacks), allChilds(), index(-1), joint(joint), usedJoint(false), visible(true), transparent(false)
{
	this->translate[0] = translate[0];
	this->translate[1] = translate[1];
	this->translate[2] = translate[2];

	this->rotate[0] = rotate[0];
	this->rotate[1] = rotate[1];
	this->rotate[2] = rotate[2];

	this->scale[0] = scale[0];
	this->scale[1] = scale[1];
	this->scale[2] = scale[2];

	rotateOffsetMatrix.translate(rotateOffset[0], rotateOffset[1], rotateOffset[2]);
	rotatePivotMatrix.translate(rotatePivot[0], rotatePivot[1], rotatePivot[2]);
	preRotateMatrix.rotateRzRyRx(preRotate[2], preRotate[1], preRotate[0]);
	postRotateMatrix.rotateRzRyRx(postRotate[2], postRotate[1], postRotate[0]);
	inverseRotatePivotMatrix = rotatePivotMatrix;
	inverseRotatePivotMatrix.inverseRigidBody();

	scaleOffsetMatrix.translate(scaleOffset[0], scaleOffset[1], scaleOffset[2]);
	scalePivotMatrix.translate(scalePivot[0], scalePivot[1], scalePivot[2]);
	inverseScalePivotMatrix = scalePivotMatrix;
	inverseScalePivotMatrix.inverseRigidBody();

	geometricTransformMatrix.translate(geoTranslate[0], geoTranslate[1], geoTranslate[2]);
	geometricTransformMatrix.rotateRzRyRx(geoRotate[2], geoRotate[1], geoRotate[0]);
	geometricTransformMatrix.scale(geoScale[0], geoScale[1], geoScale[2]);

	for (int32_t i = 0; i < 3; i++)
	{
		transMinActive[i] = false;
		transMaxActive[i] = false;
		rotMinActive[i] = false;
		rotMaxActive[i] = false;
		scaleMinActive[i] = false;
		scaleMaxActive[i] = false;
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

void Node::addChild(const NodeSP& child)
{
	allChilds.push_back(child);
}

boost::uint32_t Node::getChildCount() const
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
	transMinActive[index] = minActive;
	minTrans[index] = min;
	transMaxActive[index] = maxActive;
	maxTrans[index] = max;

	updateLocalFinalMatrix();
}

void Node::setRotationLimits(bool minActive, float min, bool maxActive, float max, int32_t index)
{
	rotMinActive[index] = minActive;
	minRot[index] = min;
	rotMaxActive[index] = maxActive;
	maxRot[index] = max;

	updateLocalFinalMatrix();
}

void Node::setScalingLimits(bool minActive, float min, bool maxActive, float max, int32_t index)
{
	scaleMinActive[index] = minActive;
	minScale[index] = min;
	scaleMaxActive[index] = maxActive;
	maxScale[index] = max;

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
	localFinalMatrix.translate(getLimit(translate, transMinActive, minTrans, transMaxActive, maxTrans, 0), getLimit(translate, transMinActive, minTrans, transMaxActive, maxTrans, 1), getLimit(translate, transMinActive, minTrans, transMaxActive, maxTrans, 2));
	localFinalMatrix.multiply(rotateOffsetMatrix);
	localFinalMatrix.multiply(rotatePivotMatrix);
	localFinalMatrix.multiply(preRotateMatrix);
	localFinalMatrix.rotateRzRyRx(getLimit(rotate, rotMinActive, minRot, rotMaxActive, maxRot, 2), getLimit(rotate, rotMinActive, minRot, rotMaxActive, maxRot, 1), getLimit(rotate, rotMinActive, minRot, rotMaxActive, maxRot, 0));
	localFinalMatrix.multiply(postRotateMatrix);
	localFinalMatrix.multiply(inverseRotatePivotMatrix);
	localFinalMatrix.multiply(scaleOffsetMatrix);
	localFinalMatrix.multiply(scalePivotMatrix);
	localFinalMatrix.scale(getLimit(scale, scaleMinActive, minScale, scaleMaxActive, maxScale, 0), getLimit(scale, scaleMinActive, minScale, scaleMaxActive, maxScale, 1), getLimit(scale, scaleMinActive, minScale, scaleMaxActive, maxScale, 2));
	localFinalMatrix.multiply(inverseScalePivotMatrix);
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

bool Node::updateSkinningMatrix(Matrix4x4& matrix, const Matrix4x4& parentMatrix, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	if (mesh)
	{
		return false;
	}

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	for (int32_t i = 0; i < 3; i++)
	{
		currentTranslate[i] = translate[i];
		currentRotate[i] = rotate[i];
		currentScale[i] = scale[i];
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

	Matrix4x4 bindMatrix;

	if (joint && usedJoint)
	{
		Matrix4x4 transformFinalMatrix = transformMatrix * geometricTransformMatrix;
		Matrix4x4 transformLinkInverseMatrix = transformLinkMatrix;
		transformLinkInverseMatrix.inverseRigidBody();

		bindMatrix = transformLinkInverseMatrix * transformFinalMatrix;
	}

	Matrix4x4 localMatrix;

	if (usedJoint)
	{
		localMatrix.translate(getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 0), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 1), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 2));
		localMatrix.multiply(rotateOffsetMatrix);
		localMatrix.multiply(rotatePivotMatrix);
		localMatrix.multiply(preRotateMatrix);
		localMatrix.rotateRzRyRx(getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 2), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 1), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 0));
		localMatrix.multiply(postRotateMatrix);
		localMatrix.multiply(inverseRotatePivotMatrix);
		localMatrix.multiply(scaleOffsetMatrix);
		localMatrix.multiply(scalePivotMatrix);
		localMatrix.scale(getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 0), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 1), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 2));
		localMatrix.multiply(inverseScalePivotMatrix);
	}
	else
	{
		localMatrix.translate(currentTranslate[0], currentTranslate[1], currentTranslate[2]);
		localMatrix.rotateRzRyRx(currentRotate[2], currentRotate[1], currentRotate[0]);
		localMatrix.scale(currentScale[0], currentScale[1], currentScale[2]);
	}

	Matrix4x4 newParentMatrix = parentMatrix * localMatrix;

	if (joint && usedJoint)
	{
		matrix = newParentMatrix * geometricTransformMatrix * bindMatrix;

		return true;
	}

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	bool result = false;
	while (walker != allChilds.end())
	{
		result = (*walker)->updateSkinningMatrix(matrix, newParentMatrix, time, animStackIndex, animLayerIndex);

		if (result)
		{
			return true;
		}

		walker++;
		i++;
	}

	return false;
}

void Node::updateRenderingMatrix(Matrix4x4& matrix, const Matrix4x4& parentMatrix, float time, int32_t animStackIndex, int32_t animLayerIndex) const
{
	if (joint)
	{
		return;
	}

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	for (int32_t i = 0; i < 3; i++)
	{
		currentTranslate[i] = translate[i];
		currentRotate[i] = rotate[i];
		currentScale[i] = scale[i];
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

	localMatrix.translate(getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 0), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 1), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 2));
	localMatrix.multiply(rotateOffsetMatrix);
	localMatrix.multiply(rotatePivotMatrix);
	localMatrix.multiply(preRotateMatrix);
	localMatrix.rotateRzRyRx(getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 2), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 1), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 0));
	localMatrix.multiply(postRotateMatrix);
	localMatrix.multiply(inverseRotatePivotMatrix);
	localMatrix.multiply(scaleOffsetMatrix);
	localMatrix.multiply(scalePivotMatrix);
	localMatrix.scale(getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 0), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 1), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 2));
	localMatrix.multiply(inverseScalePivotMatrix);

	Matrix4x4 newParentMatrix = parentMatrix * localMatrix;

	if (mesh)
	{
		matrix = newParentMatrix * geometricTransformMatrix;

		return;
	}

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	while (walker != allChilds.end())
	{
		(*walker)->updateRenderingMatrix(matrix, newParentMatrix, time, animStackIndex, animLayerIndex);

		walker++;
		i++;
	}
}

void Node::updateBindMatrix(Matrix4x4* allBindMatrices, Matrix3x3* allBindNormalMatrices) const
{
	BOOST_ASSERT(allBindMatrices);
	BOOST_ASSERT(allBindNormalMatrices);

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
	BOOST_ASSERT(allJointMatrices);
	BOOST_ASSERT(allJointNormalMatrices);

	Matrix4x4 newParentMatrix = parentMatrix;

	float currentTranslate[3] = {0.0f, 0.0f, 0.0f};
	float currentRotate[3] = {0.0f, 0.0f, 0.0f};
	float currentScale[3] = {1.0f, 1.0f, 1.0f};

	for (int32_t i = 0; i < 3; i++)
	{
		currentTranslate[i] = translate[i];
		currentRotate[i] = rotate[i];
		currentScale[i] = scale[i];
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
		jointLocalMatrix.translate(getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 0), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 1), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 2));
		jointLocalMatrix.multiply(rotateOffsetMatrix);
		jointLocalMatrix.multiply(rotatePivotMatrix);
		jointLocalMatrix.multiply(preRotateMatrix);
		jointLocalMatrix.rotateRzRyRx(getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 2), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 1), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 0));
		jointLocalMatrix.multiply(postRotateMatrix);
		jointLocalMatrix.multiply(inverseRotatePivotMatrix);
		jointLocalMatrix.multiply(scaleOffsetMatrix);
		jointLocalMatrix.multiply(scalePivotMatrix);
		jointLocalMatrix.scale(getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 0), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 1), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 2));
		jointLocalMatrix.multiply(inverseScalePivotMatrix);
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

void Node::render(const NodeOwner& nodeOwner, const InstanceNode& instanceNode, const Matrix4x4& parentMatrix, float time, int32_t animStackIndex, int32_t animLayerIndex) const
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
		currentTranslate[i] = translate[i];
		currentRotate[i] = rotate[i];
		currentScale[i] = scale[i];
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

	localMatrix.translate(getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 0), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 1), getLimit(currentTranslate, transMinActive, minTrans, transMaxActive, maxTrans, 2));
	localMatrix.multiply(rotateOffsetMatrix);
	localMatrix.multiply(rotatePivotMatrix);
	localMatrix.multiply(preRotateMatrix);
	localMatrix.rotateRzRyRx(getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 2), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 1), getLimit(currentRotate, rotMinActive, minRot, rotMaxActive, maxRot, 0));
	localMatrix.multiply(postRotateMatrix);
	localMatrix.multiply(inverseRotatePivotMatrix);
	localMatrix.multiply(scaleOffsetMatrix);
	localMatrix.multiply(scalePivotMatrix);
	localMatrix.scale(getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 0), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 1), getLimit(currentScale, scaleMinActive, minScale, scaleMaxActive, maxScale, 2));
	localMatrix.multiply(inverseScalePivotMatrix);

	Matrix4x4 newParentMatrix = parentMatrix * localMatrix;

	Matrix4x4 matrix = newParentMatrix * geometricTransformMatrix;

	Matrix3x3 normalMatrix = matrix.extractMatrix3x3();
	normalMatrix.inverse();

	//

	enum RenderFilter renderFilter = Entity::getRenderFilter();
	bool finalTransparent = (instanceNode.isTransparentActive() && instanceNode.isTransparent()) || (!instanceNode.isTransparentActive() && transparent);
	bool renderMesh = (renderFilter == RENDER_ALL) || (finalTransparent && renderFilter == RENDER_TRANSPARENT) || (!finalTransparent && renderFilter == RENDER_OPAQUE);

	if (mesh && renderMesh)
	{
		VAOSP currentVAO;
		ProgramSP currentProgram;
		SubMeshSP currentSubMesh;
		SurfaceMaterialSP currentSurfaceMaterial;
		for (uint32_t subMeshIndex = 0; subMeshIndex < mesh->getSubMeshesCount(); subMeshIndex++)
		{
			currentSubMesh = mesh->getSubMeshAt(subMeshIndex);

			currentSurfaceMaterial = mesh->getSurfaceMaterialAt(subMeshIndex);

			float currentEmissive[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			float currentAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			float currentDiffuse[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			float currentSpecular[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			float currentReflection[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			float currentRefraction[4] = {0.0f, 0.0f, 0.0f, 1.0f};
			float currentShininess = 0.0f;
			float currentTransparency = 0.0f;

			for (int32_t i = 0; i < 4; i++)
			{
				currentEmissive[i] = currentSurfaceMaterial->getEmissive().getRGBA()[i];
				currentAmbient[i] = currentSurfaceMaterial->getAmbient().getRGBA()[i];
				currentDiffuse[i] = currentSurfaceMaterial->getDiffuse().getRGBA()[i];
				currentSpecular[i] = currentSurfaceMaterial->getSpecular().getRGBA()[i];
				currentReflection[i] = currentSurfaceMaterial->getReflection().getRGBA()[i];
				currentRefraction[i] = currentSurfaceMaterial->getRefraction().getRGBA()[i];
			}
			currentShininess = currentSurfaceMaterial->getShininess();
			currentTransparency = currentSurfaceMaterial->getTransparency();

			if (animStackIndex >= 0 && animLayerIndex >= 0 && static_cast<decltype(allAnimStacks.size())>(animStackIndex) < allAnimStacks.size() && animLayerIndex < allAnimStacks[animStackIndex]->getAnimationLayersCount())
			{
				// Animate values depending on time
				const AnimationLayerSP& animLayer = allAnimStacks[animStackIndex]->getAnimationLayer(animLayerIndex);

				for (enum AnimationLayer::eCHANNELS_RGBA i = AnimationLayer::R; i <= AnimationLayer::A; i = static_cast<enum AnimationLayer::eCHANNELS_RGBA>(i + 1))
				{
					if (animLayer->hasEmissiveColorValue(i))
					{
						currentEmissive[i] = animLayer->getEmissiveColorValue(i, time);
					}
					if (animLayer->hasAmbientColorValue(i))
					{
						currentAmbient[i] = animLayer->getAmbientColorValue(i, time);
					}
					if (animLayer->hasDiffuseColorValue(i))
					{
						currentDiffuse[i] = animLayer->getDiffuseColorValue(i, time);
					}
					if (animLayer->hasSpecularColorValue(i))
					{
						currentSpecular[i] = animLayer->getSpecularColorValue(i, time);
					}
					if (animLayer->hasReflectionColorValue(i))
					{
						currentReflection[i] = animLayer->getReflectionColorValue(i, time);
					}
					if (animLayer->hasRefractionColorValue(i))
					{
						currentRefraction[i] = animLayer->getRefractionColorValue(i, time);
					}
				}

				if (animLayer->hasShininessValue(AnimationLayer::S))
				{
					currentShininess = animLayer->getShininessValue(AnimationLayer::S, time);
				}
				if (animLayer->hasTransparencyValue(AnimationLayer::S))
				{
					currentTransparency = animLayer->getTransparencyValue(AnimationLayer::S, time);
				}
			}

			currentVAO = currentSubMesh->getVAOByProgramType(nodeOwner.getCurrentProgramType());

			currentProgram = currentVAO->getProgram();

			currentProgram->use();

			// In some cases, the vertex shader should only use the model matrix
			glUniform1i(currentProgram->getUniformLocation(u_modelTransformOnly), Entity::getModelTransformOnly());

			glUniformMatrix4fv(currentProgram->getUniformLocation(u_modelMatrix), 1, GL_FALSE, matrix.getM());

			// We have the inverse and transpose by setting the matrix
			glUniformMatrix3fv(currentProgram->getUniformLocation(u_normalModelMatrix), 1, GL_TRUE, normalMatrix.getM());

			currentVAO->bind();

			glUniform4fv(currentProgram->getUniformLocation(u_emissiveColor), 1, currentEmissive);
			glUniform4fv(currentProgram->getUniformLocation(u_ambientColor), 1, currentAmbient);

			if (currentSurfaceMaterial->getDiffuseTextureName() != 0)
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDiffuseTexture), 1);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, currentSurfaceMaterial->getDiffuseTextureName());
				glUniform1i(currentProgram->getUniformLocation(u_diffuseTexture), 0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDiffuseTexture), 0);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(currentProgram->getUniformLocation(u_diffuseTexture), 0);
			}
			glUniform4fv(currentProgram->getUniformLocation(u_diffuseColor), 1, currentDiffuse);

			glUniform4fv(currentProgram->getUniformLocation(u_specularColor), 1, currentSpecular);
			glUniform1f(currentProgram->getUniformLocation(u_shininess), currentShininess);

			glUniform1f(currentProgram->getUniformLocation(u_transparency), currentTransparency);

			if (currentSurfaceMaterial->getNormalMapTextureName() != 0)
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasNormalMapTexture), 1);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, currentSurfaceMaterial->getNormalMapTextureName());
				glUniform1i(currentProgram->getUniformLocation(u_normalMapTexture), 1);
				glActiveTexture(GL_TEXTURE0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasNormalMapTexture), 0);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(currentProgram->getUniformLocation(u_normalMapTexture), 1);
				glActiveTexture(GL_TEXTURE0);
			}

			glUniform4fv(currentProgram->getUniformLocation(u_reflectionColor), 1, currentReflection);
			glUniform4fv(currentProgram->getUniformLocation(u_refractionColor), 1, currentRefraction);

			float environmentRefractiveIndex = nodeOwner.getRefractiveIndex();
			float materialRefractiveIndex = currentSurfaceMaterial->getRefractiveIndex();

			float eta = environmentRefractiveIndex / materialRefractiveIndex;

			float reflectanceNormalIncidence = ((environmentRefractiveIndex - materialRefractiveIndex) * (environmentRefractiveIndex - materialRefractiveIndex)) / ((environmentRefractiveIndex + materialRefractiveIndex) * (environmentRefractiveIndex + materialRefractiveIndex));

			glUniform1f(currentProgram->getUniformLocation(u_eta), eta);
			glUniform1f(currentProgram->getUniformLocation(u_reflectanceNormalIncidence), reflectanceNormalIncidence);

			if (SkyManager::getInstance()->hasActiveSky())
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasCubeMapTexture), 1);

				SkySP activeSky = SkyManager::getInstance()->getActiveSky();

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_CUBE_MAP, activeSky->getSkyTextureName());
			    glUniform1i(currentProgram->getUniformLocation(u_cubemap), 2);
				glActiveTexture(GL_TEXTURE0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasCubeMapTexture), 0);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			    glUniform1i(currentProgram->getUniformLocation(u_cubemap), 2);
				glActiveTexture(GL_TEXTURE0);
			}

			// Only allow dynamic cube map, if also a sky cube map is available
			if (Entity::getDynamicCubeMaps() && currentSurfaceMaterial->getDynamicCubeMapTextureName() != 0 && SkyManager::getInstance()->hasActiveSky())
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDynamicCubeMapTexture), 1);
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_CUBE_MAP, currentSurfaceMaterial->getDynamicCubeMapTextureName());
			    glUniform1i(currentProgram->getUniformLocation(u_dynamicCubeMapTexture), 3);
				glActiveTexture(GL_TEXTURE0);
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasDynamicCubeMapTexture), 0);
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			    glUniform1i(currentProgram->getUniformLocation(u_dynamicCubeMapTexture), 3);
				glActiveTexture(GL_TEXTURE0);
			}

			// Skinning
			if (mesh->hasSkinning())
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasSkinning), 1);

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_bindMatrix), nodeOwner.getNumberJoints(), GL_FALSE, nodeOwner.getBindMatrices()[0].getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_bindNormalMatrix), nodeOwner.getNumberJoints(), GL_TRUE, nodeOwner.getBindNormalMatrices()[0].getM());

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_jointMatrix), nodeOwner.getNumberJoints(), GL_FALSE, nodeOwner.getJointMatrices()[0].getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_jointNormalMatrix), nodeOwner.getNumberJoints(), GL_TRUE, nodeOwner.getJointNormalMatrices()[0].getM());
			}
			else
			{
				glUniform1i(currentProgram->getUniformLocation(u_hasSkinning), 0);

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_bindMatrix), nodeOwner.getNumberJoints(), GL_FALSE, Matrix4x4().getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_bindNormalMatrix), nodeOwner.getNumberJoints(), GL_TRUE, Matrix3x3().getM());

				glUniformMatrix4fv(currentProgram->getUniformLocation(u_jointMatrix), nodeOwner.getNumberJoints(), GL_FALSE, Matrix4x4().getM());
				glUniformMatrix3fv(currentProgram->getUniformLocation(u_jointNormalMatrix), nodeOwner.getNumberJoints(), GL_TRUE, Matrix3x3().getM());
			}

			// Write bright color
			glUniform1i(currentProgram->getUniformLocation(u_writeBrightColor), nodeOwner.isWriteBrightColor());
			glUniform1f(currentProgram->getUniformLocation(u_brightColorLimit), nodeOwner.getBrightColorLimit());

			if (finalTransparent)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}

			glDrawElements(GL_TRIANGLES, currentSubMesh->getTriangleCount() * 3, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid *>(currentSubMesh->getIndicesOffset()*sizeof(uint32_t)));

			if (finalTransparent)
			{
				glDisable(GL_BLEND);
			}

			if (currentSurfaceMaterial->getDiffuseTextureName() != 0)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (currentSurfaceMaterial->getNormalMapTextureName() != 0)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (SkyManager::getInstance()->hasActiveSky())
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}

			glActiveTexture(GL_TEXTURE0);

			currentVAO->unbind();
		}
	}

	//

	vector<NodeSP>::const_iterator walker = allChilds.begin();

	int32_t i = 0;
	while (walker != allChilds.end())
	{
		(*walker)->render(nodeOwner, *instanceNode.getChild(i), newParentMatrix, time, animStackIndex, animLayerIndex);

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

void Node::updateInstanceNode(const InstanceNodeSP& instanceNode) const
{
	auto walker = allChilds.begin();

	while (walker != allChilds.end())
	{
		NodeSP childNode = *walker;

		InstanceNodeSP childInstanceNode = InstanceNodeSP(new InstanceNode(childNode->getName()));

		instanceNode->addChild(childInstanceNode);

		childNode->updateInstanceNode(childInstanceNode);

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

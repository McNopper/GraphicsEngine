/*
 * ModelEntity.cpp
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/debug/DebugDraw.h"
#include "../../layer1/event/EventManager.h"
#include "../../layer1/material/RefractiveIndices.h"

#include "ModelEntity.h"

using namespace std;

using namespace boost;

float ModelEntity::currentDeltaTime;
string ModelEntity::currentProgramType;

void ModelEntity::setCurrentValues(const string& currentProgramType, const CameraSP& currentCamera, float currentDeltaTime, bool ascendingSortOrder, enum RenderFilter renderFilter)
{
	OctreeEntity::setCurrentValues(currentCamera, ascendingSortOrder, renderFilter);
	ModelEntity::currentProgramType = currentProgramType;
	ModelEntity::currentDeltaTime = currentDeltaTime;
}

const string& ModelEntity::getCurrentProgramType() const
{
	return ModelEntity::currentProgramType;
}

int32_t ModelEntity::getNumberJoints() const
{
	return model->getNumberJoints();
}

ModelEntity::ModelEntity(const ModelSP& model, float scaleX, float scaleY, float scaleZ) :
	OctreeEntity(), NodeOwner(), translateX(0.0f), translateY(0.0f), translateZ(0.0f), angleX(0.0f), angleY(0.0f), angleZ(0.0f), scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ), modelMatrix(), normalModelMatrix(), updateNormalModelMatrix(true), position(), origin(), model(model), time(0.0f), writeBrightColor(false), brightColorLimit(1.0f), refractiveIndex(RI_AIR), debug(false), debugAsMesh(false), boundingSphere(), updateable(false), animStackIndex(-1), animLayerIndex(-1), rootInstanceNode()
{
	float maxScale = glusMaxf(scaleX, scaleY);
	maxScale = glusMaxf(maxScale, scaleZ);

	setBoundingSphere(BoundingSphere(model->getBoundingSphere().getCenter(), model->getBoundingSphere().getRadius() * maxScale));

	setUpdateable(model->isAnimated());

	if (model->isAnimated() && model->isSkinned())
	{
		model->getRootNode()->updateBindMatrix(bindMatrices, bindNormalMatrices);
		model->getRootNode()->updateJointMatrix(jointMatrices, jointNormalMatrices, Matrix4x4(), 0.0f, getAnimStackIndex(), getAnimLayerIndex());
	}

	rootInstanceNode = InstanceNodeSP(new InstanceNode(model->getRootNode()->getName()));
	model->getRootNode()->updateInstanceNode(rootInstanceNode);

	updateBoundingSphereCenter(true);
}

ModelEntity::~ModelEntity()
{
}

void ModelEntity::updateMetrics()
{
	modelMatrix.identity();
	modelMatrix.translate(translateX, translateY, translateZ);
	modelMatrix.rotateRzRyRx(angleZ, angleY, angleX);
	modelMatrix.scale(scaleX, scaleY, scaleZ);

	if (updateNormalModelMatrix)
	{
		normalModelMatrix = modelMatrix.extractMatrix3x3();
		normalModelMatrix.inverse();

		updateNormalModelMatrix = false;
	}
}

const BoundingSphere& ModelEntity::getBoundingSphere() const
{
	return boundingSphere;
}

void ModelEntity::setBoundingSphere(const BoundingSphere& boundingSphere)
{
	this->boundingSphere = boundingSphere;
}

const Point4& ModelEntity::getPosition() const
{
	return position;
}

void ModelEntity::setPosition(const Point4& position)
{
	this->translateX = position.getX();
	this->translateY = position.getY();
	this->translateZ = position.getZ();

	this->position = position;

	updateMetrics();

	updateBoundingSphereCenter(true);
}

void ModelEntity::setRotation(float angleX, float angleY, float angleZ)
{
	this->angleX = angleX;
	this->angleY = angleY;
	this->angleZ = angleZ;

	this->updateNormalModelMatrix = true;

	updateMetrics();
}

void ModelEntity::setScale(float scaleX, float scaleY, float scaleZ)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->updateNormalModelMatrix = true;

	updateMetrics();

	updateBoundingSphereCenter(true);
}

void ModelEntity::setMetrics(const Point4& position, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ)
{
	this->translateX = position.getX();
	this->translateY = position.getY();
	this->translateZ = position.getZ();

	this->position = position;

	this->angleX = angleX;
	this->angleY = angleY;
	this->angleZ = angleZ;

	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->updateNormalModelMatrix = true;

	updateMetrics();

	updateBoundingSphereCenter(true);
}

bool ModelEntity::isUpdateable() const
{
	return updateable;
}

void ModelEntity::setUpdateable(bool updateable)
{
	this->updateable = updateable;
}

void ModelEntity::setAnimation(int32_t animStackIndex, int32_t animLayerIndex) {
	this->animStackIndex = animStackIndex;
	this->animLayerIndex = animLayerIndex;
}

int32_t ModelEntity::getAnimStackIndex() const {
	return animStackIndex;
}

int32_t ModelEntity::getAnimLayerIndex() const {
	return animLayerIndex;
}

const Matrix4x4& ModelEntity::getModelMatrix() const
{
	return modelMatrix;
}

const Matrix3x3& ModelEntity::getNormalModelMatrix() const
{
	return normalModelMatrix;
}

void ModelEntity::updateBoundingSphereCenter(bool force)
{
	bool doUpdateBoundingSphereCenter = force;

	if (model->isAnimated())
	{
		time += ModelEntity::currentDeltaTime;

		float stopTime = model->getRootNode()->getStopTime(getAnimStackIndex(), getAnimLayerIndex());
		if (time > stopTime)
		{
			time -= stopTime;
		}

		doUpdateBoundingSphereCenter = true;
	}

	if (doUpdateBoundingSphereCenter)
	{
		Matrix4x4 skinningMatrix;
		if (model->isSkinned())
		{
			model->getRootNode()->updateSkinningMatrix(skinningMatrix, Matrix4x4(), time, getAnimStackIndex(), getAnimLayerIndex());
		}

		Matrix4x4 renderingMatrix;
		model->getRootNode()->updateRenderingMatrix(renderingMatrix, modelMatrix, time, getAnimStackIndex(), getAnimLayerIndex());

		Point4 center = renderingMatrix * skinningMatrix * Point4();

		setBoundingSphereCenter(center);
	}
}

void ModelEntity::updateDistanceToCamera()
{
	setDistanceToCamera(ModelEntity::currentCamera->distanceToCamera(boundingSphere));
}

void ModelEntity::update()
{
	if (model->isAnimated())
	{
		// Calculate skinning and pass later to shader
		if (model->isSkinned() && getAnimStackIndex() >= 0 && getAnimLayerIndex() >= 0)
		{
			model->getRootNode()->updateJointMatrix(jointMatrices, jointNormalMatrices, Matrix4x4(), time, getAnimStackIndex(), getAnimLayerIndex());
		}
	}
}

void ModelEntity::render() const
{
	model->getRootNode()->render(*this, *rootInstanceNode, modelMatrix, time, getAnimStackIndex(), getAnimLayerIndex());

	if (debug)
	{
		DebugDraw::drawer.draw(boundingSphere, Color::RED, debugAsMesh);
	}
}

const Matrix4x4* ModelEntity::getBindMatrices() const {
	return bindMatrices;
}

const Matrix3x3* ModelEntity::getBindNormalMatrices() const {
	return bindNormalMatrices;
}

const Matrix4x4* ModelEntity::getJointMatrices() const {
	return jointMatrices;
}

const Matrix3x3* ModelEntity::getJointNormalMatrices() const {
	return jointNormalMatrices;
}

bool ModelEntity::isWriteBrightColor() const
{
	return writeBrightColor;
}

float ModelEntity::getBrightColorLimit() const
{
	return brightColorLimit;
}

float ModelEntity::getRefractiveIndex() const
{
	return refractiveIndex;
}

void ModelEntity::setWriteBrightColor(bool writeBrightColor)
{
	this->writeBrightColor = writeBrightColor;
}

void ModelEntity::setBrightColorLimit(float brightColorLimit)
{
	this->brightColorLimit = brightColorLimit;
}

void ModelEntity::setRefractiveIndex(float refractiveIndex)
{
	this->refractiveIndex = refractiveIndex;
}

void ModelEntity::setBoundingSphereCenter(const Point4& center)
{
	boundingSphere.setCenter(center);
}

const ModelSP& ModelEntity::getModel() const
{
	return model;
}

InstanceNodeSP ModelEntity::findInstanceNodeRecursive(const string& name) const
{
	return rootInstanceNode->findChildRecursive(name);
}

ModelEntitySP ModelEntity::getNewInstance() const
{
	return ModelEntitySP(new ModelEntity(model, scaleX, scaleY, scaleZ));
}

bool ModelEntity::isDebug() const
{
	return debug;
}

void ModelEntity::setDebug(bool debug)
{
	this->debug = debug;
}

bool ModelEntity::isDebugAsMesh() const
{
	return debugAsMesh;
}

void ModelEntity::setDebugAsMesh(bool debugAsMesh)
{
	this->debugAsMesh = debugAsMesh;
}

/*
 * GeneralEntity.cpp
 *
 *  Created on: 11.05.2013
 *      Author: nopper
 */

#include "GeneralEntity.h"

using namespace std;

float GeneralEntity::currentDeltaTime;
string GeneralEntity::currentProgramType;

void GeneralEntity::setCurrentValues(const string& currentProgramType, const CameraSP& currentCamera, float currentDeltaTime, bool ascendingSortOrder, enum RenderFilter renderFilter, bool dynamicCubeMaps)
{
	OctreeEntity::setCurrentValues(currentCamera, ascendingSortOrder, renderFilter, dynamicCubeMaps);
	GeneralEntity::currentProgramType = currentProgramType;
	GeneralEntity::currentDeltaTime = currentDeltaTime;
}

GeneralEntity::GeneralEntity(const string& name, float scaleX, float scaleY, float scaleZ) : OctreeEntity(),
		position(), rotation(), scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ), modelMatrix(), normalModelMatrix(), updateNormalModelMatrix(true), wireframe(false), debug(false), debugAsMesh(false), boundingSphere(), usePositionAsBoundingSphereCenter(false), updateable(false), name(name), writeBrightColor(false), brightColorLimit(1.0f), refractiveIndex(RI_AIR)
{
}

GeneralEntity::~GeneralEntity()
{
}

void GeneralEntity::updateMetrics()
{
	modelMatrix.identity();
	modelMatrix.translate(position.getX(), position.getY(), position.getZ());
	modelMatrix *= rotation.getRotationMatrix4x4();
	modelMatrix.scale(scaleX, scaleY, scaleZ);

	if (updateNormalModelMatrix)
	{
		normalModelMatrix = modelMatrix.extractMatrix3x3();
		normalModelMatrix.inverse();

		updateNormalModelMatrix = false;
	}
}

void GeneralEntity::setBoundingSphereCenter(const Point4& center)
{
	if (usePositionAsBoundingSphereCenter)
	{
		boundingSphere.setCenter(position);
	}
	else
	{
		boundingSphere.setCenter(center);
	}
}

void GeneralEntity::updateDistanceToCamera()
{
	setDistanceToCamera(GeneralEntity::currentCamera->distanceToCamera(boundingSphere));
}

const BoundingSphere& GeneralEntity::getBoundingSphere() const
{
	return boundingSphere;
}

void GeneralEntity::setBoundingSphere(const BoundingSphere& boundingSphere)
{
	this->boundingSphere = boundingSphere;
}

const Point4& GeneralEntity::getPosition() const
{
	return position;
}

void GeneralEntity::setPosition(const Point4& position)
{
	this->position = position;

	updateMetrics();

	updateBoundingSphereCenter(true);
}

void GeneralEntity::setRotation(float angleX, float angleY, float angleZ)
{
	Quaternion rotation;
	rotation.rotateRzRyRxf(angleZ, angleY, angleX);

	this->rotation = rotation;

	this->updateNormalModelMatrix = true;

	updateMetrics();
}

void GeneralEntity::setScale(float scaleX, float scaleY, float scaleZ)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;

	this->updateNormalModelMatrix = true;

	updateMetrics();

	updateBoundingSphereCenter(true);
}

float GeneralEntity::getScaleX() const
{
	return scaleX;
}

float GeneralEntity::getScaleY() const
{
	return scaleY;
}

float GeneralEntity::getScaleZ() const
{
	return scaleZ;
}

void GeneralEntity::setRotation(const Quaternion& rotation)
{
	this->rotation = rotation;

	this->updateNormalModelMatrix = true;

	updateMetrics();
}

bool GeneralEntity::isUpdateable() const
{
	return updateable;
}

void GeneralEntity::setUpdateable(bool updateable)
{
	this->updateable = updateable;
}

const Matrix4x4& GeneralEntity::getModelMatrix() const
{
	return modelMatrix;
}

const Matrix3x3& GeneralEntity::getNormalModelMatrix() const
{
	return normalModelMatrix;
}

bool GeneralEntity::isWireframe() const
{
	return wireframe;
}

void GeneralEntity::setWireframe(bool wireframe)
{
	this->wireframe = wireframe;
}

bool GeneralEntity::isDebug() const
{
	return debug;
}

void GeneralEntity::setDebug(bool debug)
{
	this->debug = debug;
}

bool GeneralEntity::isDebugAsMesh() const
{
	return debugAsMesh;
}

void GeneralEntity::setDebugAsMesh(bool debugAsMesh)
{
	this->debugAsMesh = debugAsMesh;
}

bool GeneralEntity::isUsePositionAsBoundingSphereCenter() const
{
	return usePositionAsBoundingSphereCenter;
}

void GeneralEntity::setUsePositionAsBoundingSphereCenter(bool usePositionAsBoundingSphereCenter)
{
	this->usePositionAsBoundingSphereCenter = usePositionAsBoundingSphereCenter;

	updateBoundingSphereCenter(true);
}

const string& GeneralEntity::getName() const
{
	return name;
}

void GeneralEntity::setPositionRotation(const Point4& position, const Quaternion& rotation)
{
	this->position = position;
	this->rotation = rotation;

	this->updateNormalModelMatrix = true;

	updateMetrics();

	updateBoundingSphereCenter(true);
}

void GeneralEntity::setWriteBrightColor(bool writeBrightColor)
{
	this->writeBrightColor = writeBrightColor;
}

void GeneralEntity::setBrightColorLimit(float brightColorLimit)
{
	this->brightColorLimit = brightColorLimit;
}

void GeneralEntity::setRefractiveIndex(float refractiveIndex)
{
	this->refractiveIndex = refractiveIndex;
}



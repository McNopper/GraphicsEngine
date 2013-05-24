/*
 * Entity.cpp
 *
 *  Created on: 12.09.2012
 *      Author: nopper
 */

#include "Entity.h"

CameraSP Entity::currentCamera;
bool Entity::ascendingSortOrder = false;
enum RenderFilter Entity::renderFilter = RENDER_ALL;
bool Entity::dynamicCubeMaps = false;

Matrix4x4 Entity::viewMatrix[6];
Matrix4x4 Entity::projectionMatrix;

Entity::Entity() :
		distanceToCamera(0.0f)
{
}

Entity::~Entity()
{
}

bool Entity::operator <=(const Entity& other) const
{
	return distanceToCamera <= other.distanceToCamera;
}
bool Entity::operator >=(const Entity& other) const
{
	return distanceToCamera >= other.distanceToCamera;
}

void Entity::setCurrentValues(const CameraSP& currentCamera, bool ascendingSortOrder, enum RenderFilter renderFilter, bool dynamicCubeMaps)
{
	Entity::currentCamera = currentCamera;
	Entity::ascendingSortOrder = ascendingSortOrder;
	Entity::renderFilter = renderFilter;
	Entity::dynamicCubeMaps = dynamicCubeMaps;
}

const CameraSP& Entity::getCurrentCamera()
{
	return Entity::currentCamera;
}

bool Entity::isAscendingSortOrder()
{
	return Entity::ascendingSortOrder;
}

enum RenderFilter Entity::getRenderFilter()
{
	return Entity::renderFilter;
}

bool Entity::getDynamicCubeMaps()
{
	return Entity::dynamicCubeMaps;
}

float Entity::getDistanceToCamera() const
{
	return distanceToCamera;
}

void Entity::setDistanceToCamera(float distanceToCamera)
{
	this->distanceToCamera = distanceToCamera;
}

void Entity::setCubeMapViewMatrix(int32_t face, const Matrix4x4& matrix)
{
	viewMatrix[face] = matrix;
}

void Entity::setCubeMapProjectionMatrix(const Matrix4x4& matrix)
{
	projectionMatrix = matrix;
}

const Matrix4x4* Entity::getCubeMapViewMatrices()
{
	return viewMatrix;
}

const Matrix4x4& Entity::getCubeMapProjectionMatrix()
{
	return projectionMatrix;
}



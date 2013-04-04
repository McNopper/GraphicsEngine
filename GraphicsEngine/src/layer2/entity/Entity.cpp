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
bool Entity::modelTransformOnly = false;

Entity::Entity() :
		distanceToCamera(0.0f)
{
}

Entity::~Entity()
{
}

void Entity::setCurrentValues(const CameraSP& currentCamera, bool ascendingSortOrder, enum RenderFilter renderFilter, bool modelTransformOnly)
{
	Entity::currentCamera = currentCamera;
	Entity::ascendingSortOrder = ascendingSortOrder;
	Entity::renderFilter = renderFilter;
	Entity::modelTransformOnly = modelTransformOnly;
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

bool Entity::getModelTransformOnly()
{
	return Entity::modelTransformOnly;
}

float Entity::getDistanceToCamera() const
{
	return distanceToCamera;
}

void Entity::setDistanceToCamera(float distanceToCamera)
{
	this->distanceToCamera = distanceToCamera;
}



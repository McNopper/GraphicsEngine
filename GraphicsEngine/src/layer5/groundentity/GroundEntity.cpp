/*
 * GroundEntity.cpp
 *
 *  Created on: 13.05.2013
 *      Author: nopper
 */

#include "../../layer1/material/RefractiveIndices.h"

#include "GroundEntity.h"

using namespace boost;

using namespace std;

GroundEntity::GroundEntity(const string& name, const GroundSP& ground, float scaleX, float scaleY, float scaleZ) :
		GeneralEntity(name, scaleX, scaleY, scaleZ), writeBrightColor(false), brightColorLimit(1.0f), refractiveIndex(RI_AIR), ground(ground)
{
	float maxScale = glusMaxf(scaleX, scaleY);
	maxScale = glusMaxf(maxScale, scaleZ);

	setBoundingSphere(BoundingSphere(ground->getBoundingSphere().getCenter(), ground->getBoundingSphere().getRadius() * maxScale));

	setUpdateable(false);

	updateBoundingSphereCenter(true);
}

GroundEntity::~GroundEntity()
{
}

void GroundEntity::updateBoundingSphereCenter(bool force)
{
	// TODO Update the bounding sphere center e.g. if the plane was moved.
}

void GroundEntity::update()
{
	// TODO Update anything needed
}

void GroundEntity::render() const
{
	// TODO Render the ground plane with material etc.
}

void GroundEntity::setWriteBrightColor(bool writeBrightColor)
{
	this->writeBrightColor = writeBrightColor;
}

void GroundEntity::setBrightColorLimit(float brightColorLimit)
{
	this->brightColorLimit = brightColorLimit;
}

void GroundEntity::setRefractiveIndex(float refractiveIndex)
{
	this->refractiveIndex = refractiveIndex;
}

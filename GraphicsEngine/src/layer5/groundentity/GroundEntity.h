/*
 * GroundEntity.h
 *
 *  Created on: 13.05.2013
 *      Author: nopper
 */

#ifndef GROUNDENTITY_H_
#define GROUNDENTITY_H_

#include "../../UsedLibs.h"

#include "../../layer4/entity/GeneralEntity.h"
#include "../../layer4/ground/Ground.h"

class GroundEntity : public GeneralEntity
{

private:

	bool writeBrightColor;
	float brightColorLimit;

	float refractiveIndex;

	GroundSP ground;

public:

	GroundEntity(const std::string& name, const GroundSP& ground, float scaleX, float scaleY, float scaleZ);
	virtual ~GroundEntity();

	virtual void updateBoundingSphereCenter(bool force = false);
	virtual void update();
	virtual void render() const;

	virtual void setWriteBrightColor(bool writeBrightColor);
	virtual void setBrightColorLimit(float brightColorLimit);
	virtual void setRefractiveIndex(float refractiveIndex);

};

#endif /* GROUNDENTITY_H_ */

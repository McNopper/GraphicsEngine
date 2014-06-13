/*
 * GroundEntity.h
 *
 *  Created on: 13.05.2013
 *      Author: nopper
 */

#ifndef GROUNDENTITY_H_
#define GROUNDENTITY_H_

#include "../../UsedLibs.h"

#include "../../layer2/ground/Ground.h"
#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer7/entity/GeneralEntity.h"

class GroundEntity : public GeneralEntity
{

private:

	float repeat;

	float displacementScale;

	bool transparent;

	bool tessellate;

	float screenDistance;

	GroundSP ground;

	SurfaceMaterialSP surfaceMaterial;

public:

	GroundEntity(const std::string& name, const GroundSP& ground, const SurfaceMaterialSP& surfaceMaterial, float scaleX, float scaleY, float scaleZ);
	virtual ~GroundEntity();

	virtual void updateBoundingSphereCenter(bool force = false);
	virtual void update();
	virtual void render() const;

	const SurfaceMaterialSP& getSurfaceMaterial() const;

	void setSurfaceMaterial(const SurfaceMaterialSP& surfaceMaterial);

	float getRepeat() const;

	void setRepeat(float repeat);

	float getDisplacementScale() const;

	void setDisplacementScale(float displacementScale);

	bool isTransparent() const;

	void setTransparent(bool transparent);

	bool isTessellate() const;

	void setTessellate(bool tessellate);

	float getScreenDistance() const;

	void setScreenDistance(float screenDistance);

};

typedef std::shared_ptr<GroundEntity> GroundEntitySP;

#endif /* GROUNDENTITY_H_ */

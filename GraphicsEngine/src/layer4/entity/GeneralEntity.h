/*
 * GeneralEntity.h
 *
 *  Created on: 11.05.2013
 *      Author: nopper
 */

#ifndef GENERALENTITY_H_
#define GENERALENTITY_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Geometry.h"
#include "../../layer3/octree/OctreeEntity.h"

class GeneralEntity : public OctreeEntity, public Geometry
{

protected:

	static float currentDeltaTime;
	static std::string currentProgramType;

public:

	GeneralEntity();
	virtual ~GeneralEntity();

    static void setCurrentValues(const std::string& currentProgramType, const CameraSP& currentCamera, float currentDeltaTime, bool ascendingSortOrder = true, enum RenderFilter renderFilter = RENDER_ALL, bool dynamicCubeMaps = false);

	virtual const std::string& getName() const = 0;

    virtual bool isUpdateable() const = 0;
    virtual void setUpdateable(bool updateable) = 0;

    virtual bool isWriteBrightColor() const = 0;
    virtual float getBrightColorLimit() const = 0;
    virtual float getRefractiveIndex() const = 0;

    virtual void setWriteBrightColor(bool writeBrightColor) = 0;
    virtual void setBrightColorLimit(float brightColorLimit) = 0;
    virtual void setRefractiveIndex(float refractiveIndex) = 0;

};

typedef boost::shared_ptr<GeneralEntity> GeneralEntitySP;

#endif /* GENERALENTITY_H_ */

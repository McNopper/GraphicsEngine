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
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Matrix3x3.h"
#include "../../layer1/collision/BoundingSphere.h"
#include "../../layer3/octree/OctreeEntity.h"

class GeneralEntity : public OctreeEntity, public Geometry
{

private:

		float translateX;
		float translateY;
		float translateZ;
		Quaternion rotation;
		float scaleX;
		float scaleY;
		float scaleZ;
		Matrix4x4 modelMatrix;
		Matrix3x3 normalModelMatrix;
		bool updateNormalModelMatrix;

		Point4 position;
		Point4 origin;

		bool debug;

		bool debugAsMesh;

		BoundingSphere boundingSphere;
		bool usePositionAsBoundingSphereCenter;
		bool updateable;

		std::string name;

protected:

	static float currentDeltaTime;
	static std::string currentProgramType;

	void updateMetrics();

    void setBoundingSphereCenter(const Point4& center);

public:

	GeneralEntity(const std::string& name, float scaleX, float scaleY, float scaleZ);
	virtual ~GeneralEntity();

    static void setCurrentValues(const std::string& currentProgramType, const CameraSP& currentCamera, float currentDeltaTime, bool ascendingSortOrder = true, enum RenderFilter renderFilter = RENDER_ALL, bool dynamicCubeMaps = false);

	virtual void updateDistanceToCamera();

    virtual const BoundingSphere & getBoundingSphere() const;
    void setBoundingSphere(const BoundingSphere& boundingSphere);

    const Point4& getPosition() const;
    void setPosition(const Point4& position);

    void setRotation(float angleX, float angleY, float angleZ);
    void setRotation(const Quaternion& rotation);

    void setScale(float scaleX, float scaleY, float scaleZ);

    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;

    void setMetrics(const Point4& position, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ);
    void setMetrics(const Point4& position, const Quaternion& rotation, float scaleX, float scaleY, float scaleZ);

    virtual bool isUpdateable() const;
    virtual void setUpdateable(bool updateable);

	const Matrix4x4& getModelMatrix() const;

	const Matrix3x3& getNormalModelMatrix() const;

	bool isDebug() const;

	void setDebug(bool debug);

	bool isDebugAsMesh() const;

	void setDebugAsMesh(bool debugAsMesh);

	bool isUsePositionAsBoundingSphereCenter() const;

	void setUsePositionAsBoundingSphereCenter(bool useCenterBoundingSphereCenter);

	virtual const std::string& getName() const;

	//

	virtual void updateLocation(const Point4& location);

	virtual void updateOrientation(const Quaternion& orientation);

	virtual void updateLocationOrientation(const Point4& location, const Quaternion& orientation);

	//

    virtual bool isWriteBrightColor() const = 0;
    virtual float getBrightColorLimit() const = 0;
    virtual float getRefractiveIndex() const = 0;

    virtual void setWriteBrightColor(bool writeBrightColor) = 0;
    virtual void setBrightColorLimit(float brightColorLimit) = 0;
    virtual void setRefractiveIndex(float refractiveIndex) = 0;

};

typedef boost::shared_ptr<GeneralEntity> GeneralEntitySP;

#endif /* GENERALENTITY_H_ */

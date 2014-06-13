/*
 * GeneralEntity.h
 *
 *  Created on: 11.05.2013
 *      Author: nopper
 */

#ifndef GENERALENTITY_H_
#define GENERALENTITY_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Matrix3x3.h"
#include "../../layer1/collision/BoundingSphere.h"
#include "../../layer2/material/RefractiveIndices.h"
#include "../../layer6/octree/OctreeEntity.h"

class GeneralEntity : public OctreeEntity
{

private:

		Point4 position;

		Quaternion rotation;

		float scaleX;
		float scaleY;
		float scaleZ;

		Matrix4x4 modelMatrix;
		Matrix3x3 normalModelMatrix;
		bool updateNormalModelMatrix;

		bool wireframe;

		bool debug;

		bool debugAsMesh;

		BoundingSphere boundingSphere;
		bool usePositionAsBoundingSphereCenter;

		bool updateable;

		std::string name;

protected:

	static float currentDeltaTime;
	static std::string currentProgramType;

	bool writeBrightColor;
	float brightColorLimit;

	float refractiveIndex;

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
    virtual void setPosition(const Point4& position);

    virtual void setRotation(float angleX, float angleY, float angleZ);
    virtual void setRotation(const Quaternion& rotation);

	virtual void setPositionRotation(const Point4& position, const Quaternion& rotation);

	virtual void setScale(float scaleX, float scaleY, float scaleZ);

    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;

    virtual bool isUpdateable() const;
    virtual void setUpdateable(bool updateable);

	const Matrix4x4& getModelMatrix() const;

	const Matrix3x3& getNormalModelMatrix() const;

	bool isWireframe() const;

	void setWireframe(bool wireframe);

	bool isDebug() const;

	void setDebug(bool debug);

	bool isDebugAsMesh() const;

	void setDebugAsMesh(bool debugAsMesh);

	bool isUsePositionAsBoundingSphereCenter() const;

	void setUsePositionAsBoundingSphereCenter(bool useCenterBoundingSphereCenter);

	virtual const std::string& getName() const;

	//

    void setWriteBrightColor(bool writeBrightColor);
    void setBrightColorLimit(float brightColorLimit);
    void setRefractiveIndex(float refractiveIndex);

};

typedef std::shared_ptr<GeneralEntity> GeneralEntitySP;

#endif /* GENERALENTITY_H_ */

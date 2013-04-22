/*
 * ModelEntity.h
 *
 *  Created on: 22.04.2011
 *      Author: Norbert Nopper
 */

#ifndef MODELENTITY_H_
#define MODELENTITY_H_

#define MAX_MATRICES 64

#include "../../UsedLibs.h"

#include "../../layer0/math/Geometry.h"
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Matrix3x3.h"
#include "../../layer1/collision/BoundingSphere.h"
#include "../../layer3/node/InstanceNode.h"
#include "../../layer3/node/NodeOwner.h"
#include "../../layer3/octree/OctreeEntity.h"
#include "../../layer4/model/Model.h"

class ModelEntity : public OctreeEntity, public NodeOwner, public Geometry
{

protected:

	static float currentDeltaTime;
	static std::string currentProgramType;

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

	ModelSP model;

	float time;

	Matrix4x4 bindMatrices[MAX_MATRICES];
	Matrix3x3 bindNormalMatrices[MAX_MATRICES];
	Matrix4x4 jointMatrices[MAX_MATRICES];
	Matrix3x3 jointNormalMatrices[MAX_MATRICES];

	bool writeBrightColor;
	float brightColorLimit;

	float refractiveIndex;

	bool debug;

	bool debugAsMesh;

private:

	BoundingSphere boundingSphere;
	bool updateable;
	boost::int32_t animStackIndex;
	boost::int32_t animLayerIndex;
	InstanceNodeSP rootInstanceNode;

	std::string name;

	boost::int32_t jointIndex;

protected:

	void updateMetrics();

    void setBoundingSphereCenter(const Point4& center);

public:

    static void setCurrentValues(const std::string& currentProgramType, const CameraSP& currentCamera, float currentDeltaTime, bool ascendingSortOrder = true, enum RenderFilter renderFilter = RENDER_ALL, bool dynamicCubeMaps = false);

    virtual const std::string& getCurrentProgramType() const;

    virtual boost::int32_t getNumberJoints() const;

	ModelEntity(const std::string& name, const ModelSP& model, float scaleX, float scaleY, float scaleZ);
	virtual ~ModelEntity();

    virtual void updateBoundingSphereCenter(bool force = false);
	virtual void updateDistanceToCamera();
    virtual void update();
    virtual void render() const;

    virtual const BoundingSphere & getBoundingSphere() const;
    void setBoundingSphere(const BoundingSphere& boundingSphere);

    const Point4& getPosition() const;
    void setPosition(const Point4& position);

    void setRotation(float angleX, float angleY, float angleZ);
    void setRotation(const Quaternion& rotation);

    void setScale(float scaleX, float scaleY, float scaleZ);

    void setMetrics(const Point4& position, float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ);
    void setMetrics(const Point4& position, const Quaternion& rotation, float scaleX, float scaleY, float scaleZ);

    bool isUpdateable() const;
    void setUpdateable(bool updateable);

	void setAnimation(boost::int32_t animStackIndex, boost::int32_t animLayerIndex);

	boost::int32_t getAnimStackIndex() const;
	boost::int32_t getAnimLayerIndex() const;

	const Matrix4x4& getModelMatrix() const;

	const Matrix3x3& getNormalModelMatrix() const;

    const ModelSP& getModel() const;

    virtual const Matrix4x4* getBindMatrices() const;
    virtual const Matrix3x3* getBindNormalMatrices() const;
    virtual const Matrix4x4* getJointMatrices() const;
    virtual const Matrix3x3* getJointNormalMatrices() const;

    virtual bool isWriteBrightColor() const;
    virtual float getBrightColorLimit() const;
    virtual float getRefractiveIndex() const;

    void setWriteBrightColor(bool writeBrightColor);
    void setBrightColorLimit(float brightColorLimit);
    void setRefractiveIndex(float refractiveIndex);

    const boost::shared_ptr<InstanceNode>& getRootInstanceNode() const;

    boost::shared_ptr<InstanceNode> findInstanceNodeRecursive(const std::string& name) const;

    boost::shared_ptr<ModelEntity> getNewInstance(const std::string& name) const;

	bool isDebug() const;

	void setDebug(bool debug);

	bool isDebugAsMesh() const;

	void setDebugAsMesh(bool debugAsMesh);

	const std::string& getName() const;

	//

	virtual void updateLocation(const Point4& location);

	virtual void updateOrientation(const Quaternion& orientation);

	virtual void updateLocationOrientation(const Point4& location, const Quaternion& orientation);

};

typedef boost::shared_ptr<ModelEntity> ModelEntitySP;

#endif /* MODELENTITY_H_ */

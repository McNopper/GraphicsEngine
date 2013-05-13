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

#include "../../layer3/environment/DynamicEnvironment.h"
#include "../../layer3/node/InstanceNode.h"
#include "../../layer3/node/NodeOwner.h"
#include "../../layer4/entity/GeneralEntity.h"
#include "../../layer4/model/Model.h"

class ModelEntity : public GeneralEntity, public NodeOwner
{

	bool writeBrightColor;
	float brightColorLimit;

	float refractiveIndex;

	ModelSP model;

	float time;

	Matrix4x4 bindMatrices[MAX_MATRICES];
	Matrix3x3 bindNormalMatrices[MAX_MATRICES];
	Matrix4x4 jointMatrices[MAX_MATRICES];
	Matrix3x3 jointNormalMatrices[MAX_MATRICES];

private:

	boost::int32_t animStackIndex;
	boost::int32_t animLayerIndex;
	InstanceNodeSP rootInstanceNode;

	boost::int32_t jointIndex;

public:

    virtual const std::string& getCurrentProgramType() const;

    virtual boost::int32_t getNumberJoints() const;

	ModelEntity(const std::string& name, const ModelSP& model, float scaleX, float scaleY, float scaleZ);
	virtual ~ModelEntity();

    virtual void updateBoundingSphereCenter(bool force = false);
    virtual void update();
    virtual void render() const;

	void setAnimation(boost::int32_t animStackIndex, boost::int32_t animLayerIndex);

	boost::int32_t getAnimStackIndex() const;
	boost::int32_t getAnimLayerIndex() const;

    const ModelSP& getModel() const;

    virtual const Matrix4x4* getBindMatrices() const;
    virtual const Matrix3x3* getBindNormalMatrices() const;
    virtual const Matrix4x4* getJointMatrices() const;
    virtual const Matrix3x3* getJointNormalMatrices() const;

    virtual bool isWriteBrightColor() const;
    virtual float getBrightColorLimit() const;
    virtual float getRefractiveIndex() const;

    virtual void setWriteBrightColor(bool writeBrightColor);
    virtual void setBrightColorLimit(float brightColorLimit);
    virtual void setRefractiveIndex(float refractiveIndex);

    const boost::shared_ptr<InstanceNode>& getRootInstanceNode() const;

    boost::shared_ptr<InstanceNode> findInstanceNodeRecursive(const std::string& name) const;

    boost::shared_ptr<ModelEntity> getNewInstance(const std::string& name) const;

};

typedef boost::shared_ptr<ModelEntity> ModelEntitySP;

#endif /* MODELENTITY_H_ */

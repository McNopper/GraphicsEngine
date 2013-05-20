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

private:

	ModelSP model;

	float time;

	Matrix4x4 bindMatrices[MAX_MATRICES];
	Matrix3x3 bindNormalMatrices[MAX_MATRICES];
	Matrix4x4 jointMatrices[MAX_MATRICES];
	Matrix3x3 jointNormalMatrices[MAX_MATRICES];

	boost::int32_t animStackIndex;
	boost::int32_t animLayerIndex;
	InstanceNodeSP rootInstanceNode;

	boost::int32_t jointIndex;

	bool dirty;

public:

    virtual const std::string& getCurrentProgramType() const;

    virtual boost::int32_t getNumberJoints() const;

	ModelEntity(const std::string& name, const ModelSP& model, float scaleX, float scaleY, float scaleZ);
	virtual ~ModelEntity();

    virtual void updateBoundingSphereCenter(bool force = false);
    virtual void update();
    virtual void render() const;

	void setAnimation(boost::int32_t animStackIndex, boost::int32_t animLayerIndex);

    const ModelSP& getModel() const;

    const boost::shared_ptr<InstanceNode>& getRootInstanceNode() const;

    boost::shared_ptr<InstanceNode> findInstanceNodeRecursive(const std::string& name) const;

    boost::shared_ptr<ModelEntity> getNewInstance(const std::string& name) const;

    //

    virtual void renderNode(const Node& node, const InstanceNode& instanceNode, float time, boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;

};

typedef boost::shared_ptr<ModelEntity> ModelEntitySP;

#endif /* MODELENTITY_H_ */

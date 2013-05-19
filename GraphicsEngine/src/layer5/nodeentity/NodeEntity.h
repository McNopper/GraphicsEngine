/*
 * NodeEntity.h
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#ifndef NODEENTITY_H_
#define NODEENTITY_H_

#include "../../UsedLibs.h"

#include "../../layer3/node/Node.h"
#include "../../layer3/node/NodeOwner.h"
#include "../../layer4/entity/GeneralEntity.h"

class NodeEntity : public GeneralEntity, public NodeOwner
{

private:

	NodeSP rootNode;

	float time;

	boost::int32_t animStackIndex;
	boost::int32_t animLayerIndex;
	InstanceNodeSP rootInstanceNode;

	bool dirty;

public:

	NodeEntity(const std::string& name, const NodeSP& rootNode, float scaleX, float scaleY, float scaleZ, bool updateable);
	virtual ~NodeEntity();

	void setAnimation(boost::int32_t animStackIndex, boost::int32_t animLayerIndex);

	boost::int32_t getAnimStackIndex() const;
	boost::int32_t getAnimLayerIndex() const;

    virtual void updateBoundingSphereCenter(bool force = false);
    virtual void update();
    virtual void render() const;

	virtual const std::string& getCurrentProgramType() const;

	virtual boost::int32_t getNumberJoints() const;

    virtual const Matrix4x4* getBindMatrices() const;
    virtual const Matrix3x3* getBindNormalMatrices() const;
    virtual const Matrix4x4* getJointMatrices() const;
    virtual const Matrix3x3* getJointNormalMatrices() const;

    virtual bool isWriteBrightColor() const;
    virtual float getBrightColorLimit() const;

    virtual float getRefractiveIndex() const;

};

typedef boost::shared_ptr<NodeEntity> NodeEntitySP;

#endif /* NODEENTITY_H_ */

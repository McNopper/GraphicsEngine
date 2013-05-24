/*
 * NodeEntity.h
 *
 *  Created on: 19.05.2013
 *      Author: nopper
 */

#ifndef NODEENTITY_H_
#define NODEENTITY_H_

#include "../../UsedLibs.h"

#include "../../layer5/node/InstanceNode.h"
#include "../../layer5/node/Node.h"
#include "../../layer5/node/NodeOwner.h"
#include "../../layer6/entity/GeneralEntity.h"

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

	//

    virtual void updateBoundingSphereCenter(bool force = false);
    virtual void update();
    virtual void render() const;

    //

    virtual void renderNode(const Node& node, const InstanceNode& instanceNode, float time, boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;
};

typedef boost::shared_ptr<NodeEntity> NodeEntitySP;

#endif /* NODEENTITY_H_ */

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

#include "../../layer5/environment/DynamicEnvironment.h"
#include "../../layer5/node/InstanceNode.h"
#include "../../layer5/node/NodeOwner.h"
#include "../../layer6/model/Model.h"
#include "../../layer7/entity/GeneralEntity.h"

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

	std::vector<InstanceNodeSP> allLights;

	std::vector<InstanceNodeSP> allCameras;

	Color ambientLightColor;

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

    const InstanceNodeSP& getRootInstanceNode() const;

    InstanceNodeSP findInstanceNodeRecursive(const std::string& name) const;

    boost::shared_ptr<ModelEntity> getNewInstance(const std::string& name) const;

    //

    virtual void renderNode(const Node& node, const InstanceNode& instanceNode, float time, boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;

    virtual void addLightNode(const InstanceNodeSP& lightNode);

    virtual void addCameraNode(const InstanceNodeSP& cameraNode);

    //

    boost::int32_t setLights(boost::int32_t lightNumber) const;

    bool setCamera(const std::string& name) const;

    //

    void passCamerasToManager() const;

    void passLightsToManager() const;

	const Color& getAmbientLightColor() const;

	void setAmbientLightColor(const Color& ambientLightColor);

};

typedef boost::shared_ptr<ModelEntity> ModelEntitySP;

#endif /* MODELENTITY_H_ */

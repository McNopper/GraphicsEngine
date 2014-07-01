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

#include "../../layer4/shadow/OrthographicCameraCascadedShadowMap2D.h"
#include "../../layer4/shadow/OrthographicCameraShadowMap2D.h"
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

	Matrix4x4 inverseBindMatrices[MAX_MATRICES];
	Matrix3x3 inverseBindNormalMatrices[MAX_MATRICES];
	Matrix4x4 bindMatrices[MAX_MATRICES];
	Matrix3x3 bindNormalMatrices[MAX_MATRICES];

	std::int32_t animStackIndex;
	std::int32_t animLayerIndex;
	InstanceNodeSP rootInstanceNode;

	std::int32_t jointIndex;

	bool dirty;

	std::vector<InstanceNodeSP> allLights;

	std::vector<InstanceNodeSP> allCameras;

	Color ambientLightColor;

public:

    virtual const std::string& getCurrentProgramType() const;

    virtual std::int32_t getNumberJoints() const;

	ModelEntity(const std::string& name, const ModelSP& model, float scaleX, float scaleY, float scaleZ);
	virtual ~ModelEntity();

    virtual void updateBoundingSphereCenter(bool force = false);
    virtual void update();
    virtual void render() const;

	void setAnimation(std::int32_t animStackIndex, std::int32_t animLayerIndex);

    const ModelSP& getModel() const;

    const InstanceNodeSP& getRootInstanceNode() const;

    InstanceNodeSP findInstanceNodeRecursive(const std::string& name) const;

    std::shared_ptr<ModelEntity> getNewInstance(const std::string& name) const;

    //

    virtual void renderNode(const Node& node, const InstanceNode& instanceNode, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

    virtual void addLightNode(const InstanceNodeSP& lightNode);

    virtual void addCameraNode(const InstanceNodeSP& cameraNode);

    //

    std::int32_t setLights(std::int32_t lightNumber) const;

    CameraSP getCamera(const std::string& name) const;

    bool setCamera(const std::string& name) const;

    bool setOrthographicCameraShadowMap(const std::string& lightName, const OrthographicCameraShadowMap2DSP& orthographicCameraShadowMap2D) const;

    bool setOrthographicCameraCascadedShadowMap(const std::string& lightName, const CameraSP& camera, const OrthographicCameraCascadedShadowMap2DSP& orthographicCameraCascadedShadowMap2D, std::int32_t section) const;

    //

    void passCamerasToManager() const;

    void passLightsToManager() const;

	const Color& getAmbientLightColor() const;

	void setAmbientLightColor(const Color& ambientLightColor);

	//

	const Matrix4x4& getInverseBindMatrix(int32_t index) const;

	const Matrix3x3& getInverseBindNormalMatrix(int32_t index) const;

};

typedef std::shared_ptr<ModelEntity> ModelEntitySP;

#endif /* MODELENTITY_H_ */

/*
 * Node.h
 *
 *  Created on: 14.05.2012
 *      Author: nopper
 */

#ifndef NODE_H_
#define NODE_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix3x3.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer3/animation/AnimationStack.h"
#include "../../layer3/camera/Camera.h"
#include "../../layer3/light/Light.h"
#include "../../layer3/mesh/Mesh.h"
#include "InstanceNode.h"
#include "NodeOwner.h"

class NodeOwner;

class Node
{

	friend class NodeBuilder;
	friend class NodeTreeFactory;
	friend class InstanceNode;

private:

	std::string name;

	std::shared_ptr<Node> parentNode;

	Matrix4x4 transformMatrix;
	Matrix4x4 transformLinkMatrix;

	Matrix4x4 rotationOffsetMatrix;
	Matrix4x4 rotationPivotMatrix;
	Matrix4x4 preRotationMatrix;
	Matrix4x4 postRotationMatrix;
	Matrix4x4 inverseRotationPivotMatrix;

	Matrix4x4 scalingOffsetMatrix;
	Matrix4x4 scalingPivotMatrix;
	Matrix4x4 inverseScalingPivotMatrix;

	Matrix4x4 geometricTransformMatrix;

	Matrix4x4 localFinalMatrix;

	float LclTranslation[3];
	float LclRotation[3];
	float LclScaling[3];

	float RotationOffset[3];
	float RotationPivot[3];
	float PreRotation[3];
	float PostRotation[3];

	float ScalingOffset[3];
	float ScalingPivot[3];

	float GeometricTranslation[3];
	float GeometricRotation[3];
	float GeometricScaling[3];

	MeshSP mesh;

	CameraSP camera;

	LightSP light;

	std::vector<std::shared_ptr<AnimationStack> > allAnimStacks;

	std::vector<std::shared_ptr<Node> > allChilds;

	std::int32_t index;

	bool joint;

	bool translationMinActive[3];
	bool translationMaxActive[3];
	float translationMin[3];
	float translationMax[3];

	bool rotationMinActive[3];
	bool rotationMaxActive[3];
	float rotationMin[3];
	float rotationMax[3];

	bool scalingMinActive[3];
	bool scalingMaxActive[3];
	float scalingMin[3];
	float scalingMax[3];

	bool usedJoint;

	bool visible;

	bool transparent;

	std::int32_t createIndex(std::int32_t index);

	std::int32_t countIndex(std::int32_t index);

	void setTransformMatrix(const std::string& jointName, const Matrix4x4& matrix);
	void setTransformLinkMatrix(const std::string& jointName, const Matrix4x4& matrix);

	void addChild(const std::shared_ptr<Node>& child);

	float getLimit(const float value[], const bool minActive[], const float min[], const bool maxActive[], const float max[], std::int32_t index) const;

	void setTranslationLimits(bool minActive, float min, bool maxActive, float max, std::int32_t index);
	void setRotationLimits(bool minActive, float min, bool maxActive, float max, std::int32_t index);
	void setScalingLimits(bool minActive, float min, bool maxActive, float max, std::int32_t index);

	void setUsedJoint(const std::string& jointName);

	void updateLocalFinalMatrix();

public:

	Node(const std::string& name, const std::shared_ptr<Node>& parent, float LclTranslation[3], float RotationOffset[3], float RotationPivot[3], float PreRotation[3], float LclRotation[3], float PostRotation[3], float ScalingOffset[3], float ScalingPivot[3], float LclScaling[3], float GeometricTranslation[3], float GeometricRotation[3], float GeometricScaling[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks, bool joint);
	virtual ~Node();

	const MeshSP& getMesh() const;

	const CameraSP& getCamera() const;

	const LightSP& getLight() const;

	std::uint32_t getChildCount() const;
	const std::shared_ptr<Node>& getChild(std::int32_t i) const;
	const std::shared_ptr<Node>& getChild(const std::string& name) const;

	std::shared_ptr<Node> findChildRecursive(const std::string& name) const;

	const std::shared_ptr<Node>& getParentNode() const;

	std::int32_t getIndex() const;
	std::int32_t getIndexRecursive(const std::string& name) const;

	const std::string& getName() const;

	bool isAnimated() const;

	std::int32_t getSkinningRootIndex() const;

	bool updateRenderingMatrix(Matrix4x4& matrix, const Matrix4x4& parentMatrix, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void updateBindMatrix(Matrix4x4* allBindMatrices, Matrix3x3* allBindNormalMatrices) const;

	void updateJointMatrix(Matrix4x4* allJointMatrices, Matrix3x3* allJointNormalMatrices, const Matrix4x4& parentMatrix, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void updateRenderMatrix(const NodeOwner& nodeOwner, InstanceNode& instanceNode, const Matrix4x4& parentMatrix, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void render(const NodeOwner& nodeOwner, const InstanceNode& instanceNode, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	const Matrix4x4& getGeometricTransform() const;

	const Matrix4x4& getLocalFinalMatrix() const;

	float getStopTime(std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void updateInstanceNode(NodeOwner& nodeOwner, const InstanceNodeSP& instanceNode) const;

	bool isTransparent() const;
	void setTransparent(bool transparent);
	void setTransparentRecursive(bool transparent);

	bool isVisible() const;
	void setVisible(bool visible);
	void setVisibleRecursive(bool transparent);

	const std::vector<std::shared_ptr<AnimationStack> >& getAllAnimStacks() const;

	const float* getGeometricRotation() const;
	const float* getGeometricScaling() const;
	const float* getGeometricTranslation() const;
	const float* getLclRotation() const;
	const float* getLclScaling() const;
	const float* getLclTranslation() const;
	const float* getPostRotation() const;
	const float* getPreRotation() const;
	const float* getRotationMax() const;
	const bool* getRotationMaxActive() const;
	const float* getRotationMin() const;
	const bool* getRotationMinActive() const;
	const float* getRotationOffset() const;
	const float* getRotationPivot() const;
	const float* getScalingMax() const;
	const bool* getScalingMaxActive() const;
	const float* getScalingMin() const;
	const bool* getScalingMinActive() const;
	const float* getScalingOffset() const;
	const float* getScalingPivot() const;
	const float* getTranslationMax() const;
	const bool* getTranslationMaxActive() const;
	const float* getTranslationMin() const;
	const bool* getTranslationMinActive() const;

};

typedef std::shared_ptr<Node> NodeSP;

#endif /* NODE_H_ */

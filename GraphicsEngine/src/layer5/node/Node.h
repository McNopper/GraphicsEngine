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

	//

	float LclTranslation[3];
	float LclRotation[3];
	float LclScaling[3];

	Matrix4x4 postTranslationMatrix;
	Matrix4x4 postRotationMatrix;
	Matrix4x4 postScalingMatrix;

	Matrix4x4 geometricTransformMatrix;

	//

	MeshSP mesh;

	CameraSP camera;

	LightSP light;

	//

	bool visible;

	bool transparent;

	//

	bool joint;

	std::int32_t jointIndex;

	Matrix4x4 inverseBindMatrix;

	//

	std::vector<std::shared_ptr<AnimationStack> > allAnimStacks;

	//

	std::vector<std::shared_ptr<Node> > allChilds;

	//

	void setJoint(const std::string& jointName);

	std::int32_t createJointIndex(std::int32_t index);

	std::int32_t countJointIndex(std::int32_t index);

	void setInverseBindMatrix(const std::string& jointName, const Matrix4x4& inverseBindMatrix);

	//

	void addChild(const std::shared_ptr<Node>& child);

public:

	Node(const std::string& name, const std::shared_ptr<Node>& parent, const float LclTranslation[3], const float RotationOffset[3], const float RotationPivot[3], const float PreRotation[3], const float LclRotation[3], const float PostRotation[3], const float ScalingOffset[3], const float ScalingPivot[3], const float LclScaling[3], const float GeometricTranslation[3], const float GeometricRotation[3], const float GeometricScaling[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);
	Node(const std::string& name, const std::shared_ptr<Node>& parent, const float LclTranslation[3], const Matrix4x4& postTranslation, const float LclRotation[3], const Matrix4x4& postRotation, const float LclScaling[3], const Matrix4x4& postScaling, const Matrix4x4& geometricTransform, const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);
	virtual ~Node();

	const MeshSP& getMesh() const;

	const CameraSP& getCamera() const;

	const LightSP& getLight() const;

	std::uint32_t getChildCount() const;
	const std::shared_ptr<Node>& getChild(std::int32_t i) const;
	const std::shared_ptr<Node>& getChild(const std::string& name) const;

	std::shared_ptr<Node> findChildRecursive(const std::string& name) const;

	const std::shared_ptr<Node>& getParentNode() const;

	std::int32_t getJointIndex() const;
	std::int32_t getJointIndexRecursive(const std::string& name) const;

	const std::string& getName() const;

	bool isAnimated() const;

	std::int32_t getRootJointIndex() const;

	bool updateBoundingSphereMatrix(Matrix4x4& matrix, const Matrix4x4& parentMatrix, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void updateInverseBindMatrix(Matrix4x4* allInverseBindMatrices, Matrix3x3* allInverseBindNormalMatrices) const;

	void updateBindMatrix(Matrix4x4* allBindMatrices, Matrix3x3* allBindNormalMatrices, const Matrix4x4& parentMatrix, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void updateRenderMatrix(const NodeOwner& nodeOwner, InstanceNode& instanceNode, const Matrix4x4& parentMatrix, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void render(const NodeOwner& nodeOwner, const InstanceNode& instanceNode, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	//

	const Matrix4x4& getPostTranslationMatrix() const;
	const Matrix4x4& getPostRotationMatrix() const;
	const Matrix4x4& getPostScalingMatrix() const;

	const Matrix4x4& getGeometricTransformMatrix() const;

	//

	void calculateAnimation(float* currentTranslation, float* currentRotation, float* currentScaling, float time, std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void calculateLocalMatrix(Matrix4x4& matrix, const float* translation = nullptr, const float* rotation = nullptr, const float* scaling = nullptr) const;

	//

	float getStopTime(std::int32_t animStackIndex, std::int32_t animLayerIndex) const;

	void updateInstanceNode(NodeOwner& nodeOwner, const InstanceNodeSP& instanceNode) const;

	bool isTransparent() const;
	void setTransparent(bool transparent);
	void setTransparentRecursive(bool transparent);

	bool isVisible() const;
	void setVisible(bool visible);
	void setVisibleRecursive(bool transparent);

	const std::vector<std::shared_ptr<AnimationStack> >& getAllAnimStacks() const;

	const float* getLclRotation() const;
	const float* getLclScaling() const;
	const float* getLclTranslation() const;

};

typedef std::shared_ptr<Node> NodeSP;

#endif /* NODE_H_ */

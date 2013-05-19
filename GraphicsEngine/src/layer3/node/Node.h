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
#include "../../layer1/camera/Camera.h"
#include "../../layer1/light/Light.h"
#include "../../layer2/animation/AnimationStack.h"
#include "../../layer2/mesh/Mesh.h"
#include "InstanceNode.h"
#include "NodeOwner.h"

class Node
{

	friend class NodeBuilder;
	friend class NodeTreeFactory;
	friend class InstanceNode;

private:

	std::string name;

	boost::shared_ptr<Node> parentNode;

	Matrix4x4 transformMatrix;
	Matrix4x4 transformLinkMatrix;

	Matrix4x4 rotateOffsetMatrix;
	Matrix4x4 rotatePivotMatrix;
	Matrix4x4 preRotateMatrix;
	Matrix4x4 postRotateMatrix;
	Matrix4x4 inverseRotatePivotMatrix;

	Matrix4x4 scaleOffsetMatrix;
	Matrix4x4 scalePivotMatrix;
	Matrix4x4 inverseScalePivotMatrix;

	Matrix4x4 geometricTransformMatrix;

	Matrix4x4 localFinalMatrix;

	float translate[3];
	float rotate[3];
	float scale[3];

	MeshSP mesh;

	CameraSP camera;

	LightSP light;

	std::vector<boost::shared_ptr<AnimationStack> > allAnimStacks;

	std::vector<boost::shared_ptr<Node> > allChilds;

	boost::int32_t index;

	bool joint;

	bool transMinActive[3];
	bool transMaxActive[3];
	float minTrans[3];
	float maxTrans[3];

	bool rotMinActive[3];
	bool rotMaxActive[3];
	float minRot[3];
	float maxRot[3];

	bool scaleMinActive[3];
	bool scaleMaxActive[3];
	float minScale[3];
	float maxScale[3];

	bool usedJoint;

	bool visible;

	bool transparent;

	boost::int32_t createIndex(boost::int32_t index);

	boost::int32_t countIndex(boost::int32_t index);

	void setTransformMatrix(const std::string& jointName, const Matrix4x4& matrix);
	void setTransformLinkMatrix(const std::string& jointName, const Matrix4x4& matrix);

	void addChild(const boost::shared_ptr<Node>& child);

	float getLimit(const float value[], const bool minActive[], const float min[], const bool maxActive[], const float max[], boost::int32_t index) const;

	void setTranslationLimits(bool minActive, float min, bool maxActive, float max, boost::int32_t index);
	void setRotationLimits(bool minActive, float min, bool maxActive, float max, boost::int32_t index);
	void setScalingLimits(bool minActive, float min, bool maxActive, float max, boost::int32_t index);

	void setUsedJoint(const std::string& jointName);

	void updateLocalFinalMatrix();

public:

	Node(const std::string& name, const boost::shared_ptr<Node>& parent, float translate[3], float rotateOffset[3], float rotatePivot[3], float preRotate[3], float rotate[3], float postRotate[3], float scaleOffset[3], float scalePivot[3], float scale[3], float geoTranslate[3], float geoRotate[3], float geoScale[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks, bool joint);
	virtual ~Node();

	const MeshSP& getMesh() const;

	boost::uint32_t getChildCount() const;
	const boost::shared_ptr<Node>& getChild(boost::int32_t i) const;
	const boost::shared_ptr<Node>& getChild(const std::string& name) const;

	boost::shared_ptr<Node> findChildRecursive(const std::string& name) const;

	const boost::shared_ptr<Node>& getParentNode() const;

	boost::int32_t getIndex() const;
	boost::int32_t getIndexRecursive(const std::string& name) const;

	const std::string& getName() const;

	bool isAnimated() const;

	boost::int32_t getSkinningRootIndex() const;

	bool updateRenderingMatrix(Matrix4x4& matrix, const Matrix4x4& parentMatrix, float time, boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;

	void updateBindMatrix(Matrix4x4* allBindMatrices, Matrix3x3* allBindNormalMatrices) const;

	void updateJointMatrix(Matrix4x4* allJointMatrices, Matrix3x3* allJointNormalMatrices, const Matrix4x4& parentMatrix, float time, boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;

	void updateRenderMatrix(const NodeOwner& nodeOwner, InstanceNode& instanceNode, const Matrix4x4& parentMatrix, float time, boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;

	void render(const NodeOwner& nodeOwner, const InstanceNode& instanceNode, float time, boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;

	const Matrix4x4& getGeometricTransform() const;

	const Matrix4x4& getLocalFinalMatrix() const;

	float getStopTime(boost::int32_t animStackIndex, boost::int32_t animLayerIndex) const;

	void updateInstanceNode(const InstanceNodeSP& instanceNode) const;

	bool isTransparent() const;
	void setTransparent(bool transparent);
	void setTransparentRecursive(bool transparent);

	bool isVisible() const;
	void setVisible(bool visible);
	void setVisibleRecursive(bool transparent);
};

typedef boost::shared_ptr<Node> NodeSP;

#endif /* NODE_H_ */

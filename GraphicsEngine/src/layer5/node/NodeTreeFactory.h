/*
 * NodeTreeFactory.h
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#ifndef NODETREEFACTORY_H_
#define NODETREEFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer3/animation/AnimationStack.h"
#include "../../layer3/camera/Camera.h"
#include "../../layer3/light/Light.h"
#include "../../layer3/mesh/Mesh.h"
#include "Node.h"

class NodeTreeFactory
{

private:

	NodeSP rootNode;

	NodeSP findNode(const std::string& name, const NodeSP& node) const;

	bool addChild(const std::shared_ptr<Node>& parentNode, const std::shared_ptr<Node>& child) const;

public:
	NodeTreeFactory();
	virtual ~NodeTreeFactory();

	void reset();

	NodeSP getRootNode() const;

	NodeSP createNode(const std::string& nodeName, const std::string& parentNodeName, const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);

	NodeSP createNode(const std::string& nodeName, const std::string& parentNodeName, const float translate[3], const float rotateOffset[3], const float rotatePivot[3], const float preRotate[3], const float rotate[3], const float postRotate[3], const float scaleOffset[3], const float scalePivot[3], const float scale[3], const float geoTranslate[3], const float geoRotate[3], const float geoScale[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);

	NodeSP createNode(const std::string& nodeName, const std::string& parentNodeName, const float translate[3], const Matrix4x4& postTranslation, const float rotate[3], const Matrix4x4& postRotation, const float scale[3], const Matrix4x4& postScaling, const Matrix4x4& geometricTransform, const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);

	std::int32_t createIndex() const;

	std::int32_t getIndex(const std::string& name) const;

	bool setInverseBindMatrix(const std::string& jointName, const Matrix4x4& inverseBindMatrix) const;

	bool setJoint(const std::string& jointName) const;

};

#endif /* NODETREEFACTORY_H_ */

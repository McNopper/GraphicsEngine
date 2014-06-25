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

	NodeSP createNode(const std::string& nodeName, const std::string& parentNodeName, float translate[3], float rotateOffset[3], float rotatePivot[3], float preRotate[3], float rotate[3], float postRotate[3], float scaleOffset[3], float scalePivot[3], float scale[3], float geoTranslate[3], float geoRotate[3], float geoScale[3], const MeshSP& mesh, const CameraSP& camera, const LightSP& light, const std::vector<AnimationStackSP>& allAnimStacks);

	std::int32_t createIndex() const;

	std::int32_t getIndex(const std::string& name) const;

	bool setBindShapeInverseBindMatrix(const std::string& jointName, const Matrix4x4& transformMatrix, const Matrix4x4& transformLinkMatrix) const;

	bool setJoint(const std::string& jointName) const;

};

#endif /* NODETREEFACTORY_H_ */

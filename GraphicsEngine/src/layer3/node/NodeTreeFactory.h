/*
 * NodeTreeFactory.h
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#ifndef NODETREEFACTORY_H_
#define NODETREEFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer2/animation/AnimationStack.h"
#include "../../layer2/mesh/Mesh.h"
#include "Node.h"

class NodeTreeFactory
{

private:

	NodeSP rootNode;

	NodeSP findNode(const std::string& name, const NodeSP& node) const;

	bool addChild(const boost::shared_ptr<Node>& parentNode, const boost::shared_ptr<Node>& child) const;

public:
	NodeTreeFactory();
	virtual ~NodeTreeFactory();

	void reset();

	NodeSP getRootNode() const;

	NodeSP createNode(const std::string& nodeName, const std::string& parentNodeName, const MeshSP& mesh, const std::vector<AnimationStackSP>& allAnimStacks, bool joint);

	NodeSP createNode(const std::string& nodeName, const std::string& parentNodeName, float translate[3], float rotateOffset[3], float rotatePivot[3], float preRotate[3], float rotate[3], float postRotate[3], float scaleOffset[3], float scalePivot[3], float scale[3], float geoTranslate[3], float geoRotate[3], float geoScale[3], const MeshSP& mesh, const std::vector<AnimationStackSP>& allAnimStacks, bool joint);

	boost::int32_t createIndex() const;

	boost::int32_t getIndex(const std::string& name) const;

	bool setTransformMatrix(const std::string& jointName, const Matrix4x4& matrix) const;
	bool setTransformLinkMatrix(const std::string& jointName, const Matrix4x4& matrix) const;

	bool setTranslationLimits(const std::string& name, bool minActive, float min, bool maxActive, float max, boost::int32_t index) const;
	bool setRotationLimits(const std::string& name, bool minActive, float min, bool maxActive, float max, boost::int32_t index) const;
	bool setScalingLimits(const std::string& name, bool minActive, float min, bool maxActive, float max, boost::int32_t index) const;

	bool setUsedJoint(const std::string& jointName) const;

};

#endif /* NODETREEFACTORY_H_ */

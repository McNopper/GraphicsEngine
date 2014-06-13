/*
 * InstanceNode.h
 *
 *  Created on: 05.09.2012
 *      Author: nopper
 */

#ifndef INSTANCENODE_H_
#define INSTANCENODE_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix3x3.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Quaternion.h"

class Node;

class InstanceNode
{

	friend class Node;

private:

	const Node* node;

	bool visible;
	bool visibleActive;

	bool transparent;
	bool transparentActive;

	Matrix4x4 modelMatrix;

	Matrix3x3 normalModelMatrix;

	Point4 position;

	Quaternion rotation;

	std::vector<std::shared_ptr<InstanceNode> > allChilds;

	std::string name;

	void addChild(const std::shared_ptr<InstanceNode>& instanceNode);

public:

	InstanceNode(const Node* node);
	virtual ~InstanceNode();

	const std::shared_ptr<InstanceNode>& getChild(std::int32_t i) const;

	std::shared_ptr<InstanceNode> findChildRecursive(const std::string& name) const;

	bool isVisible() const;

	bool isVisibleActive() const;

	void setVisible(bool visible, bool visibleActive);
	void setVisibleRecursive(bool visible, bool visibleActive);

	bool isTransparent() const;

	bool isTransparentActive() const;

	void setTransparent(bool transparent, bool transparentActive);
	void setTransparentRecursive(bool transparent, bool transparentActive);

	const Matrix4x4& getModelMatrix() const;
	const Matrix3x3& getNormalModelMatrix() const;

	const Point4& getPosition() const;
	const Quaternion& getRotation() const;

	const Node* getNode() const;

};

typedef std::shared_ptr<InstanceNode> InstanceNodeSP;

#endif /* INSTANCENODE_H_ */

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

class InstanceNode
{

	friend class Node;

private:

	std::string name;

	bool visible;
	bool visibleActive;

	bool transparent;
	bool transparentActive;

	Matrix4x4 modelMatrix;

	Matrix3x3 normalModelMatrix;

	std::vector<boost::shared_ptr<InstanceNode> > allChilds;

	void addChild(const boost::shared_ptr<InstanceNode>& instanceNode);

public:

	InstanceNode(const std::string& name);
	virtual ~InstanceNode();

	const boost::shared_ptr<InstanceNode>& getChild(boost::int32_t i) const;

	boost::shared_ptr<InstanceNode> findChildRecursive(const std::string& name) const;

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
};

typedef boost::shared_ptr<InstanceNode> InstanceNodeSP;

#endif /* INSTANCENODE_H_ */

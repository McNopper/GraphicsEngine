/*
 * GlTfNode.h
 *
 *  Created on: 07.07.2014
 *      Author: nopper
 */

#ifndef GLTFNODE_H_
#define GLTFNODE_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer0/math/Vector3.h"

#include "GlTfInstanceSkin.h"
#include "GlTfMesh.h"

class GlTfNode
{

private:

	std::string name;

	std::vector<std::shared_ptr<GlTfNode>> allChildren;

	GlTfInstanceSkinSP instanceSkin;

	bool joint;

	std::vector<GlTfMeshSP> allMeshes;

	Vector3 translation;
	Vector3 rotation;
	Vector3 scale;

	Matrix4x4 postTranslation;
	Matrix4x4 postRotation;
	Matrix4x4 postScaling;
	Matrix4x4 geometricTransform;

public:

	GlTfNode(const std::string& name);
	virtual ~GlTfNode();

	const std::string& getName() const;

	const std::vector<std::shared_ptr<GlTfNode>>& getAllChildren() const;
	void addChild(const std::shared_ptr<GlTfNode>& child);

	const GlTfInstanceSkinSP& getInstanceSkin() const;
	void setInstanceSkin(const GlTfInstanceSkinSP& instanceSkin);

	bool isJoint() const;
	void setJoint(bool joint);

	const std::vector<GlTfMeshSP>& getAllMeshes() const;
	void addMesh(const GlTfMeshSP& mesh);

	const Vector3& getTranslation() const;
	void setTranslation(const Vector3& translation);
	const Vector3& getRotation() const;
	void setRotation(const Vector3& rotation);
	const Vector3& getScale() const;
	void setScale(const Vector3& scale);

	const Matrix4x4& getPostTranslation() const;
	void setPostTranslation(const Matrix4x4& postTranslation);
	const Matrix4x4& getPostRotation() const;
	void setPostRotation(const Matrix4x4& postRotation);
	const Matrix4x4& getPostScaling() const;
	void setPostScaling(const Matrix4x4& postScaling);
	const Matrix4x4& getGeometricTransform() const;
	void setGeometricTransform(const Matrix4x4& geometricTransform);
};

typedef std::shared_ptr<GlTfNode> GlTfNodeSP;

#endif /* GLTFNODE_H_ */

/*
 * GlTfNode.cpp
 *
 *  Created on: 07.07.2014
 *      Author: nopper
 */

#include "GlTfNode.h"

using namespace std;

GlTfNode::GlTfNode(const string& name) :
	name(name), allChildren(), instanceSkin(), joint(false), allMeshes(), translation(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), postTranslation(), postRotation(), postScaling(), geometricTransform()
{
}

GlTfNode::~GlTfNode()
{
}

const string& GlTfNode::getName() const
{
	return name;
}

const vector<GlTfNodeSP>& GlTfNode::getAllChildren() const
{
	return allChildren;
}

void GlTfNode::addChild(const GlTfNodeSP& child)
{
	allChildren.push_back(child);
}

const GlTfInstanceSkinSP& GlTfNode::getInstanceSkin() const
{
	return instanceSkin;
}

void GlTfNode::setInstanceSkin(const GlTfInstanceSkinSP& instanceSkin)
{
	this->instanceSkin = instanceSkin;
}

bool GlTfNode::isJoint() const
{
	return joint;
}

void GlTfNode::setJoint(bool joint)
{
	this->joint = joint;
}

const vector<GlTfMeshSP>& GlTfNode::getAllMeshes() const
{
	return allMeshes;
}

void GlTfNode::addMesh(const GlTfMeshSP& mesh)
{
	allMeshes.push_back(mesh);
}

const Vector3& GlTfNode::getTranslation() const
{
	return translation;
}

void GlTfNode::setTranslation(const Vector3& translation)
{
	this->translation = translation;
}

const Vector3& GlTfNode::getRotation() const
{
	return rotation;
}

void GlTfNode::setRotation(const Vector3& rotation)
{
	this->rotation = rotation;
}

const Vector3& GlTfNode::getScale() const
{
	return scale;
}

void GlTfNode::setScale(const Vector3& scale)
{
	this->scale = scale;
}

const Matrix4x4& GlTfNode::getPostTranslation() const
{
	return postTranslation;
}

void GlTfNode::setPostTranslation(const Matrix4x4& postTranslation)
{
	this->postTranslation = postTranslation;
}

const Matrix4x4& GlTfNode::getPostRotation() const
{
	return postRotation;
}

void GlTfNode::setPostRotation(const Matrix4x4& postRotation)
{
	this->postRotation = postRotation;
}

const Matrix4x4& GlTfNode::getPostScaling() const
{
	return postScaling;
}

void GlTfNode::setPostScaling(const Matrix4x4& postScaling)
{
	this->postScaling = postScaling;
}

const Matrix4x4& GlTfNode::getGeometricTransform() const
{
	return geometricTransform;
}

void GlTfNode::setGeometricTransform(const Matrix4x4& geometricTransform)
{
	this->geometricTransform = geometricTransform;
}

/*
 * GlTfPrimitive.cpp
 *
 *  Created on: 07.07.2014
 *      Author: nopper
 */

#include "GlTfPrimitive.h"

using namespace std;

GlTfPrimitive::GlTfPrimitive() :
		position(), normal(), bitangent(), tangent(), texcoord(), boneIndices0(), boneIndices1(), boneWeights0(), boneWeights1(), boneCounters(), indices(), surfaceMaterial(), primitive(0)
{
}

GlTfPrimitive::~GlTfPrimitive()
{
}

const GlTfAccessorSP& GlTfPrimitive::getPosition() const
{
	return position;
}

void GlTfPrimitive::setPosition(const GlTfAccessorSP& position)
{
	this->position = position;
}

const GlTfAccessorSP& GlTfPrimitive::getNormal() const
{
	return normal;
}

void GlTfPrimitive::setNormal(const GlTfAccessorSP& normal)
{
	this->normal = normal;
}

const GlTfAccessorSP& GlTfPrimitive::getBitangent() const
{
	return bitangent;
}

void GlTfPrimitive::setBitangent(const GlTfAccessorSP& bitangent)
{
	this->bitangent = bitangent;
}

const GlTfAccessorSP& GlTfPrimitive::getTangent() const
{
	return tangent;
}

void GlTfPrimitive::setTangent(const GlTfAccessorSP& tangent)
{
	this->tangent = tangent;
}

const GlTfAccessorSP& GlTfPrimitive::getTexcoord() const
{
	return texcoord;
}

void GlTfPrimitive::setTexcoord(const GlTfAccessorSP& texcoord)
{
	this->texcoord = texcoord;
}

void GlTfPrimitive::setBoneIndices0(const GlTfAccessorSP& boneIndices0)
{
	this->boneIndices0 = boneIndices0;
}

const GlTfAccessorSP& GlTfPrimitive::getBoneIndices1() const
{
	return boneIndices1;
}

void GlTfPrimitive::setBoneIndices1(const GlTfAccessorSP& boneIndices1)
{
	this->boneIndices1 = boneIndices1;
}

const GlTfAccessorSP& GlTfPrimitive::getBoneWeights0() const
{
	return boneWeights0;
}

void GlTfPrimitive::setBoneWeights0(const GlTfAccessorSP& boneWeights0)
{
	this->boneWeights0 = boneWeights0;
}

const GlTfAccessorSP& GlTfPrimitive::getBoneWeights1() const
{
	return boneWeights1;
}

void GlTfPrimitive::setBoneWeights1(const GlTfAccessorSP& boneWeights1)
{
	this->boneWeights1 = boneWeights1;
}

const GlTfAccessorSP& GlTfPrimitive::getBoneCounters() const
{
	return boneCounters;
}

void GlTfPrimitive::setBoneCounters(const GlTfAccessorSP& boneCounters)
{
	this->boneCounters = boneCounters;
}

const GlTfAccessorSP& GlTfPrimitive::getBoneIndices0() const
{
	return boneIndices0;
}

const GlTfAccessorSP& GlTfPrimitive::getIndices() const
{
	return indices;
}

void GlTfPrimitive::setIndices(const GlTfAccessorSP& indices)
{
	this->indices = indices;
}

const SurfaceMaterialSP& GlTfPrimitive::getSurfaceMaterial() const
{
	return surfaceMaterial;
}

void GlTfPrimitive::setSurfaceMaterial(const SurfaceMaterialSP& surfaceMaterial)
{
	this->surfaceMaterial = surfaceMaterial;
}

GLenum GlTfPrimitive::getPrimitive() const
{
	return primitive;
}

void GlTfPrimitive::setPrimitive(GLenum primitive)
{
	this->primitive = primitive;
}

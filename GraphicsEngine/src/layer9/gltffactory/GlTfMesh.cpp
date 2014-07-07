/*
 * GlTfMesh.cpp
 *
 *  Created on: 07.07.2014
 *      Author: nopper
 */

#include "GlTfMesh.h"

using namespace std;

GlTfMesh::GlTfMesh(const string& name) :
	name(name), allPrimitives()
{
}

GlTfMesh::~GlTfMesh()
{
}

void GlTfMesh::addPrimitive(const GlTfPrimitiveSP& primitive)
{
	allPrimitives.push_back(primitive);
}

const std::vector<GlTfPrimitiveSP>& GlTfMesh::getAllPrimitives() const
{
	return allPrimitives;
}


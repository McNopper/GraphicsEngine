/*
 * GlTfInstanceSkin.cpp
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#include "GlTfInstanceSkin.h"

using namespace std;

GlTfInstanceSkin::GlTfInstanceSkin() :
		allSkeletonNames(), skin(), allSources()
{
}

GlTfInstanceSkin::~GlTfInstanceSkin()
{
}

void GlTfInstanceSkin::addSkeletonName(const string& skeletonName)
{
	allSkeletonNames.push_back(skeletonName);
}

const vector<string>& GlTfInstanceSkin::getAllSkeletonNames() const
{
	return allSkeletonNames;
}

const GlTfSkinSP& GlTfInstanceSkin::getSkin() const
{
	return skin;
}

void GlTfInstanceSkin::setSkin(const GlTfSkinSP& skin)
{
	this->skin = skin;
}


void GlTfInstanceSkin::addSource(const GlTfMeshSP& source)
{
	allSources.push_back(source);
}

const vector<GlTfMeshSP>& GlTfInstanceSkin::getAllSources() const
{
	return allSources;
}


/*
 * GlTfSkin.cpp
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#include "GlTfSkin.h"

using namespace std;

GlTfSkin::GlTfSkin() :
	inverseBindMatrices(), allJointNames()
{
}

GlTfSkin::~GlTfSkin()
{
}

const GlTfAccessorSP& GlTfSkin::getInverseBindMatrices() const
{
	return inverseBindMatrices;
}

void GlTfSkin::setInverseBindMatrices(const GlTfAccessorSP& inverseBindMatrices)
{
	this->inverseBindMatrices = inverseBindMatrices;
}

void GlTfSkin::addJointName(const string& jointName)
{
	allJointNames.push_back(jointName);
}

const vector<string>& GlTfSkin::getAllJointNames() const
{
	return allJointNames;
}

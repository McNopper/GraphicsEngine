/*
 * GlTfChannel.cpp
 *
 *  Created on: 08.07.2014
 *      Author: nopper
 */

#include "GlTfChannel.h"

using namespace std;

GlTfChannel::GlTfChannel() :
		time(), interpolator(), value(), targetNode(), targetPath(), targetElement()
{
}

GlTfChannel::~GlTfChannel()
{
}

const GlTfAccessorSP& GlTfChannel::getTime() const
{
	return time;
}

void GlTfChannel::setTime(const GlTfAccessorSP& time)
{
	this->time = time;
}

const GlTfAccessorSP& GlTfChannel::getInterpolator() const
{
	return interpolator;
}

void GlTfChannel::setInterpolator(const GlTfAccessorSP& interpolator)
{
	this->interpolator = interpolator;
}

const GlTfAccessorSP& GlTfChannel::getValue() const
{
	return value;
}

void GlTfChannel::setValue(const GlTfAccessorSP& value)
{
	this->value = value;
}

const GlTfNodeSP& GlTfChannel::getTargetNode() const
{
	return targetNode;
}

void GlTfChannel::setTargetNode(const GlTfNodeSP& targetNode)
{
	this->targetNode = targetNode;
}

const string& GlTfChannel::getTargetPath() const
{
	return targetPath;
}

void GlTfChannel::setTargetPath(const string& targetPath)
{
	this->targetPath = targetPath;
}

const string& GlTfChannel::getTargetElement() const
{
	return targetElement;
}

void GlTfChannel::setTargetElement(const string& targetElement)
{
	this->targetElement = targetElement;
}

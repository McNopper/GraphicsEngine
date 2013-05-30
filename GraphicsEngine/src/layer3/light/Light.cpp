/*
 * Light.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "Light.h"

using namespace std;

const float Light::getDebugRadius()
{
	return 2.0f;
}

Light::Light(const string& name, const Color& diffuse, const Color& specular) :
		name(name), diffuse(diffuse), specular(specular)
{
}

Light::~Light()
{
}

const string& Light::getName() const
{
	return name;
}

const Color& Light::getDiffuse() const
{
	return diffuse;
}

void Light::setDiffuse(const Color& diffuse)
{
	this->diffuse = diffuse;
}

const Color& Light::getSpecular() const
{
	return specular;
}

void Light::setSpecular(const Color& specular)
{
	this->specular = specular;
}

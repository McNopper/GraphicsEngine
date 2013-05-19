/*
 * Light.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "Light.h"

Light::Light(const Color& ambient, const Color& diffuse, const Color& specular) :
		ambient(ambient), diffuse(diffuse), specular(specular), position(), rotation()
{
}

Light::~Light()
{
}

const Color& Light::getAmbient() const
{
	return ambient;
}

void Light::setAmbient(const Color& ambient)
{
	this->ambient = ambient;
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

const Point4& Light::getPosition() const
{
	return position;
}

void Light::setPosition(const Point4& position)
{
	this->position = position;
}

const Quaternion& Light::getRotation() const
{
	return rotation;
}

void Light::setRotation(const Quaternion& rotation)
{
	this->rotation = rotation;
}

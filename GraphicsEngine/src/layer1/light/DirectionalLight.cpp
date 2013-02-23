/*
 * DirectionalLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vector3& direction, const Color& ambient, const Color& diffuse,
		const Color& specular) :
		Light(ambient, diffuse, specular), direction(direction)
{
	this->direction.normalize();
}

DirectionalLight::~DirectionalLight()
{
}

const Vector3& DirectionalLight::getDirection() const
{
	return direction;
}

void DirectionalLight::setDirection(const Vector3& direction)
{
	this->direction = direction;
	this->direction.normalize();
}

void DirectionalLight::setLightProperties(const ProgramSP& program) const
{
	glUniform1i(program->getUniformLocation(u_lightType), 0);

	glUniform4fv(program->getUniformLocation(u_ambientLightColor), 1, ambient.getRGBA());
	glUniform4fv(program->getUniformLocation(u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(u_specularLightColor), 1, specular.getRGBA());

	glUniform3fv(program->getUniformLocation(u_lightDirection), 1, direction.getV());
}

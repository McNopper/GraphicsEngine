/*
 * SpotLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "SpotLight.h"

SpotLight::SpotLight(const Vector3& spotDirection, float spotCosCutOff, float spotExponent, const Point4& position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& ambient, const Color& diffuse,
		const Color& specular) : PointLight(position, constantAttenuation, linearAttenuation, quadraticAttenuation, ambient, diffuse, specular), spotDirection(spotDirection), spotCosCutOff(spotCosCutOff), spotExponent(spotExponent)
{
}

SpotLight::~SpotLight()
{
}

float SpotLight::getSpotCosCutOff() const
{
	return spotCosCutOff;
}

void SpotLight::setSpotCosCutOff(float spotCosCutOff)
{
	this->spotCosCutOff = spotCosCutOff;
}

const Vector3& SpotLight::getSpotDirection() const
{
	return spotDirection;
}

void SpotLight::setSpotDirection(const Vector3& spotDirection)
{
	this->spotDirection = spotDirection;
}

float SpotLight::getSpotExponent() const
{
	return spotExponent;
}

void SpotLight::setSpotExponent(float spotExponent)
{
	this->spotExponent = spotExponent;
}

void SpotLight::setLightProperties(const ProgramSP& program) const
{
	glUniform1i(program->getUniformLocation(u_lightType), 2);

	glUniform4fv(program->getUniformLocation(u_ambientLightColor), 1, ambient.getRGBA());
	glUniform4fv(program->getUniformLocation(u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(u_specularLightColor), 1, specular.getRGBA());

	glUniform4fv(program->getUniformLocation(u_lightPosition), 1, position.getP());

	glUniform1f(program->getUniformLocation(u_lightConstantAttenuation), constantAttenuation);
	glUniform1f(program->getUniformLocation(u_lightLinearAttenuation), linearAttenuation);
	glUniform1f(program->getUniformLocation(u_lightQuadraticAttenuation), quadraticAttenuation);

	glUniform3fv(program->getUniformLocation(u_lightSpotDirection), 1, spotDirection.getV());
	glUniform1f(program->getUniformLocation(u_lightSpotCosCutOff), spotCosCutOff);
	glUniform1f(program->getUniformLocation(u_lightSpotExponent), spotExponent);
}


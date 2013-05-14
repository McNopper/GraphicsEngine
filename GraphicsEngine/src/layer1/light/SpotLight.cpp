/*
 * SpotLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "SpotLight.h"

using namespace boost;

using namespace std;

SpotLight::SpotLight(const Vector3& spotDirection, float spotCosCutOff, float spotCosCutOffOuter, float spotExponent, const Point4& position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& ambient, const Color& diffuse, const Color& specular) :
		PointLight(position, constantAttenuation, linearAttenuation, quadraticAttenuation, ambient, diffuse, specular), spotDirection(spotDirection), spotCosCutOff(spotCosCutOff), spotCosCutOffOuter(spotCosCutOffOuter), spotExponent(spotExponent)
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

float SpotLight::getSpotCosCutOffOuter() const
{
	return spotCosCutOffOuter;
}

void SpotLight::setSpotCosCutOffOuter(float spotCosCutOffOuter)
{
	this->spotCosCutOffOuter = spotCosCutOffOuter;
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

void SpotLight::setLightProperties(uint32_t lightNumber, const ProgramSP& program) const
{
	glUniform1i(program->getUniformLocation(string(u_lightType) + to_string(lightNumber) + "]"), 2);

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_ambientLightColor), 1, ambient.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_specularLightColor), 1, specular.getRGBA());

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightPosition), 1, position.getP());

	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightConstantAttenuation), constantAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightLinearAttenuation), linearAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightQuadraticAttenuation), quadraticAttenuation);

	glUniform3fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotDirection), 1, spotDirection.getV());
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotCosCutOff), spotCosCutOff);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotCosCutOffOuter), spotCosCutOffOuter);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotExponent), spotExponent);
}

void SpotLight::updateLocation(const Point4& location)
{
	position = location;
}

void SpotLight::updateOrientation(const Quaternion& orientation)
{
	spotDirection = orientation * Vector3(0.0f, 0.0f, -1.0f);
}

void SpotLight::updateLocationOrientation(const Point4& location, const Quaternion& orientation)
{
	position = location;

	spotDirection = orientation * Vector3(0.0f, 0.0f, -1.0f);
}


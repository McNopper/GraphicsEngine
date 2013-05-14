/*
 * PointLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "PointLight.h"

using namespace boost;

using namespace std;

PointLight::PointLight(const Point4& position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& ambient, const Color& diffuse,
		const Color& specular) :
		Light(ambient, diffuse, specular), position(position), constantAttenuation(constantAttenuation), linearAttenuation(linearAttenuation), quadraticAttenuation(quadraticAttenuation)
{
}

PointLight::~PointLight()
{
}

const Point4& PointLight::getPosition() const
{
	return position;
}

void PointLight::setPosition(const Point4& position)
{
	this->position = position;
}

float PointLight::getConstantAttenuation() const
{
	return constantAttenuation;
}

void PointLight::setConstantAttenuation(float constantAttenuation)
{
	this->constantAttenuation = constantAttenuation;
}

float PointLight::getLinearAttenuation() const
{
	return linearAttenuation;
}

void PointLight::setLinearAttenuation(float linearAttenuation)
{
	this->linearAttenuation = linearAttenuation;
}

float PointLight::getQuadraticAttenuation() const
{
	return quadraticAttenuation;
}

void PointLight::setQuadraticAttenuation(float quadraticAttenuation)
{
	this->quadraticAttenuation = quadraticAttenuation;
}

void PointLight::setLightProperties(uint32_t lightNumber, const ProgramSP& program) const
{
	glUniform1i(program->getUniformLocation(string(u_lightType) + to_string(lightNumber) + "]"), 1);

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_ambientLightColor), 1, ambient.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_specularLightColor), 1, specular.getRGBA());

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightPosition), 1, position.getP());

	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightConstantAttenuation), constantAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightLinearAttenuation), linearAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightQuadraticAttenuation), quadraticAttenuation);
}

void PointLight::updateLocation(const Point4& location)
{
	position = location;
}

void PointLight::updateOrientation(const Quaternion& orientation)
{
	// Do nothing
}

void PointLight::updateLocationOrientation(const Point4& location, const Quaternion& orientation)
{
	position = location;
}

/*
 * DirectionalLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "DirectionalLight.h"

using namespace boost;

using namespace std;

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

	Quaternion rotation;

	float alpha = acosf(Vector3(-1.0f, 0.0f, 0.0f).dot(direction));
	float beta = acosf(Vector3(0.0f, 1.0f, 0.0f).dot(direction));

	rotation.rotateRzRyRxf(0.0f, glusRadToDegf(alpha), 90.0f - glusRadToDegf(beta));

	Light::setRotation(rotation);
}

void DirectionalLight::setLightProperties(uint32_t lightNumber, const ProgramSP& program) const
{
	glUniform1i(program->getUniformLocation(string(u_lightType) + to_string(lightNumber) + "]"), 0);

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_ambientLightColor), 1, ambient.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_specularLightColor), 1, specular.getRGBA());

	glUniform3fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightDirection), 1, direction.getV());
}

void DirectionalLight::setRotation(const Quaternion& rotation)
{
	Light::setRotation(rotation);

	this->direction = rotation * Vector3(0.0f, 0.0f, -1.0f);
}

/*
 * DirectionalLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "../../layer2/debug/DebugDraw.h"

#include "DirectionalLight.h"

using namespace boost;

using namespace std;

DirectionalLight::DirectionalLight(const Vector3& direction, const Color& ambient, const Color& diffuse,
		const Color& specular) :
		Light(ambient, diffuse, specular)
{
	setDirection(direction);
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
	this->directionOrignal = direction.normalize();
	this->direction = rotation * this->directionOrignal;
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

	this->direction = rotation * this->directionOrignal;
}

void DirectionalLight::setPositionRotation(const Point4& position, const Quaternion& rotation)
{
	Light::setPositionRotation(position, rotation);

	this->direction = rotation * this->directionOrignal;
}

void DirectionalLight::debugDraw() const
{
	Quaternion localRotation;

	float dotAlpha = Vector3(-1.0f, 0.0f, 0.0f).dot(directionOrignal);
	float dotBeta = Vector3(0.0f, 1.0f, 0.0f).dot(directionOrignal);

	localRotation.rotateRzRyRxf(0.0f, 180.0f - 180.0f * dotAlpha, -180.0f * dotBeta);

	DebugDraw::drawer.drawArrow(getPosition(), Vector3(0.0f, 0.0f, 0.0f), getRotation() * localRotation, 1.0f, 0.1f, 0.5f, 0.3f, Color::YELLOW);
}

/*
 * DirectionalLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "../../layer2/debug/DebugDraw.h"

#include "DirectionalLight.h"

using namespace std;

DirectionalLight::DirectionalLight(const string& name, const Color& diffuse,
		const Color& specular) :
		Light(name, diffuse, specular)
{
	this->direction = Vector3(0.0f, 1.0f, 0.0f);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::setLightProperties(uint32_t lightNumber, const ProgramSP& program, const Point4& position, const Quaternion& rotation) const
{
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightType), 0.0f);

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_specularLightColor), 1, specular.getRGBA());

	glUniform3fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightDirection), 1, (rotation * direction).getV());
}

void DirectionalLight::debugDraw(const Point4& position, const Quaternion& rotation) const
{
	Quaternion baseRotation(180.0f, Vector3(1.0f, 0.0f, 0.0f));

	DebugDraw::drawer.drawArrow(position, Vector3(0.0f, 0.0f, 0.0f), rotation * baseRotation, 1.0f, 0.1f, 0.5f, 0.3f, Color::YELLOW);
}

int32_t DirectionalLight::getShadowType() const
{
	return 0;
}

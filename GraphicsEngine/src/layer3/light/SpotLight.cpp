/*
 * SpotLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "../../layer2/debug/DebugDraw.h"

#include "SpotLight.h"

using namespace std;

SpotLight::SpotLight(const string& name, float spotCosCutOff, float spotCosCutOffOuter, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& diffuse, const Color& specular) :
		PointLight(name, constantAttenuation, linearAttenuation, quadraticAttenuation, diffuse, specular), spotCosCutOff(spotCosCutOff), spotCosCutOffOuter(spotCosCutOffOuter)
{
	this->spotDirection = Vector3(0.0f, -1.0f, 0.0f);
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

void SpotLight::setLightProperties(uint32_t lightNumber, const ProgramSP& program, const Point4& position, const Quaternion& rotation) const
{
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightType), 2.0f);

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_specularLightColor), 1, specular.getRGBA());

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightPosition), 1, position.getP());

	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightConstantAttenuation), constantAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightLinearAttenuation), linearAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightQuadraticAttenuation), quadraticAttenuation);

	glUniform3fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotDirection), 1, (rotation * spotDirection).getV());
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotCosCutOff), spotCosCutOff);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotCosCutOffOuter), spotCosCutOffOuter);
}

void SpotLight::debugDraw(const Point4& position, const Quaternion& rotation) const
{
	float halfExtend = 0.5f;

	DebugDraw::drawer.drawCone(position, Vector3(0.0f, -halfExtend, 0.0f), rotation, halfExtend, 0.4f, Color::YELLOW);
}

int32_t SpotLight::getShadowType() const
{
	return 2;
}


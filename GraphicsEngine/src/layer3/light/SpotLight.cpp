/*
 * SpotLight.cpp
 *
 *  Created on: 24.09.2012
 *      Author: nopper
 */

#include "../../layer2/debug/DebugDraw.h"

#include "SpotLight.h"

using namespace boost;

using namespace std;

SpotLight::SpotLight(const string& name, float spotCosCutOff, float spotCosCutOffOuter, float spotExponent, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, const Color& diffuse, const Color& specular) :
		PointLight(name, constantAttenuation, linearAttenuation, quadraticAttenuation, diffuse, specular), spotCosCutOff(spotCosCutOff), spotCosCutOffOuter(spotCosCutOffOuter), spotExponent(spotExponent)
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

float SpotLight::getSpotExponent() const
{
	return spotExponent;
}

void SpotLight::setSpotExponent(float spotExponent)
{
	this->spotExponent = spotExponent;
}

void SpotLight::setLightProperties(uint32_t lightNumber, const ProgramSP& program, const Point4& position, const Quaternion& rotation) const
{
	glUniform1i(program->getUniformLocation(string(u_lightType) + to_string(lightNumber) + "]"), 2);

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_diffuseLightColor), 1, diffuse.getRGBA());
	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_specularLightColor), 1, specular.getRGBA());

	glUniform4fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightPosition), 1, position.getP());

	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightConstantAttenuation), constantAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightLinearAttenuation), linearAttenuation);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightQuadraticAttenuation), quadraticAttenuation);

	glUniform3fv(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotDirection), 1, (rotation * spotDirection).getV());
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotCosCutOff), spotCosCutOff);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotCosCutOffOuter), spotCosCutOffOuter);
	glUniform1f(program->getUniformLocation(string(u_light) + to_string(lightNumber) + u_lightSpotExponent), spotExponent);
}

void SpotLight::debugDraw(const Point4& position, const Quaternion& rotation) const
{
	float halfExtend = 0.5f;

	DebugDraw::drawer.drawCone(position, Vector3(0.0f, -halfExtend, 0.0f), rotation, halfExtend, 0.4f, Color::YELLOW);
}


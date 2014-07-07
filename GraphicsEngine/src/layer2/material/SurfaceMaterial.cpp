/*
 * SurfaceMaterial.cpp
 *
 *  Created on: 29.05.2011
 *      Author: Norbert Nopper
 */

#include "SurfaceMaterial.h"

using namespace std;

SurfaceMaterial::SurfaceMaterial(const string& name) :
	name(name), reflectionCoefficient(0.0f), reflectionCoefficientTexture(), roughness(0.0f), roughnessTexture(), emissive(Color::DEFAULT_EMISSIVE), emissiveTexture(), diffuse(Color::DEFAULT_DIFFUSE), diffuseTexture(), ambient(Color::DEFAULT_AMBIENT), ambientTexture(), specular(Color::DEFAULT_SPECULAR), specularTexture(), shininess(0.0f), shininessTexture(), reflection(Color::DEFAULT_REFLECTION), reflectionTexture(), refraction(Color::DEFAULT_REFRACTION), refractionTexture(), refractiveIndex(0.0f), refractiveIndexTexture(), transparency(1.0f), normalMapTexture(), displacementMapTexture(), dynamicCubeMapTexture(), convertDirectX(true), programPipeline()
{
}

SurfaceMaterial::~SurfaceMaterial()
{
}

const string& SurfaceMaterial::getName() const
{
	return name;
}

//

float SurfaceMaterial::getReflectionCoefficient() const
{
	return reflectionCoefficient;
}

const Texture2DSP& SurfaceMaterial::getReflectionCoefficientTexture() const
{
	return reflectionCoefficientTexture;
}

GLuint SurfaceMaterial::getReflectionCoefficientTextureName() const
{
	if (reflectionCoefficientTexture.get())
	{
		return reflectionCoefficientTexture->getTextureName();
	}

	return 0;
}

float SurfaceMaterial::getRoughness() const
{
	return roughness;
}

const Texture2DSP& SurfaceMaterial::getRoughnessTexture() const
{
	return roughnessTexture;
}

GLuint SurfaceMaterial::getRoughnessTextureName() const
{
	if (roughnessTexture.get())
	{
		return roughnessTexture->getTextureName();
	}

	return 0;
}

//

const Color& SurfaceMaterial::getEmissive() const
{
	return emissive;
}

const Texture2DSP& SurfaceMaterial::getEmissiveTexture() const
{
	return emissiveTexture;
}

GLuint SurfaceMaterial::getEmissiveTextureName() const
{
	if (emissiveTexture.get())
	{
		return emissiveTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getDiffuse() const
{
	return diffuse;
}

const Texture2DSP& SurfaceMaterial::getDiffuseTexture() const
{
	return diffuseTexture;
}

GLuint SurfaceMaterial::getDiffuseTextureName() const
{
	if (diffuseTexture.get())
	{
		return diffuseTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getAmbient() const
{
	return ambient;
}

const Texture2DSP& SurfaceMaterial::getAmbientTexture() const
{
	return ambientTexture;
}

GLuint SurfaceMaterial::getAmbientTextureName() const
{
	if (ambientTexture.get())
	{
		return ambientTexture->getTextureName();
	}

	return 0;
}
const Color& SurfaceMaterial::getSpecular() const
{
	return specular;
}

const Texture2DSP& SurfaceMaterial::getSpecularTexture() const
{
	return specularTexture;
}

GLuint SurfaceMaterial::getSpecularTextureName() const
{
	if (specularTexture.get())
	{
		return specularTexture->getTextureName();
	}

	return 0;
}

float SurfaceMaterial::getShininess() const
{
	return shininess;
}

const Texture2DSP& SurfaceMaterial::getShininessTexture() const
{
	return shininessTexture;
}

GLuint SurfaceMaterial::getShininessTextureName() const
{
	if (shininessTexture.get())
	{
		return shininessTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getReflection() const
{
	return reflection;
}

const Texture2DSP& SurfaceMaterial::getReflectionTexture() const
{
	return reflectionTexture;
}

GLuint SurfaceMaterial::getReflectionTextureName() const
{
	if (reflectionTexture.get())
	{
		return reflectionTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getRefraction() const
{
	return refraction;
}

const Texture2DSP& SurfaceMaterial::getRefractionTexture() const
{
	return refractionTexture;
}

GLuint SurfaceMaterial::getRefractionTextureName() const
{
	if (refractionTexture.get())
	{
		return refractionTexture->getTextureName();
	}

	return 0;
}

float SurfaceMaterial::getRefractiveIndex() const
{
	return refractiveIndex;
}

const Texture2DSP& SurfaceMaterial::getRefractiveIndexTexture() const
{
	return refractiveIndexTexture;
}

GLuint SurfaceMaterial::getRefractiveIndexTextureName() const
{
	if (refractiveIndexTexture.get())
	{
		return refractiveIndexTexture->getTextureName();
	}

	return 0;
}

float SurfaceMaterial::getTransparency() const
{
	return transparency;
}

const Texture2DSP& SurfaceMaterial::getTransparencyTexture() const
{
	return transparencyTexture;
}

GLuint SurfaceMaterial::getTransparencyTextureName() const
{
	if (transparencyTexture.get())
	{
		return transparencyTexture->getTextureName();
	}

	return 0;
}

const Texture2DSP& SurfaceMaterial::getNormalMapTexture() const
{
	return normalMapTexture;
}

GLuint SurfaceMaterial::getNormalMapTextureName() const
{
	if (normalMapTexture.get())
	{
		return normalMapTexture->getTextureName();
	}

	return 0;
}

const Texture2DSP& SurfaceMaterial::getDisplacementMapTexture() const
{
	return displacementMapTexture;
}

GLuint SurfaceMaterial::getDisplacementMapTextureName() const
{
	if (displacementMapTexture.get())
	{
		return displacementMapTexture->getTextureName();
	}

	return 0;
}

const TextureCubeMapSP& SurfaceMaterial::getDynamicCubeMapTexture() const
{
	return dynamicCubeMapTexture;
}

GLuint SurfaceMaterial::getDynamicCubeMapTextureName() const
{
	if (dynamicCubeMapTexture.get())
	{
		return dynamicCubeMapTexture->getTextureName();
	}

	return 0;
}

//

void SurfaceMaterial::setReflectionCoefficient(float reflectionCoefficient)
{
	this->reflectionCoefficient = reflectionCoefficient;
}

void SurfaceMaterial::setReflectionCoefficientTexture(const Texture2DSP& reflectionCoefficientTexture)
{
	this->reflectionCoefficientTexture = reflectionCoefficientTexture;
}

void SurfaceMaterial::setRoughness(float roughness)
{
	this->roughness = roughness;
}

void SurfaceMaterial::setRoughnessTexture(const Texture2DSP& roughnessTexture)
{
	this->roughnessTexture = roughnessTexture;
}

void SurfaceMaterial::setEmissive(const Color& emissive)
{
	this->emissive = emissive;
}

void SurfaceMaterial::setEmissiveTexture(const Texture2DSP& emissiveTexture)
{
	this->emissiveTexture = emissiveTexture;
}

void SurfaceMaterial::setAmbient(const Color& ambient)
{
	this->ambient = ambient;
}

void SurfaceMaterial::setAmbientTexture(const Texture2DSP& ambientTexture)
{
	this->ambientTexture = ambientTexture;
}

void SurfaceMaterial::setDiffuse(const Color& diffuse)
{
	this->diffuse = diffuse;
}

void SurfaceMaterial::setDiffuseTexture(const Texture2DSP& diffuseTexture)
{
	this->diffuseTexture = diffuseTexture;
}

void SurfaceMaterial::setSpecular(const Color& specular)
{
	this->specular = specular;
}

void SurfaceMaterial::setSpecularTexture(const Texture2DSP& specularTexture)
{
	this->specularTexture = specularTexture;
}

void SurfaceMaterial::setShininess(float shininess)
{
	this->shininess = shininess;
}

void SurfaceMaterial::setShininessTexture(const Texture2DSP& shininessTexture)
{
	this->shininessTexture = shininessTexture;
}

void SurfaceMaterial::setReflection(const Color& reflection)
{
	this->reflection = reflection;
}

void SurfaceMaterial::setReflectionTexture(const Texture2DSP& reflectionTexture)
{
	this->reflectionTexture = reflectionTexture;
}

void SurfaceMaterial::setRefraction(const Color& refraction)
{
	this->refraction = refraction;
}

void SurfaceMaterial::setRefractionTexture(const Texture2DSP& refractionTexture)
{
	this->refractionTexture = refractionTexture;
}

void SurfaceMaterial::setRefractiveIndex(float refractiveIndex)
{
	this->refractiveIndex = refractiveIndex;
}

void SurfaceMaterial::setRefractiveIndexTexture(const Texture2DSP& refractiveIndexTexture)
{
	this->refractiveIndexTexture = refractiveIndexTexture;
}

void SurfaceMaterial::setTransparency(float transparency)
{
	this->transparency = transparency;
}

void SurfaceMaterial::setTransparencyTexture(const Texture2DSP& transparencyTexture)
{
	this->transparencyTexture = transparencyTexture;
}

void SurfaceMaterial::setNormalMapTexture(const Texture2DSP& normalMapTexture)
{
	this->normalMapTexture = normalMapTexture;
}

void SurfaceMaterial::setDisplacementMapTexture(const Texture2DSP& displacementMapTexture)
{
	this->displacementMapTexture = displacementMapTexture;
}

void SurfaceMaterial::setDynamicCubeMapTexture(const TextureCubeMapSP& dynamicCubeMapTexture)
{
	this->dynamicCubeMapTexture = dynamicCubeMapTexture;
}

//

bool SurfaceMaterial::isConvertDirectX() const
{
	return convertDirectX;
}

void SurfaceMaterial::setConvertDirectX(bool convertDirectX)
{
	this->convertDirectX = convertDirectX;
}

const ProgramPipelineSP& SurfaceMaterial::getProgramPipeline() const
{
	return programPipeline;
}

void SurfaceMaterial::setProgramPipeline(const ProgramPipelineSP& programPipeline)
{
	this->programPipeline = programPipeline;
}

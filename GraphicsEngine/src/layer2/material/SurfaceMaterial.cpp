/*
 * SurfaceMaterial.cpp
 *
 *  Created on: 29.05.2011
 *      Author: Norbert Nopper
 */

#include "SurfaceMaterial.h"

using namespace std;

SurfaceMaterial::SurfaceMaterial(const string& name) :
	name(name), emissive(Color::DEFAULT_EMISSIVE), emissiveTexture(), ambient(Color::DEFAULT_AMBIENT), ambientTexture(), diffuse(Color::DEFAULT_DIFFUSE), diffuseTexture(), specular(Color::DEFAULT_SPECULAR), specularTexture(), shininess(0.0f), reflection(Color::DEFAULT_REFLECTION), reflectionTexture(), refraction(Color::DEFAULT_REFRACTION), refractionTexture(), refractiveIndex(0.0f), transparency(1.0f), normalMapTexture(), displacementMapTexture(), dynamicCubeMapTexture(), convertDirectX(true)
{
}

SurfaceMaterial::~SurfaceMaterial()
{
}

const string& SurfaceMaterial::getName() const
{
	return name;
}

const Color& SurfaceMaterial::getAmbient() const
{
	return ambient;
}

GLuint SurfaceMaterial::getAmbientTextureName() const
{
	if (ambientTexture.get())
	{
		return ambientTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getDiffuse() const
{
	return diffuse;
}

GLuint SurfaceMaterial::getDiffuseTextureName() const
{
	if (diffuseTexture.get())
	{
		return diffuseTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getEmissive() const
{
	return emissive;
}

GLuint SurfaceMaterial::getEmissiveTextureName() const
{
	if (emissiveTexture.get())
	{
		return emissiveTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getSpecular() const
{
	return specular;
}

GLuint SurfaceMaterial::getSpecularTextureName() const
{
	if (specularTexture.get())
	{
		return specularTexture->getTextureName();
	}

	return 0;
}

const Color& SurfaceMaterial::getReflection() const
{
	return reflection;
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

GLuint SurfaceMaterial::getRefractionTextureName() const
{
	if (refractionTexture.get())
	{
		return refractionTexture->getTextureName();
	}

	return 0;
}

float SurfaceMaterial::getShininess() const
{
	return shininess;
}

float SurfaceMaterial::getRefractiveIndex() const
{
	return refractiveIndex;
}

float SurfaceMaterial::getTransparency() const
{
	return transparency;
}

GLuint SurfaceMaterial::getNormalMapTextureName() const
{
	if (normalMapTexture.get())
	{
		return normalMapTexture->getTextureName();
	}

	return 0;
}

GLuint SurfaceMaterial::getDisplacementMapTextureName() const
{
	if (displacementMapTexture.get())
	{
		return displacementMapTexture->getTextureName();
	}

	return 0;
}

GLuint SurfaceMaterial::getDynamicCubeMapTextureName() const
{
	if (dynamicCubeMapTexture.get())
	{
		return dynamicCubeMapTexture->getTextureName();
	}

	return 0;
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

void SurfaceMaterial::setEmissive(const Color& emissive)
{
	this->emissive = emissive;
}

void SurfaceMaterial::setEmissiveTexture(const Texture2DSP& emissiveTexture)
{
	this->emissiveTexture = emissiveTexture;
}

void SurfaceMaterial::setSpecular(const Color& specular)
{
	this->specular = specular;
}

void SurfaceMaterial::setSpecularTexture(const Texture2DSP& specularTexture)
{
	this->specularTexture = specularTexture;
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

void SurfaceMaterial::setShininess(float shininess)
{
	this->shininess = shininess;
}

void SurfaceMaterial::setRefractiveIndex(float refractiveIndex)
{
	this->refractiveIndex = refractiveIndex;
}

void SurfaceMaterial::setTransparency(float transparency)
{
	this->transparency = transparency;
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

const Texture2DSP& SurfaceMaterial::getAmbientTexture() const
{
	return ambientTexture;
}

const Texture2DSP& SurfaceMaterial::getDiffuseTexture() const
{
	return diffuseTexture;
}

const Texture2DSP& SurfaceMaterial::getEmissiveTexture() const
{
	return emissiveTexture;
}

const Texture2DSP& SurfaceMaterial::getNormalMapTexture() const
{
	return normalMapTexture;
}

const Texture2DSP& SurfaceMaterial::getDisplacementMapTexture() const
{
	return displacementMapTexture;
}

const Texture2DSP& SurfaceMaterial::getReflectionTexture() const
{
	return reflectionTexture;
}

const Texture2DSP& SurfaceMaterial::getRefractionTexture() const
{
	return refractionTexture;
}

const Texture2DSP& SurfaceMaterial::getSpecularTexture() const
{
	return specularTexture;
}

const TextureCubeMapSP& SurfaceMaterial::getDynamicCubeMapTexture() const
{
	return dynamicCubeMapTexture;
}

bool SurfaceMaterial::isConvertDirectX() const
{
	return convertDirectX;
}

void SurfaceMaterial::setConvertDirectX(bool convertDirectX)
{
	this->convertDirectX = convertDirectX;
}

bool SurfaceMaterial::save(FILE* f) const
{
	// TODO Write surface material data

	// std::string name;

	// Color emissive;
	// Texture2DSP emissiveTexture;

	// Color ambient;
	// Texture2DSP ambientTexture;

	// Color diffuse;
	// Texture2DSP diffuseTexture;

	// Color specular;
	// Texture2DSP specularTexture;

	// float shininess;

	// Color reflection;
	// Texture2DSP reflectionTexture;

	// Color refraction;
	// Texture2DSP refractionTexture;

	// float refractiveIndex;

	// float transparency;
	// Texture2DSP transparencyTexture;

	// Texture2DSP normalMapTexture;

	// Texture2DSP displacementMapTexture;

	// TextureCubeMapSP dynamicCubeMapTexture;

	// bool convertDirectX;

	return true;
}

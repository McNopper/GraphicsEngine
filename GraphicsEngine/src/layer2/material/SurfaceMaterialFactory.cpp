/*
 * SurfaceMaterialFactory.cpp
 *
 *  Created on: 04.09.2012
 *      Author: nopper
 */

#include "SurfaceMaterialFactory.h"

using namespace std;

SurfaceMaterialFactory::SurfaceMaterialFactory()
{
}

SurfaceMaterialFactory::~SurfaceMaterialFactory()
{
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Texture2DSP& diffuseTexture, const Texture2DSP& displacementTexture) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setDiffuse(Color::WHITE);

	surfaceMaterial->setDiffuseTexture(diffuseTexture);
	surfaceMaterial->setDisplacementMapTexture(displacementTexture);

	surfaceMaterial->setConvertDirectX(false);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& diffuse) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setDiffuse(diffuse);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Color& specular, float shininess) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuse(diffuse);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Texture2DSP& diffuseTexture, const Color& specular, float shininess) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuseTexture(diffuseTexture);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Texture2DSP& diffuseTexture, const Color& specular, float shininess) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuse(diffuse);
	surfaceMaterial->setDiffuseTexture(diffuseTexture);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuse(diffuse);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);
	surfaceMaterial->setReflection(reflection);
	surfaceMaterial->setRefraction(refraction);
	surfaceMaterial->setRefractiveIndex(refractiveIndex);
	surfaceMaterial->setTransparency(transparency);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Texture2DSP& diffuseTexture, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuseTexture(diffuseTexture);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);
	surfaceMaterial->setReflection(reflection);
	surfaceMaterial->setRefraction(refraction);
	surfaceMaterial->setRefractiveIndex(refractiveIndex);
	surfaceMaterial->setTransparency(transparency);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Texture2DSP& diffuseTexture, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuse(diffuse);
	surfaceMaterial->setDiffuseTexture(diffuseTexture);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);
	surfaceMaterial->setReflection(reflection);
	surfaceMaterial->setRefraction(refraction);
	surfaceMaterial->setRefractiveIndex(refractiveIndex);
	surfaceMaterial->setTransparency(transparency);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Texture2DSP& diffuseTexture, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency, const TextureCubeMapSP& dynamicCubeMapTexture) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuseTexture(diffuseTexture);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);
	surfaceMaterial->setReflection(reflection);
	surfaceMaterial->setRefraction(refraction);
	surfaceMaterial->setRefractiveIndex(refractiveIndex);
	surfaceMaterial->setTransparency(transparency);
	surfaceMaterial->setDynamicCubeMapTexture(dynamicCubeMapTexture);

	return surfaceMaterial;
}

SurfaceMaterialSP SurfaceMaterialFactory::createSurfaceMaterial(const string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Texture2DSP& diffuseTexture, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency, const TextureCubeMapSP& dynamicCubeMapTexture) const
{
	SurfaceMaterialSP surfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(name));

	surfaceMaterial->setEmissive(emissive);
	surfaceMaterial->setAmbient(ambient);
	surfaceMaterial->setDiffuse(diffuse);
	surfaceMaterial->setDiffuseTexture(diffuseTexture);
	surfaceMaterial->setSpecular(specular);
	surfaceMaterial->setShininess(shininess);
	surfaceMaterial->setReflection(reflection);
	surfaceMaterial->setRefraction(refraction);
	surfaceMaterial->setRefractiveIndex(refractiveIndex);
	surfaceMaterial->setTransparency(transparency);
	surfaceMaterial->setDynamicCubeMapTexture(dynamicCubeMapTexture);

	return surfaceMaterial;
}

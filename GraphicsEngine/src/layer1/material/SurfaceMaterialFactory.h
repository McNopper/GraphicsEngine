/*
 * SurfaceMaterialFactory.h
 *
 *  Created on: 04.09.2012
 *      Author: nopper
 */

#ifndef SURFACEMATERIALFACTORY_H_
#define SURFACEMATERIALFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer0/texture/Texture2D.h"

#include "SurfaceMaterial.h"

class SurfaceMaterialFactory {
public:
	SurfaceMaterialFactory();
	virtual ~SurfaceMaterialFactory();

	SurfaceMaterialSP createSurfaceMaterial(const std::string& name, const Color& diffuse) const;

	SurfaceMaterialSP createSurfaceMaterial(const std::string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Color& specular, float shininess) const;

	SurfaceMaterialSP createSurfaceMaterial(const std::string& name, const Color& emissive, const Color& ambient, const Texture2DSP& diffuseTexture, const Color& specular, float shininess) const;

	SurfaceMaterialSP createSurfaceMaterial(const std::string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Texture2DSP& diffuseTexture, const Color& specular, float shininess) const;

	SurfaceMaterialSP createSurfaceMaterial(const std::string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency) const;

	SurfaceMaterialSP createSurfaceMaterial(const std::string& name, const Color& emissive, const Color& ambient, const Texture2DSP& diffuseTexture, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency) const;

	SurfaceMaterialSP createSurfaceMaterial(const std::string& name, const Color& emissive, const Color& ambient, const Color& diffuse, const Texture2DSP& diffuseTexture, const Color& specular, float shininess, const Color& reflection, const Color& refraction, float refractiveIndex, float transparency) const;

};

#endif /* SURFACEMATERIALFACTORY_H_ */

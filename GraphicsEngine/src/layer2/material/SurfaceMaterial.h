/*
 * SurfaceMaterial.h
 *
 *  Created on: 29.05.2011
 *      Author: Norbert Nopper
 */

#ifndef SURFACEMATERIAL_H_
#define SURFACEMATERIAL_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer1/texture/Texture2D.h"
#include "../../layer1/texture/TextureCubeMap.h"

class SurfaceMaterial
{

private:

	std::string name;

	Color emissive;
	Texture2DSP emissiveTexture;

	Color ambient;
	Texture2DSP ambientTexture;

	Color diffuse;
	Texture2DSP diffuseTexture;

	Color specular;
	Texture2DSP specularTexture;

	float shininess;

	Color reflection;
	Texture2DSP reflectionTexture;

	Color refraction;
	Texture2DSP refractionTexture;

	float refractiveIndex;

	float transparency;
	Texture2DSP transparencyTexture;

	Texture2DSP normalMapTexture;

	Texture2DSP displacementMapTexture;

	TextureCubeMapSP dynamicCubeMapTexture;

	bool convertDirectX;

public:

	SurfaceMaterial(const std::string& name);
	virtual ~SurfaceMaterial();

	const std::string& getName() const;

    const Color& getAmbient() const;
	const Texture2DSP& getAmbientTexture() const;
    GLuint getAmbientTextureName() const;

    const Color& getDiffuse() const;
	const Texture2DSP& getDiffuseTexture() const;
    GLuint getDiffuseTextureName() const;

    const Color& getEmissive() const;
	const Texture2DSP& getEmissiveTexture() const;
    GLuint getEmissiveTextureName() const;

    const Color& getSpecular() const;
	const Texture2DSP& getSpecularTexture() const;
    GLuint getSpecularTextureName() const;

    float getShininess() const;

    const Color& getReflection() const;
	const Texture2DSP& getReflectionTexture() const;
    GLuint getReflectionTextureName() const;

    const Color& getRefraction() const;
	const Texture2DSP& getRefractionTexture() const;
    GLuint getRefractionTextureName() const;

    float getRefractiveIndex() const;

    float getTransparency() const;

	const Texture2DSP& getNormalMapTexture() const;
    GLuint getNormalMapTextureName() const;

	const Texture2DSP& getDisplacementMapTexture() const;
    GLuint getDisplacementMapTextureName() const;

	const TextureCubeMapSP& getDynamicCubeMapTexture() const;
    GLuint getDynamicCubeMapTextureName() const;

    void setAmbient(const Color& ambient);
    void setAmbientTexture(const Texture2DSP& ambientTexture);

    void setDiffuse(const Color& diffuse);
    void setDiffuseTexture(const Texture2DSP& diffuseTexture);

    void setEmissive(const Color& emissive);
    void setEmissiveTexture(const Texture2DSP& emissiveTexture);

    void setSpecular(const Color& specular);
    void setSpecularTexture(const Texture2DSP& specularTexture);

    void setShininess(float shininess);

    void setReflection(const Color& reflection);
    void setReflectionTexture(const Texture2DSP& reflectionTexture);

    void setRefraction(const Color& refraction);
    void setRefractionTexture(const Texture2DSP& refractionTexture);

    void setRefractiveIndex(float refractiveIndex);

    void setTransparency(float transparency);

    void setNormalMapTexture(const Texture2DSP& normalMapTexture);

    void setDisplacementMapTexture(const Texture2DSP& displacementMapTexture);

    void setDynamicCubeMapTexture(const TextureCubeMapSP& dynamicCubeMapTexture);

	bool isConvertDirectX() const;

	void setConvertDirectX(bool convertDirectX);

};

typedef std::shared_ptr<SurfaceMaterial> SurfaceMaterialSP;

#endif /* FBXSURFACEMATERIAL_H_ */

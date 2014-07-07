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
#include "../../layer1/shader/ProgramPipeline.h"
#include "../../layer1/texture/Texture2D.h"
#include "../../layer1/texture/TextureCubeMap.h"

class SurfaceMaterial
{

private:

	std::string name;

	//
	// BRDF
	//

	float reflectionCoefficient;
	Texture2DSP reflectionCoefficientTexture;

	float roughness;
	Texture2DSP roughnessTexture;

	//
	// For all color models.
	//

	Color emissive;
	Texture2DSP emissiveTexture;

	Color diffuse;
	Texture2DSP diffuseTexture;

	//
	// Phong
	//

	Color ambient;
	Texture2DSP ambientTexture;

	Color specular;
	Texture2DSP specularTexture;

	float shininess;
	Texture2DSP shininessTexture;

	Color reflection;
	Texture2DSP reflectionTexture;

	Color refraction;
	Texture2DSP refractionTexture;

	float refractiveIndex;
	Texture2DSP refractiveIndexTexture;

	float transparency;
	Texture2DSP transparencyTexture;

	//

	Texture2DSP normalMapTexture;

	Texture2DSP displacementMapTexture;

	//

	TextureCubeMapSP dynamicCubeMapTexture;

	//

	bool convertDirectX;

	//

	ProgramPipelineSP programPipeline;

public:

	SurfaceMaterial(const std::string& name);
	virtual ~SurfaceMaterial();

	const std::string& getName() const;

	//

	float getReflectionCoefficient() const;
	const Texture2DSP& getReflectionCoefficientTexture() const;
	GLuint getReflectionCoefficientTextureName() const;

	float getRoughness() const;
	const Texture2DSP& getRoughnessTexture() const;
	GLuint getRoughnessTextureName() const;

	//

    const Color& getEmissive() const;
	const Texture2DSP& getEmissiveTexture() const;
    GLuint getEmissiveTextureName() const;

    const Color& getDiffuse() const;
	const Texture2DSP& getDiffuseTexture() const;
    GLuint getDiffuseTextureName() const;

    //

    const Color& getAmbient() const;
	const Texture2DSP& getAmbientTexture() const;
    GLuint getAmbientTextureName() const;

    const Color& getSpecular() const;
	const Texture2DSP& getSpecularTexture() const;
    GLuint getSpecularTextureName() const;

    float getShininess() const;
	const Texture2DSP& getShininessTexture() const;
    GLuint getShininessTextureName() const;

    const Color& getReflection() const;
	const Texture2DSP& getReflectionTexture() const;
    GLuint getReflectionTextureName() const;

    const Color& getRefraction() const;
	const Texture2DSP& getRefractionTexture() const;
    GLuint getRefractionTextureName() const;

    float getRefractiveIndex() const;
	const Texture2DSP& getRefractiveIndexTexture() const;
    GLuint getRefractiveIndexTextureName() const;

    float getTransparency() const;
	const Texture2DSP& getTransparencyTexture() const;
    GLuint getTransparencyTextureName() const;

	const Texture2DSP& getNormalMapTexture() const;
    GLuint getNormalMapTextureName() const;

	const Texture2DSP& getDisplacementMapTexture() const;
    GLuint getDisplacementMapTextureName() const;

	const TextureCubeMapSP& getDynamicCubeMapTexture() const;
    GLuint getDynamicCubeMapTextureName() const;

    //

	void setReflectionCoefficient(float reflectionCoefficient);
	void setReflectionCoefficientTexture( const Texture2DSP& reflectionCoefficientTexture);

	void setRoughness(float roughness);
	void setRoughnessTexture(const Texture2DSP& roughnessTexture);

    void setEmissive(const Color& emissive);
    void setEmissiveTexture(const Texture2DSP& emissiveTexture);

    void setAmbient(const Color& ambient);
    void setAmbientTexture(const Texture2DSP& ambientTexture);

    void setDiffuse(const Color& diffuse);
    void setDiffuseTexture(const Texture2DSP& diffuseTexture);

    void setSpecular(const Color& specular);
    void setSpecularTexture(const Texture2DSP& specularTexture);

    void setShininess(float shininess);
    void setShininessTexture(const Texture2DSP& shininessTexture);

    void setReflection(const Color& reflection);
    void setReflectionTexture(const Texture2DSP& reflectionTexture);

    void setRefraction(const Color& refraction);
    void setRefractionTexture(const Texture2DSP& refractionTexture);

    void setRefractiveIndex(float refractiveIndex);
    void setRefractiveIndexTexture(const Texture2DSP& refractiveIndexTexture);

    void setTransparency(float transparency);
    void setTransparencyTexture(const Texture2DSP& transparencyTexture);

    void setNormalMapTexture(const Texture2DSP& normalMapTexture);

    void setDisplacementMapTexture(const Texture2DSP& displacementMapTexture);

    void setDynamicCubeMapTexture(const TextureCubeMapSP& dynamicCubeMapTexture);

    //

	bool isConvertDirectX() const;

	void setConvertDirectX(bool convertDirectX);

	//

	const ProgramPipelineSP& getProgramPipeline() const;
	void setProgramPipeline(const ProgramPipelineSP& programPipeline);

};

typedef std::shared_ptr<SurfaceMaterial> SurfaceMaterialSP;

#endif /* FBXSURFACEMATERIAL_H_ */

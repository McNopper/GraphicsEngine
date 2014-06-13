/*
 * Sky.h
 *
 *  Created on: 07.11.2012
 *      Author: nopper
 */

#ifndef SKY_H_
#define SKY_H_

#include "../../layer0/primitive/Shape.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer1/texture/TextureCubeMap.h"

#include "SkyVAO.h"

class Sky
{

private:

	GLuint vboVertices;

	GLuint vboIndices;

	std::uint32_t numberIndices;

	ProgramSP program;

	SkyVAOSP skyVAO;

	TextureCubeMapSP skyTexture;

	Matrix4x4 scaleMatrix;

	bool writeBrightColor;
	float brightColorLimit;

public:

	Sky(const Shape& shape, float radiusX, float radiusY, float radiusZ, const std::string& identifier, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ);
	Sky(const Shape& shape, float radiusX, float radiusY, float radiusZ, const std::string& filename);
	virtual ~Sky();

	GLuint getVboVertices() const;

	GLuint getVboIndices() const;

	void render(const Point4& center) const;

	GLuint getSkyTextureName() const;

    bool isWriteBrightColor() const;
    float getBrightColorLimit() const;

    void setWriteBrightColor(bool writeBrightColor);
    void setBrightColorLimit(float brightColorLimit);

};

typedef std::shared_ptr<Sky> SkySP;

#endif /* SKY_H_ */

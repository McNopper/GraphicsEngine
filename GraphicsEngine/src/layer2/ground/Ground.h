/*
 * Ground.h
 *
 *  Created on: 16.05.2013
 *      Author: nopper
 */

#ifndef GROUND_H_
#define GROUND_H_

#include "../../UsedLibs.h"

#include "../../layer0/primitive/GridPlaneShape.h"
#include "../../layer1/collision/BoundingSphere.h"

#include "GroundVAO.h"

class Ground
{

private:

	BoundingSphere boundingSphere;

	std::uint32_t numberVertices;

	std::uint32_t numberIndices;

	GLuint vboVertices;
	GLuint vboNormals;
	GLuint vboBitangents;
	GLuint vboTangents;
	GLuint vboTexCoords;

	GLuint vboIndices;

	std::map<std::string, GroundVAOSP> allVAOs;

	void addVAO(const GroundVAOSP& vao);

public:

	Ground(const BoundingSphere& boundingSphere, const GridPlaneShape& gridPlaneShape);
	virtual ~Ground();

	const BoundingSphere& getBoundingSphere() const;

    std::uint32_t getNumberVertices() const;

    GLuint getVboVertices() const;

    GLuint getVboNormals() const;

    GLuint getVboBitangents() const;

    GLuint getVboTangents() const;

    GLuint getVboTexCoords() const;

    std::uint32_t getNumberIndices() const;

    GLuint getVboIndices() const;

    bool containsVAOByProgramType(const std::string& type) const;

	const GroundVAOSP& getVAOByProgramType(const std::string& type) const;

};

typedef std::shared_ptr<Ground> GroundSP;

#endif /* GROUND_H_ */

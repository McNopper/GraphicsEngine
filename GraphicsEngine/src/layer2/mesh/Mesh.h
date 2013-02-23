/*
 * Mesh.h
 *
 *  Created on: 28.05.2011
 *      Author: Norbert Nopper
 */

#ifndef MESH_H_
#define MESH_H_

#define MAX_SKIN_INDICES 8

#include "../../UsedLibs.h"

#include "../../layer1/material/SurfaceMaterial.h"
#include "SubMesh.h"

class Mesh
{

private:

	boost::uint32_t numberVertices;

	float* vertices;
	float* normals;
	float* bitangents;
	float* tangents;
	float* texCoords;

	boost::uint32_t numberIndices;

	boost::uint32_t* indices;

	GLuint vboVertices;
	GLuint vboNormals;
	GLuint vboBitangents;
	GLuint vboTangents;
	GLuint vboTexCoords;

	GLuint vboIndices;

	float* boneIndices0;
	float* boneIndices1;
	float* boneWeights0;
	float* boneWeights1;
	float* boneCounters;

	GLuint vboBoneIndices[2];
	GLuint vboBoneWeights[2];
	GLuint vboBoneCounters;

	std::map<boost::int32_t, SubMeshSP> subMeshes;

	std::map<boost::int32_t, SurfaceMaterialSP> surfaceMaterials;

	void updateVAO();

public:

	Mesh(boost::uint32_t numberVertices, float* vertices, float* normals, float* bitangents, float* tangents, float* texCoords, boost::uint32_t numberIndices, boost::uint32_t* indices, const std::map<boost::int32_t, SubMeshSP>& subMeshes, const std::map<boost::int32_t, SurfaceMaterialSP>& surfaceMaterials);
	virtual ~Mesh();

	void cleanCpuData();

	boost::uint32_t getNumberVertices() const;
    GLuint getVboVertices() const;
    const float* getVertices() const;

    GLuint getVboNormals() const;
    const float* getNormals() const;

    GLuint getVboBitangents() const;
    const float* getBitangents() const;

    GLuint getVboTangents() const;
    const float* getTangents() const;

    GLuint getVboTexCoords() const;
    const float* getTexCoords() const;

    boost::uint32_t getNumberIndices() const;
    GLuint getVboIndices() const;
    const boost::uint32_t* getIndices() const;

    GLuint getVboBoneIndices(boost::int32_t index) const;
    GLuint getVboBoneWeights(boost::int32_t index) const;
    GLuint getVboBoneCounters() const;

    boost::uint32_t getSubMeshesCount() const;
	bool containsSubMeshAt(boost::int32_t index) const;
	const SubMeshSP& getSubMeshAt(boost::int32_t index) const;

	boost::uint32_t getSurfaceMaterialsCount() const;
	bool containsSurfaceMaterialAt(boost::int32_t index) const;
	const SurfaceMaterialSP& getSurfaceMaterialAt(boost::int32_t index) const;

	SurfaceMaterialSP findSurfaceMaterial(const std::string& name) const;

	void addSkinningData(float* boneIndices0, float* boneIndices1, float* boneWeights0, float* boneWeights1, float* boneCounters);

	bool hasSkinning() const;

	bool hasTexCoords() const;

	bool hasTangents() const;

};

typedef boost::shared_ptr<Mesh> MeshSP;

#endif /* MESH_H_ */

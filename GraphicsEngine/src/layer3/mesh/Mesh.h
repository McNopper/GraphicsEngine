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

#include "../../layer2/material/SurfaceMaterial.h"
#include "SubMesh.h"

class Mesh
{

private:

	std::string name;

	std::uint32_t numberVertices;

	float* vertices;
	float* normals;
	float* bitangents;
	float* tangents;
	float* texCoords;

	std::uint32_t numberIndices;

	std::uint32_t* indices;

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

	std::map<std::int32_t, SubMeshSP> subMeshes;

	std::map<std::int32_t, SurfaceMaterialSP> surfaceMaterials;

	void updateVAO();

public:

	Mesh(const std::string& name, std::uint32_t numberVertices, float* vertices, float* normals, float* bitangents, float* tangents, float* texCoords, std::uint32_t numberIndices, std::uint32_t* indices, const std::map<std::int32_t, SubMeshSP>& subMeshes, const std::map<std::int32_t, SurfaceMaterialSP>& surfaceMaterials);
	virtual ~Mesh();

	void cleanCpuData();

	const std::string& getName() const;

	std::uint32_t getNumberVertices() const;
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

    std::uint32_t getNumberIndices() const;
    GLuint getVboIndices() const;
    const std::uint32_t* getIndices() const;

    GLuint getVboBoneIndices(std::int32_t index) const;
    GLuint getVboBoneWeights(std::int32_t index) const;
    GLuint getVboBoneCounters() const;

    std::uint32_t getSubMeshesCount() const;
	bool containsSubMeshAt(std::int32_t index) const;
	const SubMeshSP& getSubMeshAt(std::int32_t index) const;

	std::uint32_t getSurfaceMaterialsCount() const;
	bool containsSurfaceMaterialAt(std::int32_t index) const;
	const SurfaceMaterialSP& getSurfaceMaterialAt(std::int32_t index) const;

	SurfaceMaterialSP findSurfaceMaterial(const std::string& name) const;

	void addSkinningData(float* boneIndices0, float* boneIndices1, float* boneWeights0, float* boneWeights1, float* boneCounters);

	bool hasSkinning() const;

	bool hasTexCoords() const;

	bool hasTangents() const;

	//

	float* getBoneCounters() const;
	float* getBoneIndices0() const;
	float* getBoneIndices1() const;
	float* getBoneWeights0() const;
	float* getBoneWeights1() const;

};

typedef std::shared_ptr<Mesh> MeshSP;

#endif /* MESH_H_ */

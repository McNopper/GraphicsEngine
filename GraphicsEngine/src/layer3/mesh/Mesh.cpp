/*
 * Mesh.cpp
 *
 *  Created on: 28.05.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/shader/ProgramFactory.h"
#include "SubMeshVAO.h"

#include "Mesh.h"

using namespace std;

Mesh::Mesh(const string& name, uint32_t numberVertices, float* vertices, float* normals, float* bitangents, float* tangents, float* texCoords, uint32_t numberIndices, uint32_t* indices, const map<int32_t, SubMeshSP>& subMeshes, const map<int32_t, SurfaceMaterialSP>& surfaceMaterials) :
	name(name), numberVertices(numberVertices), vertices(vertices), normals(normals), bitangents(bitangents), tangents(tangents), texCoords(texCoords), numberIndices(numberIndices), indices(indices), vboVertices(0),
			vboNormals(0), vboTexCoords(0), vboIndices(0), boneIndices0(0), boneIndices1(0), boneWeights0(0), boneWeights1(0), boneCounters(0), subMeshes(subMeshes), surfaceMaterials(surfaceMaterials)
{
	vboBoneIndices[0] = 0;
	vboBoneIndices[1] = 0;
	vboBoneWeights[0] = 0;
	vboBoneWeights[1] = 0;
	vboBoneCounters = 0;

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 4 * sizeof(GLfloat), (GLfloat*) vertices, GL_STATIC_DRAW);

	if (normals)
	{
		glGenBuffers(1, &vboNormals);
		glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
		glBufferData(GL_ARRAY_BUFFER, numberVertices * 3 * sizeof(GLfloat), (GLfloat*) normals, GL_STATIC_DRAW);
	}

	if (bitangents)
	{
		glGenBuffers(1, &vboBitangents);
		glBindBuffer(GL_ARRAY_BUFFER, vboBitangents);
		glBufferData(GL_ARRAY_BUFFER, numberVertices * 3 * sizeof(GLfloat), (GLfloat*) bitangents, GL_STATIC_DRAW);
	}

	if (tangents)
	{
		glGenBuffers(1, &vboTangents);
		glBindBuffer(GL_ARRAY_BUFFER, vboTangents);
		glBufferData(GL_ARRAY_BUFFER, numberVertices * 3 * sizeof(GLfloat), (GLfloat*) tangents, GL_STATIC_DRAW);
	}

	if (texCoords)
	{
		glGenBuffers(1, &vboTexCoords);
		glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
		glBufferData(GL_ARRAY_BUFFER, numberVertices * 2 * sizeof(GLfloat), (GLfloat*) texCoords, GL_STATIC_DRAW);
	}

	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndices * sizeof(GLuint), (GLuint*) indices, GL_STATIC_DRAW);

	updateVAO();
}

Mesh::~Mesh()
{
	map<int32_t, SubMeshSP>::iterator walkerSubMeshes = subMeshes.begin();
	while (walkerSubMeshes != subMeshes.end())
	{
		walkerSubMeshes->second.reset();
		walkerSubMeshes++;
	}
	subMeshes.clear();

	map<int32_t, SurfaceMaterialSP>::iterator walkerSurfaceMaterials = surfaceMaterials.begin();
	while (walkerSurfaceMaterials != surfaceMaterials.end())
	{
		walkerSurfaceMaterials->second.reset();
		walkerSurfaceMaterials++;
	}
	surfaceMaterials.clear();

	cleanCpuData();

	glDeleteBuffers(1, &vboVertices);
	glDeleteBuffers(1, &vboNormals);
	glDeleteBuffers(1, &vboBitangents);
	glDeleteBuffers(1, &vboTangents);
	glDeleteBuffers(1, &vboTexCoords);

	glDeleteBuffers(2, vboBoneIndices);
	glDeleteBuffers(2, vboBoneWeights);
	glDeleteBuffers(1, &vboBoneCounters);

	glDeleteBuffers(1, &vboIndices);
}


void Mesh::updateVAO()
{
	ProgramFactory programFactory;

	ProgramSP shaderprogram;

	for (uint32_t materialIndex = 0; materialIndex < surfaceMaterials.size(); materialIndex++)
	{
		SurfaceMaterialSP currentSurfaceMaterial = getSurfaceMaterialAt(materialIndex);

		SubMeshSP currentSubMesh = getSubMeshAt(materialIndex);

		shaderprogram = programFactory.createPhongProgram();

		SubMeshVAOSP vao = SubMeshVAOSP(new SubMeshVAO(shaderprogram, *this));
		currentSubMesh->addVAO(vao);

		shaderprogram = programFactory.createPhongRenderToCubeMapProgram();

		vao = SubMeshVAOSP(new SubMeshVAO(shaderprogram, *this));
		currentSubMesh->addVAO(vao);

		shaderprogram = programFactory.createPhongRenderToShadowMapProgram();

		vao = SubMeshVAOSP(new SubMeshVAO(shaderprogram, *this));
		currentSubMesh->addVAO(vao);
	}
}

void Mesh::cleanCpuData()
{
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (bitangents)
	{
		delete[] bitangents;
		bitangents = 0;
	}
	if (tangents)
	{
		delete[] tangents;
		tangents = 0;
	}
	if (texCoords)
	{
		delete[] texCoords;
		texCoords = 0;
	}

	if (indices)
	{
		delete[] indices;
		indices = 0;
	}

	if (boneIndices0)
	{
		delete[] boneIndices0;
		boneIndices0 = 0;
	}

	if (boneIndices1)
	{
		delete[] boneIndices1;
		boneIndices1 = 0;
	}

	if (boneWeights0)
	{
		delete[] boneWeights0;
		boneWeights0 = 0;
	}

	if (boneWeights1)
	{
		delete[] boneWeights1;
		boneWeights1 = 0;
	}

	if (boneCounters)
	{
		delete[] boneCounters;
		boneCounters = 0;
	}
}

const string& Mesh::getName() const
{
	return name;
}

uint32_t Mesh::getNumberVertices() const
{
    return numberVertices;
}

uint32_t Mesh::getNumberIndices() const
{
    return numberIndices;
}

const float* Mesh::getVertices() const
{
	return vertices;
}

const float* Mesh::getNormals() const
{
	return normals;
}

const float* Mesh::getBitangents() const
{
	return bitangents;
}

const float* Mesh::getTangents() const
{
	return tangents;
}

const float* Mesh::getTexCoords() const
{
	return texCoords;
}

const uint32_t* Mesh::getIndices() const
{
	return indices;
}

GLuint Mesh::getVboVertices() const
{
    return vboVertices;
}

GLuint Mesh::getVboNormals() const
{
    return vboNormals;
}

GLuint Mesh::getVboBitangents() const
{
    return vboBitangents;
}

GLuint Mesh::getVboTangents() const
{
    return vboTangents;
}

GLuint Mesh::getVboTexCoords() const
{
    return vboTexCoords;
}

GLuint Mesh::getVboBoneIndices(int32_t index) const
{
	return vboBoneIndices[index];
}

GLuint Mesh::getVboBoneWeights(int32_t index) const
{
	return vboBoneWeights[index];
}

GLuint Mesh::getVboBoneCounters() const
{
	return vboBoneCounters;
}

GLuint Mesh::getVboIndices() const
{
    return vboIndices;
}

uint32_t Mesh::getSubMeshesCount() const
{
	return subMeshes.size();
}

bool Mesh::containsSubMeshAt(int32_t index) const
{
	return subMeshes.find(index) != subMeshes.end();
}

const SubMeshSP& Mesh::getSubMeshAt(int32_t index) const
{
	return subMeshes.at(index);
}

uint32_t Mesh::getSurfaceMaterialsCount() const
{
	return surfaceMaterials.size();
}

bool Mesh::containsSurfaceMaterialAt(int32_t index) const
{
	return surfaceMaterials.find(index) != surfaceMaterials.end();
}

const SurfaceMaterialSP& Mesh::getSurfaceMaterialAt(int32_t index) const
{
	return surfaceMaterials.at(index);
}

SurfaceMaterialSP Mesh::findSurfaceMaterial(const string& name) const
{
	auto walker = surfaceMaterials.begin();

	while (walker != surfaceMaterials.end())
	{
		if (walker->second->getName().compare(name) == 0)
		{
			return walker->second;
		}

		walker++;
	}

	return SurfaceMaterialSP();
}

void Mesh::addSkinningData(float* boneIndices0, float* boneIndices1, float* boneWeights0, float* boneWeights1, float* boneCounters)
{
	this->boneIndices0 = boneIndices0;
	this->boneIndices1 = boneIndices1;
	this->boneWeights0 = boneWeights0;
	this->boneWeights1 = boneWeights1;
	this->boneCounters = boneCounters;

	glGenBuffers(2, vboBoneIndices);
	glBindBuffer(GL_ARRAY_BUFFER, vboBoneIndices[0]);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 4 * sizeof(GLfloat), (GLfloat*)boneIndices0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vboBoneIndices[1]);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 4 * sizeof(GLfloat), (GLfloat*)boneIndices1, GL_STATIC_DRAW);

	glGenBuffers(2, vboBoneWeights);
	glBindBuffer(GL_ARRAY_BUFFER, vboBoneWeights[0]);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 4 * sizeof(GLfloat), (GLfloat*)boneWeights0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vboBoneWeights[1]);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * 4 * sizeof(GLfloat), (GLfloat*)boneWeights1, GL_STATIC_DRAW);

	glGenBuffers(1, &vboBoneCounters);
	glBindBuffer(GL_ARRAY_BUFFER, vboBoneCounters);
	glBufferData(GL_ARRAY_BUFFER, numberVertices * sizeof(GLfloat), (GLfloat*)boneCounters, GL_STATIC_DRAW);

	updateVAO();
}

bool Mesh::hasSkinning() const
{
	return vboBoneIndices[0] != 0 && vboBoneIndices[1] != 0;
}

bool Mesh::hasTexCoords() const
{
	return vboTexCoords != 0;
}

bool Mesh::hasTangents() const
{
	return vboTangents != 0 && vboBitangents != 0;
}

float* Mesh::getBoneCounters() const
{
	return boneCounters;
}

float* Mesh::getBoneIndices0() const
{
	return boneIndices0;
}

float* Mesh::getBoneIndices1() const
{
	return boneIndices1;
}

float* Mesh::getBoneWeights0() const
{
	return boneWeights0;
}

float* Mesh::getBoneWeights1() const
{
	return boneWeights1;
}

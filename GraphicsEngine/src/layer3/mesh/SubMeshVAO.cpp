/*
 * SubMeshVAO.cpp
 *
 *  Created on: 28.05.2011
 *      Author: Norbert Nopper
 */

#include "../../layer1/shader/Variables.h"
#include "Mesh.h"

#include "SubMeshVAO.h"

SubMeshVAO::SubMeshVAO(const ProgramSP& program, const Mesh& mesh) :
	VAO(program)
{
	generateVAO();

	update(mesh);
}

SubMeshVAO::~SubMeshVAO()
{
	deleteVAO();
}

void SubMeshVAO::update(const Mesh& mesh) const
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboVertices());
	glVertexAttribPointer(program->getAttribLocation(a_vertex), 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_vertex));

	glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboNormals());
	glVertexAttribPointer(program->getAttribLocation(a_normal), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(program->getAttribLocation(a_normal));

	if (mesh.hasTangents())
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboBitangents());
		glVertexAttribPointer(program->getAttribLocation(a_bitangent), 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_bitangent));

		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboTangents());
		glVertexAttribPointer(program->getAttribLocation(a_tangent), 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_tangent));
	}

	if (mesh.hasTexCoords())
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboTexCoords());
		glVertexAttribPointer(program->getAttribLocation(a_texCoord), 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_texCoord));
	}

	if (mesh.hasSkinning())
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboBoneIndices(0));
		glVertexAttribPointer(program->getAttribLocation(a_boneIndex_0), 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_boneIndex_0));
		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboBoneIndices(1));
		glVertexAttribPointer(program->getAttribLocation(a_boneIndex_1), 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_boneIndex_1));

		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboBoneWeights(0));
		glVertexAttribPointer(program->getAttribLocation(a_boneWeight_0), 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_boneWeight_0));
		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboBoneWeights(1));
		glVertexAttribPointer(program->getAttribLocation(a_boneWeight_1), 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_boneWeight_1));

		glBindBuffer(GL_ARRAY_BUFFER, mesh.getVboBoneCounters());
		glVertexAttribPointer(program->getAttribLocation(a_boneCounter), 1, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(program->getAttribLocation(a_boneCounter));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getVboIndices());

	glEnableVertexAttribArray(0);

	unbind();
}

/*
 * SubMeshVAO.h
 *
 *  Created on: 28.05.2011
 *      Author: Norbert Nopper
 */

#ifndef SUBMESHVAO_H_
#define SUBMESHVAO_H_

#include "../../layer0/shader/Program.h"
#include "../../layer0/shader/VAO.h"

class Mesh;

class SubMeshVAO : public VAO
{
public:
	SubMeshVAO(const ProgramSP& program, const Mesh& mesh);
	virtual ~SubMeshVAO();

	void update(const Mesh& mesh) const;

};

typedef boost::shared_ptr<SubMeshVAO> SubMeshVAOSP;

#endif /* SUBMESHVAO_H_ */

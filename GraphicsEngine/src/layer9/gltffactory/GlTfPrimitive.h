/*
 * GlTfPrimitive.h
 *
 *  Created on: 07.07.2014
 *      Author: nopper
 */

#ifndef GLTFPRIMITIVE_H_
#define GLTFPRIMITIVE_H_

#include "../../UsedLibs.h"

#include "../../layer2/material/SurfaceMaterial.h"

#include "GlTfAccessor.h"

class GlTfPrimitive
{

private:

	GlTfAccessorSP position;
	GlTfAccessorSP normal;
	GlTfAccessorSP bitangent;
	GlTfAccessorSP tangent;
	GlTfAccessorSP texcoord;

	GlTfAccessorSP boneIndices0;
	GlTfAccessorSP boneIndices1;
	GlTfAccessorSP boneWeights0;
	GlTfAccessorSP boneWeights1;
	GlTfAccessorSP boneCounters;

	GlTfAccessorSP indices;

	SurfaceMaterialSP surfaceMaterial;

	GLenum primitive;

public:

	GlTfPrimitive();
	virtual ~GlTfPrimitive();

	const GlTfAccessorSP& getPosition() const;
	void setPosition(const GlTfAccessorSP& position);
	const GlTfAccessorSP& getNormal() const;
	void setNormal(const GlTfAccessorSP& normal);
	const GlTfAccessorSP& getBitangent() const;
	void setBitangent(const GlTfAccessorSP& bitangent);
	const GlTfAccessorSP& getTangent() const;
	void setTangent(const GlTfAccessorSP& tangent);
	const GlTfAccessorSP& getTexcoord() const;
	void setTexcoord(const GlTfAccessorSP& texcoord);

	const GlTfAccessorSP& getBoneIndices0() const;
	void setBoneIndices0(const GlTfAccessorSP& boneIndices0);
	const GlTfAccessorSP& getBoneIndices1() const;
	void setBoneIndices1(const GlTfAccessorSP& boneIndices1);
	const GlTfAccessorSP& getBoneWeights0() const;
	void setBoneWeights0(const GlTfAccessorSP& boneWeights0);
	const GlTfAccessorSP& getBoneWeights1() const;
	void setBoneWeights1(const GlTfAccessorSP& boneWeights1);
	const GlTfAccessorSP& getBoneCounters() const;
	void setBoneCounters(const GlTfAccessorSP& boneCounters);

	const GlTfAccessorSP& getIndices() const;
	void setIndices(const GlTfAccessorSP& indices);

	const SurfaceMaterialSP& getSurfaceMaterial() const;
	void setSurfaceMaterial(const SurfaceMaterialSP& surfaceMaterial);

	GLenum getPrimitive() const;
	void setPrimitive(GLenum primitive);

};

typedef std::shared_ptr<GlTfPrimitive> GlTfPrimitiveSP;

#endif /* GLTFPRIMITIVE_H_ */

/*
 * Model.h
 *
 *  Created on: 24.05.2011
 *      Author: Norbert Nopper
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Matrix4x4.h"
#include "../../layer0/math/Matrix3x3.h"
#include "../../layer1/collision/BoundingSphere.h"
#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer5/node/Node.h"

class Model
{

private:

	BoundingSphere boundingSphere;

	NodeSP rootNode;
	std::int32_t numberJoints;
	bool animated;
	bool skinned;

	std::map<std::string, NodeSP> allNodesByName;
	std::map<std::string, SurfaceMaterialSP> allSurfaceMaterialsByName;

	void updateSurfaceMaterialsRecursive(const NodeSP& node);

public:

	Model(const BoundingSphere& boundingSphere, const NodeSP& node, std::int32_t numberJoints, bool animationData, bool skinned);
	virtual ~Model();

	const BoundingSphere& getBoundingSphere() const;

	const NodeSP& getRootNode() const;

	std::int32_t getNumberJoints() const;

	bool isAnimated() const;

	bool isSkinned() const;

	SurfaceMaterialSP findSurfaceMaterial(const std::string& name) const;

	std::int32_t getNodeCount() const;

	NodeSP getNodeAt(std::int32_t index) const;

	std::int32_t getSurfaceMaterialCount() const;

	SurfaceMaterialSP getSurfaceMaterialAt(std::int32_t index) const;

};

typedef std::shared_ptr<Model> ModelSP;

#endif /* MODEL_H_ */

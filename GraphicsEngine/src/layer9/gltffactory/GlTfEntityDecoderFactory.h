/*
 * GlTfEntityDecoderFactory.h
 *
 *  Created on: 02.07.2014
 *      Author: nopper
 */

#ifndef GLTFENTITYDECODERFACTORY_H_
#define GLTFENTITYDECODERFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/color/Color.h"
#include "../../layer0/json/JSONarray.h"
#include "../../layer0/json/JSONobject.h"
#include "../../layer0/json/JSONnumber.h"
#include "../../layer0/json/JSONstring.h"
#include "../../layer0/json/JSONvalue.h"
#include "../../layer0/math/Matrix3x3.h"
#include "../../layer0/math/Matrix4x4.h"
#include "../../layer5/node/NodeTreeFactory.h"
#include "../../layer2/material/SurfaceMaterial.h"
#include "../../layer8/modelentity/ModelEntity.h"

#include "GlTfAccessor.h"
#include "GlTfAnimation.h"
#include "GlTfBufferView.h"
#include "GlTfMesh.h"
#include "GlTfNode.h"
#include "GlTfSampler.h"
#include "GlTfSkin.h"

class GlTfEntityDecoderFactory
{

private:

	bool doReset;

	float minX, maxX, minY, maxY, minZ, maxZ;

	NodeTreeFactory nodeTreeFactory;

	bool animated;

	bool skinned;

	std::map<std::string, GLUSbinaryfile> allBuffers;
	std::map<std::string, GlTfBufferViewSP> allBufferViews;
	std::map<std::string, GlTfAccessorSP> allAccessors;

	std::map<std::string, GLUStgaimage> allTgaImages;
	std::map<std::string, GLUShdrimage> allHdrImages;
	std::map<std::string, GlTfSamplerSP> allSamplers;
	std::map<std::string, Texture2DSP> allTextures2D;

	std::map<std::string, SurfaceMaterialSP> allSurfaceMaterials;

	std::map<std::string, GlTfMeshSP> allMeshes;

	std::map<std::string, GlTfSkinSP> allSkins;

	std::map<std::string, GlTfNodeSP> allNodes;

	std::map<std::string, GlTfAnimationSP> allAnimations;

	bool decodeBuffers(const JSONobjectSP& jsonGlTf, const std::string& folderName);
	bool decodeBufferViews(const JSONobjectSP& jsonGlTf);
	bool decodeAccessors(const JSONobjectSP& jsonGlTf);

	bool decodeImages(const JSONobjectSP& jsonGlTf, const std::string& folderName);
	bool decodeSamplers(const JSONobjectSP& jsonGlTf);
	bool decodeTextures(const JSONobjectSP& jsonGlTf);

	bool decodeMaterials(const JSONobjectSP& jsonGlTf);

	bool decodeMeshes(const JSONobjectSP& jsonGlTf);

	bool decodeSkins(const JSONobjectSP& jsonGlTf);

	GlTfNodeSP decodeNode(const std::string& name, const JSONobjectSP& nodesObject);
	bool decodeNodes(const JSONobjectSP& jsonGlTf);

	bool decodeAnimations(const JSONobjectSP& jsonGlTf);

	//

	bool decodeFloat(float& number, const JSONvalueSP& jsonValue) const;

	bool decodeInteger(int32_t& number, const JSONvalueSP& jsonValue) const;

	bool decodeString(std::string& value, const JSONvalueSP& jsonValue) const;

	bool decodeMatrix4x4(Matrix4x4& matrix, const JSONvalueSP& jsonValue) const;

	bool decodeMatrix3x3(Matrix3x3& matrix, const JSONvalueSP& jsonValue) const;

	bool decodeVector3(Vector3& vector, const JSONvalueSP& jsonValue) const;

	bool decodeColor(Color& color, const JSONvalueSP& jsonValue) const;

	bool decodeTexture2D(Texture2DSP& texture, const JSONvalueSP& jsonValue) const;

	bool decodeAccessor(GlTfAccessorSP& accessor, const JSONvalueSP& jsonValue) const;

	//

	void processMinMax(const float* vertices, std::int32_t numberVertices, const Matrix4x4& matrix);

	NodeSP buildNode(const NodeSP& parentNode, const GlTfNodeSP& node, const Matrix4x4& parentMatrix);

	//

	void cleanUp();

public:

	GlTfEntityDecoderFactory();

	virtual ~GlTfEntityDecoderFactory();

	ModelEntitySP loadGlTfModelFile(const std::string& identifier, const std::string& fileName, const std::string& folderName, float scale);

};

#endif /* GLTFENTITYDECODERFACTORY_H_ */

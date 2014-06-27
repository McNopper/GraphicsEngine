/*
 * GlTfEntityFactory.h
 *
 *  Created on: 18.06.2014
 *      Author: nopper
 */

#ifndef GLTFENTITYFACTORY_H_
#define GLTFENTITYFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/json/JSONobject.h"
#include "../../layer0/json/JSONstring.h"
#include "../../layer1/shader/ProgramPipeline.h"
#include "../../layer1/shader/ProgramSeparable.h"
#include "../../layer8/modelentity/ModelEntity.h"

#include "GlTfBin.h"

class GlTfEntityFactory
{

private:

	JSONstringSP getElement(const AnimationLayer::eCHANNELS_XYZ channel) const;


	void addChannel(JSONobjectSP& channelObject, const JSONstringSP& samplerValueString, const JSONstringSP& idString, const JSONstringSP& pathString, const JSONstringSP& elementString) const;

	void addAnimationAccessors(JSONobjectSP& animationsObject, JSONobjectSP& accessorsObject, const ModelSP& model) const;

	void addAsset(JSONobjectSP& assetObject) const;


	void addImage(JSONobjectSP& imagesObject, const JSONstringSP& imageString, const Texture2DSP& texture) const;

	void addSampler(JSONobjectSP& samplersObject, const JSONstringSP& samplerString, const Texture2DSP& texture) const;

	void addTexture(JSONobjectSP& texturesObject, const JSONstringSP& textureString, const Texture2DSP& texture) const;

	void addTextureSamplerImage(JSONobjectSP& texturesObject, const JSONstringSP& textureString, JSONobjectSP& samplersObject, const JSONstringSP& samplerString, JSONobjectSP& imagesObject, const JSONstringSP& imageString, const Texture2DSP& texture) const;


	void addShader(JSONobjectSP& shadersObject, const JSONstringSP& shaderString, const ProgramSeparableSP programSeparable) const;

	void addProgramShader(JSONobjectSP& programsObject, JSONobjectSP& shadersObject, const JSONstringSP& programString, const ProgramPipelineSP programPipeline) const;

	void addTechniqueProgramShader(JSONobjectSP& techniquesObject, JSONobjectSP& programsObject, JSONobjectSP& shadersObject, const JSONstringSP& techniqueString, const ProgramPipelineSP programPipeline) const;


	void addMaterialTechniqueProgramShaderTextureSamplerImage(JSONobjectSP& materialsObject, JSONobjectSP& techniquesObject, JSONobjectSP& programsObject, JSONobjectSP& shadersObject, JSONobjectSP& texturesObject, JSONobjectSP& samplersObject, JSONobjectSP& imagesObject,const ModelSP& model) const;


	void addFBXValues(JSONobjectSP& nodeObject, const NodeSP& node) const;


	void addAccessorsValues(JSONobjectSP& accessorObject, const JSONstringSP& bufferViewValueString, size_t byteOffset, size_t byteStride, GLenum componentType, int32_t count, const std::string& type) const;

	void addBufferViewsValues(JSONobjectSP& bufferViewObject, const JSONstringSP& bufferValueString, size_t byteOffset, size_t byteLength, GLenum target) const;

	void addBufferBufferViewsAccessors(JSONobjectSP& buffersObject, const JSONstringSP& bufferString, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, const MeshSP& mesh) const;


	void addMesh(JSONobjectSP& meshesObject, const JSONstringSP& meshString, const MeshSP& mesh, std::int32_t index) const;


	void addNodeBufferBufferViewsAccessorsMeshes(JSONobjectSP& nodesObject, JSONobjectSP& buffersObject, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, JSONobjectSP& meshesObject, const ModelSP& model) const;


	void addScene(JSONobjectSP& scenesObject, const JSONstringSP& sceneString, const NodeSP& rootNode) const;

public:

	GlTfEntityFactory();
	virtual ~GlTfEntityFactory();

	bool saveGlTfModelFile(const ModelEntitySP& modelEntity, const std::string& identifier);

};

#endif /* GLTFENTITYFACTORY_H_ */

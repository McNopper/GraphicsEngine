/*
 * GlTfEntityEncoderFactory.h
 *
 *  Created on: 18.06.2014
 *      Author: nopper
 */

#ifndef GLTFENTITYENCODERFACTORY_H_
#define GLTFENTITYENCODERFACTORY_H_

#include "../../UsedLibs.h"

#include "../../layer0/json/JSONarray.h"
#include "../../layer0/json/JSONobject.h"
#include "../../layer0/json/JSONstring.h"
#include "../../layer1/shader/ProgramPipeline.h"
#include "../../layer1/shader/ProgramSeparable.h"
#include "../../layer2/interpolation/Interpolator.h"
#include "../../layer8/modelentity/ModelEntity.h"

#include "GlTfBin.h"

class GlTfEntityEncoderFactory
{

private:

	std::string channelToString(const AnimationLayer::eCHANNELS_XYZ channel) const;

	const NodeSP getParentRootJointNode(const NodeSP& node) const;


	void addChannelValues(JSONobjectSP& channelObject, const JSONstringSP& samplerValueString, const JSONstringSP& idString, const JSONstringSP& pathString, const JSONstringSP& elementString) const;

	void addChannelParameterSampler(GlTfBin& bin, JSONarraySP& channelsArray, JSONobjectSP& parametersObject, JSONobjectSP& samplersObject, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, const JSONstringSP& bufferString, const JSONstringSP& nodeValueString, const std::string& identifier, const std::string& transform, const std::string& channel, const std::map<float, float>& timeValues, const std::map<float, const Interpolator*>& timeInterpolators) const;

	void addAnimationBufferBufferViewAccessor(JSONobjectSP& animationsObject, JSONobjectSP& buffersObject, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, const ModelSP& model, const std::string& folderName) const;


	void addAsset(JSONobjectSP& assetObject) const;


	void addImage(JSONobjectSP& imagesObject, const JSONstringSP& imageString, const Texture2DSP& texture, const std::string& folderName) const;

	void addSampler(JSONobjectSP& samplersObject, const JSONstringSP& samplerString, const Texture2DSP& texture) const;

	void addTexture(JSONobjectSP& texturesObject, const JSONstringSP& textureString, const Texture2DSP& texture) const;

	void addTextureSamplerImage(JSONobjectSP& texturesObject, const JSONstringSP& textureString, JSONobjectSP& samplersObject, const JSONstringSP& samplerString, JSONobjectSP& imagesObject, const JSONstringSP& imageString, const Texture2DSP& texture, const std::string& folderName) const;


	void addShader(JSONobjectSP& shadersObject, const JSONstringSP& shaderString, const ProgramSeparableSP programSeparable) const;

	void addProgramShader(JSONobjectSP& programsObject, JSONobjectSP& shadersObject, const JSONstringSP& programString, const ProgramPipelineSP programPipeline) const;

	void addTechniqueProgramShader(JSONobjectSP& techniquesObject, JSONobjectSP& programsObject, JSONobjectSP& shadersObject, const JSONstringSP& techniqueString, const ProgramPipelineSP programPipeline) const;


	void addMaterialTechniqueProgramShaderTextureSamplerImage(JSONobjectSP& materialsObject, JSONobjectSP& techniquesObject, JSONobjectSP& programsObject, JSONobjectSP& shadersObject, JSONobjectSP& texturesObject, JSONobjectSP& samplersObject, JSONobjectSP& imagesObject, const ModelSP& model, const std::string& folderName) const;


	void addFBXValues(JSONobjectSP& nodeObject, const NodeSP& node) const;


	void addAccessorValues(JSONobjectSP& accessorObject, const JSONstringSP& bufferViewValueString, size_t byteOffset, size_t byteStride, GLenum componentType, int32_t count, const std::string& type) const;

	void addBufferViewValues(JSONobjectSP& bufferViewObject, const JSONstringSP& bufferValueString, size_t byteOffset, size_t byteLength, GLenum target) const;

	void addBufferViewValues(JSONobjectSP& bufferViewObject, const JSONstringSP& bufferValueString, size_t byteOffset, size_t byteLength) const;

	void addBufferBufferViewAccessor(JSONobjectSP& buffersObject, const JSONstringSP& bufferString, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, const MeshSP& mesh, const std::string& folderName) const;


	void addMesh(JSONobjectSP& meshesObject, const JSONstringSP& meshString, const MeshSP& mesh) const;


	void addNodeBufferBufferViewAccessorMesh(JSONobjectSP& nodesObject, JSONobjectSP& buffersObject, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, JSONobjectSP& meshesObject, const ModelSP& model, const std::string& folderName) const;


	void addScene(JSONobjectSP& scenesObject, const JSONstringSP& sceneString, const NodeSP& rootNode) const;


	void addSkin(JSONobjectSP& skinsObject, JSONobjectSP& buffersObject, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, const ModelEntitySP& modelEntity, const std::string& folderName) const;

public:

	GlTfEntityEncoderFactory();
	virtual ~GlTfEntityEncoderFactory();

	bool saveGlTfModelFile(const ModelEntitySP& modelEntity, const std::string& identifier);

};

#endif /* GLTFENTITYENCODERFACTORY_H_ */

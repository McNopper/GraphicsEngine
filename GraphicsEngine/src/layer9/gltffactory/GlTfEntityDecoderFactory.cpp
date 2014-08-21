/*
 * GlTfEntityDecoderFactory.cpp
 *
 *  Created on: 02.07.2014
 *      Author: nopper
 */

#include "../../layer0/json/JSONdecoder.h"
#include "../../layer2/interpolation/ConstantInterpolator.h"
#include "../../layer2/interpolation/CubicInterpolator.h"
#include "../../layer2/interpolation/LinearInterpolator.h"
#include "../../layer1/texture/Texture2DManager.h"
#include "../../layer3/mesh/Mesh.h"

#include "GlTfEntityDecoderFactory.h"

using namespace std;

GlTfEntityDecoderFactory::GlTfEntityDecoderFactory() :
		doReset(true), minX(0.0f), maxX(0.0f), minY(0.0f), maxY(0.0f), minZ(0.0f), maxZ(0.0f), nodeTreeFactory(), animated(false), skinned(false)
{
}

GlTfEntityDecoderFactory::~GlTfEntityDecoderFactory()
{
}

bool GlTfEntityDecoderFactory::decodeBuffers(const JSONobjectSP& jsonGlTf, const string& folderName)
{
	JSONstringSP buffersString = JSONstringSP(new JSONstring("buffers"));

	if (!jsonGlTf->hasKey(buffersString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(buffersString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP buffersObject = dynamic_pointer_cast<JSONobject>(value);

	JSONstringSP uriString = JSONstringSP(new JSONstring("uri"));
	JSONstringSP byteLengthString = JSONstringSP(new JSONstring("byteLength"));

	GLUSbinaryfile binaryfile;

	for (auto& currentKey : buffersObject->getAllKeys())
	{
		JSONvalueSP currentValue = buffersObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentBuffer = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentBuffer->getValue(uriString);
		if (!currentValue->isJsonString())
		{
			return false;
		}

		JSONstringSP currentUri = dynamic_pointer_cast<JSONstring>(currentValue);

		//

		glusLogPrint(GLUS_LOG_INFO, "Loading buffer '%s'", (folderName + currentUri->getValue()).c_str());

		if (!glusFileLoadBinary((GLUSchar*)(folderName + currentUri->getValue()).c_str(), &binaryfile))
		{
			return false;
		}

		allBuffers[currentKey->getValue()] = binaryfile;

		//

		currentValue = currentBuffer->getValue(byteLengthString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentByteLength = dynamic_pointer_cast<JSONnumber>(currentValue);

		if (currentByteLength->getIntegerValue() != (int32_t)binaryfile.length)
		{
			return false;
		}
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeBufferViews(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP bufferViewsString = JSONstringSP(new JSONstring("bufferViews"));

	if (!jsonGlTf->hasKey(bufferViewsString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(bufferViewsString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP bufferViewsObject = dynamic_pointer_cast<JSONobject>(value);

	JSONstringSP bufferString = JSONstringSP(new JSONstring("buffer"));
	JSONstringSP byteOffestString = JSONstringSP(new JSONstring("byteOffset"));
	JSONstringSP byteLengthString = JSONstringSP(new JSONstring("byteLength"));
	JSONstringSP targetString = JSONstringSP(new JSONstring("target"));

	for (auto& currentKey : bufferViewsObject->getAllKeys())
	{
		JSONvalueSP currentValue = bufferViewsObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentBufferView = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentBufferView->getValue(bufferString);
		if (!currentValue->isJsonString())
		{
			return false;
		}

		JSONstringSP currentBufferString = dynamic_pointer_cast<JSONstring>(currentValue);

		//

		auto currentBuffer = allBuffers.find(currentBufferString->getValue());

		if (currentBuffer == allBuffers.end())
		{
			return false;
		}

		//

		currentValue = currentBufferView->getValue(byteOffestString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentByteOffset = dynamic_pointer_cast<JSONnumber>(currentValue);

		if (currentByteOffset->getIntegerValue() >= currentBuffer->second.length)
		{
			return false;
		}

		//

		currentValue = currentBufferView->getValue(byteLengthString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentByteLength = dynamic_pointer_cast<JSONnumber>(currentValue);

		if (currentByteOffset->getIntegerValue() + currentByteLength->getIntegerValue() > currentBuffer->second.length)
		{
			return false;
		}

		//

		GLenum target = 0;

		if (currentBufferView->hasKey(targetString))
		{
			currentValue = currentBufferView->getValue(targetString);
			if (!currentValue->isJsonNumber())
			{
				return false;
			}

			JSONnumberSP currentTarget = dynamic_pointer_cast<JSONnumber>(currentValue);

			target = (GLenum)currentTarget->getIntegerValue();
		}

		//

		GlTfBufferViewSP currentGlTfBufferView = GlTfBufferViewSP(new GlTfBufferView((const uint8_t*)currentBuffer->second.binary, currentByteOffset->getIntegerValue(), currentByteLength->getIntegerValue(), target));

		allBufferViews[currentKey->getValue()] = currentGlTfBufferView;
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeAccessors(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP accessorsString = JSONstringSP(new JSONstring("accessors"));

	if (!jsonGlTf->hasKey(accessorsString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(accessorsString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP accessorsObject = dynamic_pointer_cast<JSONobject>(value);

	JSONstringSP bufferViewString = JSONstringSP(new JSONstring("bufferView"));
	JSONstringSP byteOffestString = JSONstringSP(new JSONstring("byteOffset"));
	JSONstringSP byteStrideString = JSONstringSP(new JSONstring("byteStride"));
	JSONstringSP componentTypeString = JSONstringSP(new JSONstring("componentType"));
	JSONstringSP countString = JSONstringSP(new JSONstring("count"));
	JSONstringSP typeString = JSONstringSP(new JSONstring("type"));

	for (auto& currentKey : accessorsObject->getAllKeys())
	{
		JSONvalueSP currentValue = accessorsObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentAccessor = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentAccessor->getValue(bufferViewString);
		if (!currentValue->isJsonString())
		{
			return false;
		}

		JSONstringSP bufferViewString = dynamic_pointer_cast<JSONstring>(currentValue);

		//

		auto currentBufferView = allBufferViews.find(bufferViewString->getValue());

		if (currentBufferView == allBufferViews.end())
		{
			return false;
		}

		//

		currentValue = currentAccessor->getValue(byteOffestString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentByteOffset = dynamic_pointer_cast<JSONnumber>(currentValue);

		if (currentByteOffset->getIntegerValue() >= currentBufferView->second->getByteLength())
		{
			return false;
		}

		//

		currentValue = currentAccessor->getValue(byteStrideString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentByteStride = dynamic_pointer_cast<JSONnumber>(currentValue);

		//

		currentValue = currentAccessor->getValue(componentTypeString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentComponentType = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum componentType = (GLenum)currentComponentType->getIntegerValue();

		//

		currentValue = currentAccessor->getValue(countString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentCount = dynamic_pointer_cast<JSONnumber>(currentValue);

		//

		currentValue = currentAccessor->getValue(typeString);
		if (!currentValue->isJsonString())
		{
			return false;
		}

		JSONstringSP currentType = dynamic_pointer_cast<JSONstring>(currentValue);

		//

		GlTfAccessorSP currentGlTfAccessor = GlTfAccessorSP(new GlTfAccessor(currentBufferView->second, currentByteOffset->getIntegerValue(), currentByteStride->getIntegerValue(), componentType, currentCount->getIntegerValue(), currentType->getValue()));

		allAccessors[currentKey->getValue()] = currentGlTfAccessor;
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeImages(const JSONobjectSP& jsonGlTf, const string& folderName)
{
	JSONstringSP imagesString = JSONstringSP(new JSONstring("images"));

	if (!jsonGlTf->hasKey(imagesString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(imagesString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP imagesObject = dynamic_pointer_cast<JSONobject>(value);

	JSONstringSP uriString = JSONstringSP(new JSONstring("uri"));

	GLUStgaimage tgaimage;
	GLUShdrimage hdrimage;

	string extension;

	for (auto& currentKey : imagesObject->getAllKeys())
	{
		JSONvalueSP currentValue = imagesObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentImage = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentImage->getValue(uriString);
		if (!currentValue->isJsonString())
		{
			return false;
		}

		JSONstringSP currentUri = dynamic_pointer_cast<JSONstring>(currentValue);

		//

		if (currentUri->getValue().length() < 5)
		{
			return false;
		}

		extension = currentUri->getValue().substr(currentUri->getValue().length() - 3, 3);

		transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

		if (extension == "tga")
		{
			glusLogPrint(GLUS_LOG_INFO, "Loading image '%s'", (folderName + currentUri->getValue()).c_str());

			if (!glusImageLoadTga((GLUSchar*)(folderName + currentUri->getValue()).c_str(), &tgaimage))
			{
				return false;
			}

			allTgaImages[currentKey->getValue()] = tgaimage;
		}
		else if (extension == "hdr")
		{
			glusLogPrint(GLUS_LOG_INFO, "Loading image '%s'", (folderName + currentUri->getValue()).c_str());

			if (!glusImageLoadHdr((GLUSchar*)(folderName + currentUri->getValue()).c_str(), &hdrimage))
			{
				return false;
			}

			allHdrImages[currentKey->getValue()] = hdrimage;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeSamplers(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP samplersString = JSONstringSP(new JSONstring("samplers"));

	if (!jsonGlTf->hasKey(samplersString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(samplersString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP samplersObject = dynamic_pointer_cast<JSONobject>(value);

	JSONstringSP magFilterString = JSONstringSP(new JSONstring("magFilter"));
	JSONstringSP minFilterString = JSONstringSP(new JSONstring("minFilter"));
	JSONstringSP wrapSString = JSONstringSP(new JSONstring("wrapS"));
	JSONstringSP wrapTString = JSONstringSP(new JSONstring("wrapT"));

	for (auto& currentKey : samplersObject->getAllKeys())
	{
		JSONvalueSP currentValue = samplersObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentSampler = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentSampler->getValue(magFilterString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentMagFilter = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum magFilter = (GLenum)currentMagFilter->getIntegerValue();

		//

		currentValue = currentSampler->getValue(minFilterString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentMinFilter = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum minFilter = (GLenum)currentMinFilter->getIntegerValue();

		//

		currentValue = currentSampler->getValue(wrapSString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentWrapS = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum wrapS = (GLenum)currentWrapS->getIntegerValue();

		//

		currentValue = currentSampler->getValue(wrapTString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentWrapT = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum wrapT = (GLenum)currentWrapT->getIntegerValue();

		//

		GlTfSamplerSP currentGlTfSampler = GlTfSamplerSP(new GlTfSampler(magFilter, minFilter, wrapS, wrapT));

		allSamplers[currentKey->getValue()] = currentGlTfSampler;
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeTextures(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP texturesString = JSONstringSP(new JSONstring("textures"));

	if (!jsonGlTf->hasKey(texturesString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(texturesString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP texturesObject = dynamic_pointer_cast<JSONobject>(value);

	JSONstringSP formatString = JSONstringSP(new JSONstring("format"));
	JSONstringSP internalFormatString = JSONstringSP(new JSONstring("internalFormat"));
	JSONstringSP samplerString = JSONstringSP(new JSONstring("sampler"));
	JSONstringSP sourceString = JSONstringSP(new JSONstring("source"));
	JSONstringSP targetString = JSONstringSP(new JSONstring("target"));
	JSONstringSP typeString = JSONstringSP(new JSONstring("type"));

	for (auto& currentKey : texturesObject->getAllKeys())
	{
		if (allTextures2D.find(currentKey->getValue()) != allTextures2D.end())
		{
			continue;
		}

		//

		JSONvalueSP currentValue = texturesObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentTexture = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentTexture->getValue(formatString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentFormat = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum format = (GLenum)currentFormat->getIntegerValue();

		//

		currentValue = currentTexture->getValue(internalFormatString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentInternalFormat = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum internalFormat = (GLenum)currentInternalFormat->getIntegerValue();

		//

		currentValue = currentTexture->getValue(samplerString);
		if (!currentValue->isJsonString())
		{
			return false;
		}

		JSONstringSP currentSampler = dynamic_pointer_cast<JSONstring>(currentValue);

		if (allSamplers.find(currentSampler->getValue()) == allSamplers.end())
		{
			return false;
		}

		GlTfSamplerSP sampler = allSamplers[currentSampler->getValue()];

		//

		currentValue = currentTexture->getValue(targetString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentTarget = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum target = (GLenum)currentTarget->getIntegerValue();

		if (target != GL_TEXTURE_2D)
		{
			glusLogPrint(GLUS_LOG_ERROR, "Only GL_TEXTURE_2D as target supported.");

			return false;
		}

		//

		currentValue = currentTexture->getValue(typeString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentType = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum type = (GLenum)currentType->getIntegerValue();

		//

		currentValue = currentTexture->getValue(sourceString);
		if (!currentValue->isJsonString())
		{
			return false;
		}

		JSONstringSP currentSource = dynamic_pointer_cast<JSONstring>(currentValue);


		Texture2DSP texture2D;

		uint32_t sizeOfData;

		if (allHdrImages.find(currentSource->getValue()) != allHdrImages.end())
		{
			const GLUShdrimage& hdrImage = allHdrImages[currentSource->getValue()];

			sizeOfData = 3 * sizeof(GLfloat) * hdrImage.width * hdrImage.height;

			texture2D = Texture2DManager::getInstance()->createTexture(currentKey->getValue(), internalFormat, hdrImage.width, hdrImage.height, format, type, (const uint8_t*)hdrImage.data, sizeOfData, true, sampler->getMinFilter(), sampler->getMagFilter(), sampler->getWrapS(), sampler->getWrapT(), 1.0f);
		}
		else if (allTgaImages.find(currentSource->getValue()) != allTgaImages.end())
		{
			const GLUStgaimage& tgaImage = allTgaImages[currentSource->getValue()];

			sizeOfData = sizeof(GLubyte) * tgaImage.width * tgaImage.height;

			if (tgaImage.format == GL_RGB)
			{
				sizeOfData *= 3;
			}
			else if (tgaImage.format == GL_RGBA)
			{
				sizeOfData *= 4;
			}

			texture2D = Texture2DManager::getInstance()->createTexture(currentKey->getValue(), internalFormat, tgaImage.width, tgaImage.height, format, type, (const uint8_t*)tgaImage.data, sizeOfData, true, sampler->getMinFilter(), sampler->getMagFilter(), sampler->getWrapS(), sampler->getWrapT(), 1.0f);
		}
		else
		{
			return false;
		}

		allTextures2D[currentKey->getValue()] = texture2D;
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeMaterials(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP materialsString = JSONstringSP(new JSONstring("materials"));

	if (!jsonGlTf->hasKey(materialsString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(materialsString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP materialsObject = dynamic_pointer_cast<JSONobject>(value);

	JSONstringSP instanceTechniqueString = JSONstringSP(new JSONstring("instanceTechnique"));
	JSONstringSP valuesString = JSONstringSP(new JSONstring("values"));

	JSONstringSP emissionString = JSONstringSP(new JSONstring("emission"));
	JSONstringSP diffuseString = JSONstringSP(new JSONstring("diffuse"));
	JSONstringSP reflectionCoefficientString = JSONstringSP(new JSONstring("reflectionCoefficient"));
	JSONstringSP roughnessString = JSONstringSP(new JSONstring("roughness"));
	JSONstringSP alphaString = JSONstringSP(new JSONstring("alpha"));

	for (auto& currentKey : materialsObject->getAllKeys())
	{
		if (allSurfaceMaterials.find(currentKey->getValue()) != allSurfaceMaterials.end())
		{
			continue;
		}

		//

		JSONvalueSP currentValue = materialsObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentMaterial = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentMaterial->getValue(instanceTechniqueString);
		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentInstanceTechnique = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentInstanceTechnique->getValue(valuesString);
		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentValues = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		Color emissionColor = Color::DEFAULT_EMISSIVE;
		Texture2DSP emissionTexture;

		currentValue = currentValues->getValue(emissionString);
		if (!decodeColor(emissionColor, currentValue) && !decodeTexture2D(emissionTexture, currentValue))
		{
			return false;
		}

		//

		Color diffuseColor = Color::DEFAULT_DIFFUSE;
		Texture2DSP diffuseTexture;

		currentValue = currentValues->getValue(diffuseString);
		if (!decodeColor(diffuseColor, currentValue) && !decodeTexture2D(diffuseTexture, currentValue))
		{
			return false;
		}

		//

		float reflectionCoefficient = 0.0f;
		Texture2DSP reflectionCoefficientTexture;

		currentValue = currentValues->getValue(reflectionCoefficientString);
		if (!decodeFloat(reflectionCoefficient, currentValue) && !decodeTexture2D(reflectionCoefficientTexture, currentValue))
		{
			return false;
		}

		//

		float roughness = 0.0f;
		Texture2DSP roughnessTexture;

		currentValue = currentValues->getValue(roughnessString);
		if (!decodeFloat(roughness, currentValue) && !decodeTexture2D(roughnessTexture, currentValue))
		{
			return false;
		}

		//

		float alpha = 0.0f;
		Texture2DSP alphaTexture;

		currentValue = currentValues->getValue(roughnessString);
		if (!decodeFloat(alpha, currentValue) && !decodeTexture2D(alphaTexture, currentValue))
		{
			return false;
		}

		//

		SurfaceMaterialSP currentSurfaceMaterial = SurfaceMaterialSP(new SurfaceMaterial(currentKey->getValue()));

		currentSurfaceMaterial->setEmissive(emissionColor);
		currentSurfaceMaterial->setEmissiveTexture(emissionTexture);

		currentSurfaceMaterial->setDiffuse(diffuseColor);
		currentSurfaceMaterial->setDiffuseTexture(diffuseTexture);

		currentSurfaceMaterial->setReflectionCoefficient(reflectionCoefficient);
		currentSurfaceMaterial->setReflectionCoefficientTexture(reflectionCoefficientTexture);

		currentSurfaceMaterial->setRoughness(roughness);
		currentSurfaceMaterial->setRoughnessTexture(roughnessTexture);

		currentSurfaceMaterial->setTransparency(alpha);
		currentSurfaceMaterial->setTransparencyTexture(alphaTexture);

		allSurfaceMaterials[currentKey->getValue()] = currentSurfaceMaterial;
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeMeshes(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP meshesString = JSONstringSP(new JSONstring("meshes"));

	if (!jsonGlTf->hasKey(meshesString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(meshesString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP meshesObject = dynamic_pointer_cast<JSONobject>(value);


	JSONstringSP primitivesString = JSONstringSP(new JSONstring("primitives"));
	JSONstringSP nameString = JSONstringSP(new JSONstring("name"));

	JSONstringSP attributesString = JSONstringSP(new JSONstring("attributes"));

	JSONstringSP positionString = JSONstringSP(new JSONstring("POSITION"));
	JSONstringSP normalString = JSONstringSP(new JSONstring("NORMAL"));
	JSONstringSP bitangentString = JSONstringSP(new JSONstring("BITANGENT"));
	JSONstringSP tangentString = JSONstringSP(new JSONstring("TANGENT"));
	JSONstringSP texCoordString = JSONstringSP(new JSONstring("TEXCOORD"));

	JSONstringSP boneIndices0String = JSONstringSP(new JSONstring("BONEINDICES0"));
	JSONstringSP boneIndices1String = JSONstringSP(new JSONstring("BONEINDICES1"));
	JSONstringSP boneWeights0String = JSONstringSP(new JSONstring("BONEWEIGHTS0"));
	JSONstringSP boneWeights1String = JSONstringSP(new JSONstring("BONEWEIGHTS1"));
	JSONstringSP boneCountersString = JSONstringSP(new JSONstring("BONECOUNTERS"));

	JSONstringSP indicesString = JSONstringSP(new JSONstring("indices"));
	JSONstringSP materialString = JSONstringSP(new JSONstring("material"));
	JSONstringSP primitiveString = JSONstringSP(new JSONstring("primitive"));

	for (auto& currentKey : meshesObject->getAllKeys())
	{
		if (allMeshes.find(currentKey->getValue()) != allMeshes.end())
		{
			continue;
		}

		//

		JSONvalueSP currentValue = meshesObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentMesh = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentMesh->getValue(primitivesString);
		if (!currentValue->isJsonArray())
		{
			return false;
		}

		JSONarraySP currentPrimitives = dynamic_pointer_cast<JSONarray>(currentValue);

		//

		GlTfMeshSP glTFMesh = GlTfMeshSP(new GlTfMesh(currentKey->getValue()));

		//
		//

		for (auto& currentElement : currentPrimitives->getAllValues())
		{
			if (!currentElement->isJsonObject())
			{
				return false;
			}

			JSONobjectSP currentPrimitive = dynamic_pointer_cast<JSONobject>(currentElement);

			//

			GlTfPrimitiveSP glTfPrimitive = GlTfPrimitiveSP(new GlTfPrimitive());

			//

			currentValue = currentPrimitive->getValue(attributesString);
			if (!currentValue->isJsonObject())
			{
				return false;
			}
			JSONobjectSP currentAttribute = dynamic_pointer_cast<JSONobject>(currentValue);

			//
			//

			if (!currentAttribute->hasKey(positionString))
			{
				return false;
			}
			currentValue = currentAttribute->getValue(positionString);
			GlTfAccessorSP position;
			if (!decodeAccessor(position, currentValue))
			{
				return false;
			}
			glTfPrimitive->setPosition(position);

			if (currentAttribute->hasKey(normalString))
			{
				currentValue = currentAttribute->getValue(normalString);
				GlTfAccessorSP normal;
				decodeAccessor(normal, currentValue);
				glTfPrimitive->setNormal(normal);
			}

			if (currentAttribute->hasKey(bitangentString))
			{
				currentValue = currentAttribute->getValue(bitangentString);
				GlTfAccessorSP bitangent;
				decodeAccessor(bitangent, currentValue);
				glTfPrimitive->setBitangent(bitangent);
			}

			if (currentAttribute->hasKey(tangentString))
			{
				currentValue = currentAttribute->getValue(tangentString);
				GlTfAccessorSP tangent;
				decodeAccessor(tangent, currentValue);
				glTfPrimitive->setTangent(tangent);
			}

			if (currentAttribute->hasKey(texCoordString))
			{
				currentValue = currentAttribute->getValue(texCoordString);
				GlTfAccessorSP texCoord;
				decodeAccessor(texCoord, currentValue);
				glTfPrimitive->setTexcoord(texCoord);
			}

			if (currentAttribute->hasKey(boneIndices0String))
			{
				currentValue = currentAttribute->getValue(boneIndices0String);
				GlTfAccessorSP boneIndices0;
				decodeAccessor(boneIndices0, currentValue);
				glTfPrimitive->setBoneIndices0(boneIndices0);
			}

			if (currentAttribute->hasKey(boneIndices1String))
			{
				currentValue = currentAttribute->getValue(boneIndices1String);
				GlTfAccessorSP boneIndices1;
				decodeAccessor(boneIndices1, currentValue);
				glTfPrimitive->setBoneIndices1(boneIndices1);
			}

			if (currentAttribute->hasKey(boneWeights0String))
			{
				currentValue = currentAttribute->getValue(boneWeights0String);
				GlTfAccessorSP boneWeights0;
				decodeAccessor(boneWeights0, currentValue);
				glTfPrimitive->setBoneWeights0(boneWeights0);
			}

			if (currentAttribute->hasKey(boneWeights1String))
			{
				currentValue = currentAttribute->getValue(boneWeights1String);
				GlTfAccessorSP boneWeights1;
				decodeAccessor(boneWeights1, currentValue);
				glTfPrimitive->setBoneWeights1(boneWeights1);
			}

			if (currentAttribute->hasKey(boneCountersString))
			{
				currentValue = currentAttribute->getValue(boneCountersString);
				GlTfAccessorSP boneCounters;
				decodeAccessor(boneCounters, currentValue);
				glTfPrimitive->setBoneCounters(boneCounters);
			}

			//
			//

			if (!currentPrimitive->hasKey(indicesString))
			{
				return false;
			}
			currentValue = currentPrimitive->getValue(indicesString);
			GlTfAccessorSP indices;
			decodeAccessor(indices, currentValue);
			glTfPrimitive->setIndices(indices);

			if (currentPrimitive->hasKey(materialString))
			{
				currentValue = currentPrimitive->getValue(materialString);
				if (!currentValue->isJsonString())
				{
					return false;
				}
				JSONstringSP currentMaterial = dynamic_pointer_cast<JSONstring>(currentValue);
				if (allSurfaceMaterials.find(currentMaterial->getValue()) == allSurfaceMaterials.end())
				{
					return false;
				}
				glTfPrimitive->setSurfaceMaterial(allSurfaceMaterials[currentMaterial->getValue()]);
			}

			if (!currentPrimitive->hasKey(primitiveString))
			{
				return false;
			}
			currentValue = currentPrimitive->getValue(primitiveString);
			if (!currentValue->isJsonNumber())
			{
				return false;
			}
			JSONnumberSP currentPrimitiveValue = dynamic_pointer_cast<JSONnumber>(currentValue);
			glTfPrimitive->setPrimitive((GLenum)currentPrimitiveValue->getIntegerValue());

			//

			glTFMesh->addPrimitive(glTfPrimitive);
		}

		//
		//

		allMeshes[currentKey->getValue()] = glTFMesh;
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeSkins(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP skinsString = JSONstringSP(new JSONstring("skins"));

	if (!jsonGlTf->hasKey(skinsString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(skinsString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP skinsObject = dynamic_pointer_cast<JSONobject>(value);


	JSONstringSP inverseBindMatricesString = JSONstringSP(new JSONstring("inverseBindMatrices"));
	JSONstringSP jointsString = JSONstringSP(new JSONstring("joints"));


	for (auto& currentKey : skinsObject->getAllKeys())
	{
		JSONvalueSP currentValue = skinsObject->getValue(currentKey);

		if (!currentValue->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentSkin = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		GlTfSkinSP glTFSkin = GlTfSkinSP(new GlTfSkin());

		//
		//

		currentValue = currentSkin->getValue(inverseBindMatricesString);

		GlTfAccessorSP inverseBindMatrices;

		if (!decodeAccessor(inverseBindMatrices, currentValue))
		{
			return false;
		}
		glTFSkin->setInverseBindMatrices(inverseBindMatrices);

		//

		currentValue = currentSkin->getValue(jointsString);
		if (!currentValue->isJsonArray())
		{
			return false;
		}

		JSONarraySP currentJoints = dynamic_pointer_cast<JSONarray>(currentValue);

		for (auto& currentElement : currentJoints->getAllValues())
		{
			if (!currentElement->isJsonString())
			{
				return false;
			}

			JSONstringSP currentJoint = dynamic_pointer_cast<JSONstring>(currentElement);

			glTFSkin->addJointName(currentJoint->getValue());
		}

		//

		allSkins[currentKey->getValue()] = glTFSkin;
	}

	return true;
}

GlTfNodeSP GlTfEntityDecoderFactory::decodeNode(const string& name, const JSONobjectSP& nodesObject)
{
	if (allNodes.find(name) != allNodes.end())
	{
		return allNodes[name];
	}

	//

	JSONstringSP nodeString = JSONstringSP(new JSONstring(name));

	if (!nodesObject->hasKey(nodeString))
	{
		return GlTfNodeSP();
	}

	JSONvalueSP currentValue = nodesObject->getValue(nodeString);

	if (!currentValue->isJsonObject())
	{
		return GlTfNodeSP();
	}

	JSONobjectSP currentNode = dynamic_pointer_cast<JSONobject>(currentValue);

	//

	JSONstringSP childrenString = JSONstringSP(new JSONstring("children"));

	JSONstringSP instanceSkinString = JSONstringSP(new JSONstring("instanceSkin"));
	JSONstringSP skeletonsString = JSONstringSP(new JSONstring("skeletons"));
	JSONstringSP skinString = JSONstringSP(new JSONstring("skin"));
	JSONstringSP sourcesString = JSONstringSP(new JSONstring("sources"));


	JSONstringSP jointString = JSONstringSP(new JSONstring("joint"));
	JSONstringSP meshesString = JSONstringSP(new JSONstring("meshes"));
	JSONstringSP translationString = JSONstringSP(new JSONstring("translation"));
	JSONstringSP rotationString = JSONstringSP(new JSONstring("rotation"));
	JSONstringSP scaleString = JSONstringSP(new JSONstring("scale"));

	JSONstringSP postTranslationString = JSONstringSP(new JSONstring("postTranslation"));
	JSONstringSP postRotationString = JSONstringSP(new JSONstring("postRotation"));
	JSONstringSP postScalingString = JSONstringSP(new JSONstring("postScaling"));
	JSONstringSP geometricTransformString = JSONstringSP(new JSONstring("geometricTransform"));

	//

	GlTfNodeSP glTfNode = GlTfNodeSP(new GlTfNode(name));

	//

	if (currentNode->hasKey(childrenString))
	{
		JSONvalueSP currentValue = currentNode->getValue(childrenString);
		if (!currentValue->isJsonArray())
		{
			return GlTfNodeSP();
		}
		JSONarraySP currentChildren = dynamic_pointer_cast<JSONarray>(currentValue);

		for (auto& currentChild : currentChildren->getAllValues())
		{
			if (!currentChild->isJsonString())
			{
				return GlTfNodeSP();
			}
			JSONstringSP currentChildName = dynamic_pointer_cast<JSONstring>(currentChild);

			//

			GlTfNodeSP child = decodeNode(currentChildName->getValue(), nodesObject);

			if (child.get() == nullptr)
			{
				return GlTfNodeSP();
			}

			glTfNode->addChild(child);
		}
	}

	//

	if (currentNode->hasKey(instanceSkinString))
	{
		JSONvalueSP currentValue = currentNode->getValue(instanceSkinString);
		if (!currentValue->isJsonObject())
		{
			return GlTfNodeSP();
		}
		JSONobjectSP currentInstanceSkin = dynamic_pointer_cast<JSONobject>(currentValue);

		GlTfInstanceSkinSP glTfInstanceSkin = GlTfInstanceSkinSP(new GlTfInstanceSkin());

		//

		currentValue = currentInstanceSkin->getValue(skeletonsString);
		if (!currentValue->isJsonArray())
		{
			return GlTfNodeSP();
		}
		JSONarraySP currentSkeletons = dynamic_pointer_cast<JSONarray>(currentValue);

		for (auto& currentElement : currentSkeletons->getAllValues())
		{
			if (!currentElement->isJsonString())
			{
				return GlTfNodeSP();
			}

			JSONstringSP currentSkeleton = dynamic_pointer_cast<JSONstring>(currentElement);

			glTfInstanceSkin->addSkeletonName(currentSkeleton->getValue());
		}

		//

		currentValue = currentInstanceSkin->getValue(skinString);
		if (!currentValue->isJsonString())
		{
			return GlTfNodeSP();
		}
		JSONstringSP currentSkin = dynamic_pointer_cast<JSONstring>(currentValue);

		if (allSkins.find(currentSkin->getValue()) == allSkins.end())
		{
			return GlTfNodeSP();
		}

		glTfInstanceSkin->setSkin(allSkins[currentSkin->getValue()]);

		//

		currentValue = currentInstanceSkin->getValue(sourcesString);
		if (!currentValue->isJsonArray())
		{
			return GlTfNodeSP();
		}
		JSONarraySP currentSources = dynamic_pointer_cast<JSONarray>(currentValue);

		for (auto& currentElement : currentSources->getAllValues())
		{
			if (!currentElement->isJsonString())
			{
				return GlTfNodeSP();
			}

			JSONstringSP currentSource = dynamic_pointer_cast<JSONstring>(currentElement);

			if (allMeshes.find(currentSource->getValue()) == allMeshes.end())
			{
				return GlTfNodeSP();
			}

			glTfInstanceSkin->addSource(allMeshes[currentSource->getValue()]);
		}

		//

		glTfNode->setInstanceSkin(glTfInstanceSkin);
	}

	if (currentNode->hasKey(jointString))
	{
		JSONvalueSP currentValue = currentNode->getValue(jointString);
		if (!currentValue->isJsonString())
		{
			return GlTfNodeSP();
		}
		JSONstringSP currentJoint = dynamic_pointer_cast<JSONstring>(currentValue);

		glTfNode->setJoint(true);
	}

	if (currentNode->hasKey(meshesString))
	{
		JSONvalueSP currentValue = currentNode->getValue(meshesString);
		if (!currentValue->isJsonArray())
		{
			return GlTfNodeSP();
		}
		JSONarraySP currentMeshes = dynamic_pointer_cast<JSONarray>(currentValue);

		for (auto& currentMesh : currentMeshes->getAllValues())
		{
			if (!currentMesh->isJsonString())
			{
				return GlTfNodeSP();
			}
			JSONstringSP currentMeshName = dynamic_pointer_cast<JSONstring>(currentMesh);

			//

			if (allMeshes.find(currentMeshName->getValue()) == allMeshes.end())
			{
				return GlTfNodeSP();
			}

			glTfNode->addMesh(allMeshes[currentMeshName->getValue()]);
		}
	}

	if (currentNode->hasKey(translationString))
	{
		JSONvalueSP currentValue = currentNode->getValue(translationString);

		Vector3 translation;

		if (!decodeVector3(translation, currentValue))
		{
			return GlTfNodeSP();
		}

		glTfNode->setTranslation(translation);
	}

	if (currentNode->hasKey(rotationString))
	{
		JSONvalueSP currentValue = currentNode->getValue(rotationString);

		Vector3 rotation;

		if (!decodeVector3(rotation, currentValue))
		{
			return GlTfNodeSP();
		}

		glTfNode->setRotation(rotation);
	}

	if (currentNode->hasKey(scaleString))
	{
		JSONvalueSP currentValue = currentNode->getValue(scaleString);

		Vector3 scale;

		if (!decodeVector3(scale, currentValue))
		{
			return GlTfNodeSP();
		}

		glTfNode->setScale(scale);
	}

	if (currentNode->hasKey(postTranslationString))
	{
		JSONvalueSP currentValue = currentNode->getValue(postTranslationString);

		Matrix4x4 postTranslation;

		if (!decodeMatrix4x4(postTranslation, currentValue))
		{
			return GlTfNodeSP();
		}

		glTfNode->setPostTranslation(postTranslation);
	}

	if (currentNode->hasKey(postRotationString))
	{
		JSONvalueSP currentValue = currentNode->getValue(postRotationString);

		Matrix4x4 postRotation;

		if (!decodeMatrix4x4(postRotation, currentValue))
		{
			return GlTfNodeSP();
		}

		glTfNode->setPostRotation(postRotation);
	}

	if (currentNode->hasKey(postScalingString))
	{
		JSONvalueSP currentValue = currentNode->getValue(postScalingString);

		Matrix4x4 postScaling;

		if (!decodeMatrix4x4(postScaling, currentValue))
		{
			return GlTfNodeSP();
		}

		glTfNode->setPostScaling(postScaling);
	}

	if (currentNode->hasKey(geometricTransformString))
	{
		JSONvalueSP currentValue = currentNode->getValue(geometricTransformString);

		Matrix4x4 geometricTransform;

		if (!decodeMatrix4x4(geometricTransform, currentValue))
		{
			return GlTfNodeSP();
		}

		glTfNode->setGeometricTransform(geometricTransform);
	}

	//

	if (allNodes.find(glTfNode->getName()) == allNodes.end())
	{
		allNodes[glTfNode->getName()] = glTfNode;
	}

	return glTfNode;
}

bool GlTfEntityDecoderFactory::decodeNodes(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP nodesString = JSONstringSP(new JSONstring("nodes"));

	if (!jsonGlTf->hasKey(nodesString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(nodesString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP nodesObject = dynamic_pointer_cast<JSONobject>(value);


	for (auto& currentKey : nodesObject->getAllKeys())
	{
		if (!currentKey->isJsonString())
		{
			return false;
		}

		JSONstringSP currentNode = dynamic_pointer_cast<JSONstring>(currentKey);

		//

		GlTfNodeSP glTfNode = decodeNode(currentNode->getValue(), nodesObject);

		if (glTfNode.get() == nullptr)
		{
			return false;
		}

		if (allNodes.find(glTfNode->getName()) == allNodes.end())
		{
			allNodes[glTfNode->getName()] = glTfNode;
		}
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeAnimations(const JSONobjectSP& jsonGlTf)
{
	JSONstringSP animationsString = JSONstringSP(new JSONstring("animations"));

	if (!jsonGlTf->hasKey(animationsString))
	{
		return true;
	}

	JSONvalueSP value = jsonGlTf->getValue(animationsString);

	if (!value->isJsonObject())
	{
		return false;
	}

	JSONobjectSP animationsObject = dynamic_pointer_cast<JSONobject>(value);


	for (auto& currentKey : animationsObject->getAllKeys())
	{
		if (!currentKey->isJsonString())
		{
			return false;
		}

		value = animationsObject->getValue(currentKey);

		if (!value->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentAnimation = dynamic_pointer_cast<JSONobject>(value);

		//

		GlTfAnimationSP glTfAnimation = GlTfAnimationSP(new GlTfAnimation());

		//

		JSONstringSP channelsString = JSONstringSP(new JSONstring("channels"));
		JSONstringSP samplerString = JSONstringSP(new JSONstring("sampler"));
		JSONstringSP targetString = JSONstringSP(new JSONstring("target"));
		JSONstringSP idString = JSONstringSP(new JSONstring("id"));
		JSONstringSP pathString = JSONstringSP(new JSONstring("path"));
		JSONstringSP elementString = JSONstringSP(new JSONstring("element"));

		JSONstringSP parametersString = JSONstringSP(new JSONstring("parameters"));

		JSONstringSP samplersString = JSONstringSP(new JSONstring("samplers"));
		JSONstringSP inputString = JSONstringSP(new JSONstring("input"));
		JSONstringSP interpolationString = JSONstringSP(new JSONstring("interpolation"));
		JSONstringSP outputString = JSONstringSP(new JSONstring("output"));

		JSONstringSP startTimeString = JSONstringSP(new JSONstring("startTime"));
		JSONstringSP stopTimeString = JSONstringSP(new JSONstring("stopTime"));

		//

		value = currentAnimation->getValue(channelsString);

		if (!value->isJsonArray())
		{
			return false;
		}

		JSONarraySP currentChannels = dynamic_pointer_cast<JSONarray>(value);


		value = currentAnimation->getValue(parametersString);

		if (!value->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentParameters = dynamic_pointer_cast<JSONobject>(value);


		value = currentAnimation->getValue(samplersString);

		if (!value->isJsonObject())
		{
			return false;
		}

		JSONobjectSP currentSamplers = dynamic_pointer_cast<JSONobject>(value);

		//

		value = currentAnimation->getValue(startTimeString);

		if (!value->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentStartTime = dynamic_pointer_cast<JSONnumber>(value);

		glTfAnimation->setStartTime(currentStartTime->getFloatValue());

		value = currentAnimation->getValue(stopTimeString);

		if (!value->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentStopTime = dynamic_pointer_cast<JSONnumber>(value);

		glTfAnimation->setStopTime(currentStopTime->getFloatValue());

		for (auto& currentElement : currentChannels->getAllValues())
		{
			if (!currentElement->isJsonObject())
			{
				return false;
			}

			JSONobjectSP currentChannel = dynamic_pointer_cast<JSONobject>(currentElement);

			//

			GlTfChannelSP glTfChannel = GlTfChannelSP(new GlTfChannel());

			//
			//

			value = currentChannel->getValue(targetString);
			if (!value->isJsonObject())
			{
				return false;
			}
			JSONobjectSP currentTarget = dynamic_pointer_cast<JSONobject>(value);


			value = currentTarget->getValue(idString);
			if (!value->isJsonString())
			{
				return false;
			}
			JSONstringSP currentId = dynamic_pointer_cast<JSONstring>(value);

			if (allNodes.find(currentId->getValue()) == allNodes.end())
			{
				return false;
			}

			glTfChannel->setTargetNode(allNodes[currentId->getValue()]);


			value = currentTarget->getValue(pathString);
			if (!value->isJsonString())
			{
				return false;
			}
			JSONstringSP currentPath = dynamic_pointer_cast<JSONstring>(value);

			glTfChannel->setTargetPath(currentPath->getValue());


			value = currentTarget->getValue(elementString);
			if (!value->isJsonString())
			{
				return false;
			}
			JSONstringSP currentTargetElement = dynamic_pointer_cast<JSONstring>(value);

			glTfChannel->setTargetElement(currentTargetElement->getValue());

			//

			value = currentChannel->getValue(samplerString);
			if (!value->isJsonString())
			{
				return false;
			}
			JSONstringSP currentSampler = dynamic_pointer_cast<JSONstring>(value);

			if (!currentSamplers->hasKey(currentSampler))
			{
				return false;
			}
			value = currentSamplers->getValue(currentSampler);
			if (!value->isJsonObject())
			{
				return false;
			}
			JSONobjectSP currentSamplerObject = dynamic_pointer_cast<JSONobject>(value);


			value = currentSamplerObject->getValue(inputString);
			if (!value->isJsonString())
			{
				return false;
			}
			JSONstringSP currentInput = dynamic_pointer_cast<JSONstring>(value);

			if (!currentParameters->hasKey(currentInput))
			{
				return false;
			}

			value = currentSamplerObject->getValue(interpolationString);
			if (!value->isJsonString())
			{
				return false;
			}
			JSONstringSP currentInterpolation = dynamic_pointer_cast<JSONstring>(value);

			if (!currentParameters->hasKey(currentInterpolation))
			{
				return false;
			}

			value = currentSamplerObject->getValue(outputString);
			if (!value->isJsonString())
			{
				return false;
			}
			JSONstringSP currentOutput = dynamic_pointer_cast<JSONstring>(value);

			if (!currentParameters->hasKey(currentOutput))
			{
				return false;
			}

			//

			GlTfAccessorSP input;
			GlTfAccessorSP interpolator;
			GlTfAccessorSP output;

			if (!decodeAccessor(input, currentParameters->getValue(currentInput)))
			{
				return false;
			}
			glTfChannel->setTime(input);

			if (!decodeAccessor(interpolator, currentParameters->getValue(currentInterpolation)))
			{
				return false;
			}
			glTfChannel->setInterpolator(interpolator);

			if (!decodeAccessor(output, currentParameters->getValue(currentOutput)))
			{
				return false;
			}
			glTfChannel->setValue(output);

			//
			//

			glTfAnimation->addChannel(glTfChannel);
		}

		//

		allAnimations[currentKey->getValue()] = glTfAnimation;
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeFloat(float& number, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonNumber())
	{
		return false;
	}

	const JSONnumberSP jsonNumber = dynamic_pointer_cast<JSONnumber>(jsonValue);

	number = jsonNumber->getFloatValue();

	return true;
}

bool GlTfEntityDecoderFactory::decodeInteger(int32_t& number, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonNumber())
	{
		return false;
	}

	const JSONnumberSP jsonNumber = dynamic_pointer_cast<JSONnumber>(jsonValue);

	number = jsonNumber->getIntegerValue();

	return true;
}

bool GlTfEntityDecoderFactory::decodeString(string& value, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonString())
	{
		return false;
	}

	const JSONstringSP jsonString = dynamic_pointer_cast<JSONstring>(jsonValue);

	value = jsonString->getValue();

	return true;
}

bool GlTfEntityDecoderFactory::decodeMatrix4x4(Matrix4x4& matrix, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonArray())
	{
		return false;
	}

	const JSONarraySP matrixArray = dynamic_pointer_cast<JSONarray>(jsonValue);

	if (matrixArray->size() != 16)
	{
		return false;
	}

	float number;

	int32_t index = 0;
	for (auto& jsonNumber : matrixArray->getAllValues())
	{
		if (!decodeFloat(number, jsonNumber))
		{
			return false;
		}

		matrix.setM(number, index++);
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeMatrix3x3(Matrix3x3& matrix, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonArray())
	{
		return false;
	}

	const JSONarraySP matrixArray = dynamic_pointer_cast<JSONarray>(jsonValue);

	if (matrixArray->size() != 9)
	{
		return false;
	}

	float number;

	int32_t index = 0;
	for (auto& jsonNumber : matrixArray->getAllValues())
	{
		if (!decodeFloat(number, jsonNumber))
		{
			return false;
		}

		matrix.setM(number, index++);
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeVector3(Vector3& vector, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonArray())
	{
		return false;
	}

	const JSONarraySP vectorArray = dynamic_pointer_cast<JSONarray>(jsonValue);

	if (vectorArray->size() != 3)
	{
		return false;
	}

	float number;

	int32_t index = 0;
	for (auto& jsonNumber : vectorArray->getAllValues())
	{
		if (!decodeFloat(number, jsonNumber))
		{
			return false;
		}

		vector.setV(number, index++);
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeColor(Color& color, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonArray())
	{
		return false;
	}

	const JSONarraySP colorArray = dynamic_pointer_cast<JSONarray>(jsonValue);

	if (colorArray->size() != 4)
	{
		return false;
	}

	float number;

	int32_t index = 0;
	for (auto& jsonNumber : colorArray->getAllValues())
	{
		if (!decodeFloat(number, jsonNumber))
		{
			return false;
		}

		color.setRGBA(number, index++);
	}

	return true;
}

bool GlTfEntityDecoderFactory::decodeTexture2D(Texture2DSP& texture, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonString())
	{
		return false;
	}

	const JSONstringSP textureString = dynamic_pointer_cast<JSONstring>(jsonValue);

	if (allTextures2D.find(textureString->getValue()) == allTextures2D.end())
	{
		return false;
	}

	texture = allTextures2D.at(textureString->getValue());

	return true;
}

bool GlTfEntityDecoderFactory::decodeAccessor(GlTfAccessorSP& accessor, const JSONvalueSP& jsonValue) const
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (!jsonValue->isJsonString())
	{
		return false;
	}

	const JSONstringSP accessorString = dynamic_pointer_cast<JSONstring>(jsonValue);

	if (allAccessors.find(accessorString->getValue()) == allAccessors.end())
	{
		return false;
	}

	accessor = allAccessors.at(accessorString->getValue());

	return true;
}

ModelEntitySP GlTfEntityDecoderFactory::loadGlTfModelFile(const string& identifier, const string& fileName, const string& folderName, float scale)
{
	ModelEntitySP result;

	GLUStextfile textfile;

	string completeFilename = folderName + fileName;

	if (!glusFileLoadText((const GLUSchar*)completeFilename.c_str(), &textfile))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not load '%s'", completeFilename.c_str());

		return result;
	}

	JSONdecoder decoder;

	string jsonText((char*)textfile.text);

	JSONvalueSP jsonResult;

	if (!decoder.decode(jsonText, jsonResult))
	{
		glusFileDestroyText(&textfile);

		glusLogPrint(GLUS_LOG_ERROR, "Could not load '%s'", completeFilename.c_str());

		return result;
	}

	glusFileDestroyText(&textfile);

	//

	glusLogPrint(GLUS_LOG_INFO, "Decoded '%s'", completeFilename.c_str());

	nodeTreeFactory.reset();

	doReset = true;

	animated = false;

	skinned = false;

	//

	if (!jsonResult->isJsonObject())
	{
		glusLogPrint(GLUS_LOG_ERROR, "glTF not found");

		return result;
	}

	JSONobjectSP jsonGlTf = dynamic_pointer_cast<JSONobject>(jsonResult);

	//

	JSONstringSP nodesString = JSONstringSP(new JSONstring("nodes"));
	JSONstringSP sceneString = JSONstringSP(new JSONstring("scene"));
	JSONstringSP scenesString = JSONstringSP(new JSONstring("scenes"));

	//

	NodeSP rootNode;
	int32_t numberJoints;

	//

	JSONstringSP key;
	JSONvalueSP value;

	string sceneValue;
	value = jsonGlTf->getValue(sceneString);
	if (!decodeString(sceneValue, value))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Scene not found");

		return result;
	}

	JSONstringSP usedSceneString = JSONstringSP(new JSONstring(sceneValue));

	//

	string scenesValue;
	value = jsonGlTf->getValue(scenesString);
	if (!value->isJsonObject())
	{
		glusLogPrint(GLUS_LOG_ERROR, "Scenes not found");

		return result;
	}
	JSONobjectSP scenesObject = dynamic_pointer_cast<JSONobject>(value);

	//

	value = scenesObject->getValue(usedSceneString);
	if (!value->isJsonObject())
	{
		glusLogPrint(GLUS_LOG_ERROR, "Used scene not found");

		return result;
	}
	JSONobjectSP usedSceneObject = dynamic_pointer_cast<JSONobject>(value);

	//

	value = usedSceneObject->getValue(nodesString);
	if (!value->isJsonArray())
	{
		glusLogPrint(GLUS_LOG_ERROR, "Nodes not found");

		return result;
	}
	JSONarraySP nodesArray = dynamic_pointer_cast<JSONarray>(value);

	//

	if (nodesArray->size() != 1)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Only one root node allowed");

		return result;
	}

	value = nodesArray->getValueAt(0);
	if (!value->isJsonString())
	{
		glusLogPrint(GLUS_LOG_ERROR, "Root node not found");

		return result;
	}
	JSONstringSP rootNodeString = dynamic_pointer_cast<JSONstring>(value);

	//

	// Decode Buffers etc.

	if (!decodeBuffers(jsonGlTf, folderName))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode buffers");

		cleanUp();

		return result;
	}

	if (!decodeBufferViews(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode buffer views");

		cleanUp();

		return result;
	}

	if (!decodeAccessors(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode accessors");

		cleanUp();

		return result;
	}

	//

	if (!decodeImages(jsonGlTf, folderName))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode images");

		cleanUp();

		return result;
	}

	if (!decodeSamplers(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode samplers");

		cleanUp();

		return result;
	}

	if (!decodeTextures(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode textures");

		cleanUp();

		return result;
	}

	//

	if (!decodeMaterials(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode materials");

		cleanUp();

		return result;
	}

	//

	if (!decodeMeshes(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode meshes");

		cleanUp();

		return result;
	}

	//

	if (!decodeSkins(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode skins");

		cleanUp();

		return result;
	}

	//

	if (!decodeNodes(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode nodes");

		cleanUp();

		return result;
	}

	//

	if (!decodeAnimations(jsonGlTf))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not decode animations");

		cleanUp();

		return result;
	}

	//

	if (allNodes.find(rootNodeString->getValue()) == allNodes.end())
	{
		glusLogPrint(GLUS_LOG_ERROR, "Root node '%s' not found", rootNodeString->getValue().c_str());

		cleanUp();

		return result;
	}

	rootNode = buildNode(NodeSP(), allNodes[rootNodeString->getValue()], Matrix4x4());

	if (rootNode.get() == nullptr)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not create node tree");

		cleanUp();

		return result;
	}

	numberJoints = nodeTreeFactory.createIndex();

	// Set inverse bind matrices of nodes.

	for (auto& currentSkinPair : allSkins)
	{
		auto& currentSkin = currentSkinPair.second;

		const float* currentData = (const float*)currentSkin->getInverseBindMatrices()->getData();

		for (auto& currentJointName : currentSkin->getAllJointNames())
		{
			Matrix4x4 currentInverseBindMatrix(currentData);

			nodeTreeFactory.setInverseBindMatrix(currentJointName, currentInverseBindMatrix);

			currentData += 16;
		}
	}

	//

	float absMaxX = glusMathMaxf(fabs(maxX), fabs(minX));
	float absMaxY = glusMathMaxf(fabs(maxY), fabs(minY));
	float absMaxZ = glusMathMaxf(fabs(maxZ), fabs(minZ));

	float newRadius = glusMathLengthf(absMaxX, absMaxY, absMaxZ);

	BoundingSphere boundingSphere;
	boundingSphere.setRadius(newRadius);

	// Create the model.

	ModelSP model = ModelSP(new Model(boundingSphere, rootNode, numberJoints, animated, skinned));

	// Create the model entity.

	result = ModelEntitySP(new ModelEntity(identifier, model, scale, scale, scale));

	//

	cleanUp();

	nodeTreeFactory.reset();

	animated = false;

	skinned = false;

	return result;
}

void GlTfEntityDecoderFactory::processMinMax(const float* vertices, int32_t numberVertices, const Matrix4x4& matrix)
{
	GLfloat vertex[4];

	// Calculate bounding sphere from existing vertices in mesh
	for (int32_t i = 0; i < numberVertices; i++)
	{
		glusMatrix4x4MultiplyPoint4f(vertex, matrix.getM(), &vertices[i * 4]);

		if (doReset)
		{
			minX = vertex[0];
			maxX = vertex[0];
			minY = vertex[1];
			maxY = vertex[1];
			minZ = vertex[2];
			maxZ = vertex[2];

			doReset = false;
		}
		else
		{
			if (vertex[0] < minX)
			{
				minX = vertex[0];
			}
			if (vertex[0] > maxX)
			{
				maxX = vertex[0];
			}
			if (vertex[1] < minY)
			{
				minY = vertex[1];
			}
			if (vertex[1] > maxY)
			{
				maxY = vertex[1];
			}
			if (vertex[2] < minZ)
			{
				minZ = vertex[2];
			}
			if (vertex[2] > maxZ)
			{
				maxZ = vertex[2];
			}
		}
	}
}

NodeSP GlTfEntityDecoderFactory::buildNode(const NodeSP& parentNode, const GlTfNodeSP& node, const Matrix4x4& parentMatrix)
{
	Matrix4x4 newParentMatrix(parentMatrix);

	if (node.get() == nullptr)
	{
		return NodeSP();
	}

	MeshSP mesh;
	CameraSP camera;
	LightSP light;
	vector<AnimationStackSP> allAnimStacks;

	//

	for (auto& currentMesh : node->getAllMeshes())
	{
		string name;
		uint32_t numberVertices;

		float* vertices = nullptr;
		float* normals = nullptr;
		float* bitangents = nullptr;
		float* tangents = nullptr;
		float* texCoords = nullptr;

		float* boneIndices0 = nullptr;
		float* boneIndices1 = nullptr;
		float* boneWeights0 = nullptr;
		float* boneWeights1 = nullptr;
		float* boneCounters = nullptr;

		uint32_t numberIndices;
		uint32_t* indices = nullptr;
		map<int32_t, SubMeshSP> subMeshes;
		map<int32_t, SurfaceMaterialSP> surfaceMaterials;

		name = currentMesh->getName();

		int32_t index = 0;

		for (auto& currentPrimitive : currentMesh->getAllPrimitives())
		{
			// Only shared attributes supported
			if (index == 0)
			{
				numberVertices = static_cast<uint32_t>(currentPrimitive->getPosition()->getCount());

				vertices = new float[4 * numberVertices];
				memcpy(vertices, currentPrimitive->getPosition()->getData(), 4 * sizeof(float) * numberVertices);

				if (currentPrimitive->getNormal().get() != nullptr)
				{
					normals = new float[3 * numberVertices];
					memcpy(normals, currentPrimitive->getNormal()->getData(), 3 * sizeof(float) * numberVertices);
				}

				if (currentPrimitive->getBitangent().get() != nullptr)
				{
					bitangents = new float[3 * numberVertices];
					memcpy(bitangents, currentPrimitive->getBitangent()->getData(), 3 * sizeof(float) * numberVertices);
				}

				if (currentPrimitive->getTangent().get() != nullptr)
				{
					tangents = new float[3 * numberVertices];
					memcpy(tangents, currentPrimitive->getTangent()->getData(), 3 * sizeof(float) * numberVertices);
				}

				if (currentPrimitive->getTexcoord().get() != nullptr)
				{
					texCoords = new float[2 * numberVertices];
					memcpy(texCoords, currentPrimitive->getTexcoord()->getData(), 2 * sizeof(float) * numberVertices);
				}

				//

				if (currentPrimitive->getBoneIndices0().get() != nullptr)
				{
					boneIndices0 = new float[4 * numberVertices];
					memcpy(boneIndices0, currentPrimitive->getBoneIndices0()->getData(), 4 * sizeof(float) * numberVertices);
				}

				if (currentPrimitive->getBoneIndices1().get() != nullptr)
				{
					boneIndices1 = new float[4 * numberVertices];
					memcpy(boneIndices1, currentPrimitive->getBoneIndices1()->getData(), 4 * sizeof(float) * numberVertices);
				}

				if (currentPrimitive->getBoneWeights0().get() != nullptr)
				{
					boneWeights0 = new float[4 * numberVertices];
					memcpy(boneWeights0, currentPrimitive->getBoneWeights0()->getData(), 4 * sizeof(float) * numberVertices);
				}

				if (currentPrimitive->getBoneWeights1().get() != nullptr)
				{
					boneWeights1 = new float[4 * numberVertices];
					memcpy(boneWeights1, currentPrimitive->getBoneWeights1()->getData(), 4 * sizeof(float) * numberVertices);
				}

				if (currentPrimitive->getBoneCounters().get() != nullptr)
				{
					boneCounters = new float[numberVertices];
					memcpy(boneCounters, currentPrimitive->getBoneCounters()->getData(), sizeof(float) * numberVertices);
				}

				//

				numberIndices = static_cast<uint32_t>(currentPrimitive->getIndices()->getCount());

				indices = new uint32_t[numberIndices];
				memcpy(indices, currentPrimitive->getIndices()->getData(), sizeof(uint32_t) * numberIndices);
			}

			SubMeshSP currentSubMesh = SubMeshSP(new SubMesh(currentPrimitive->getIndices()->getByteOffset(), currentPrimitive->getIndices()->getCount()));

			subMeshes[index] = currentSubMesh;

			surfaceMaterials[index] = currentPrimitive->getSurfaceMaterial();

			index++;
		}

		mesh = MeshSP(new Mesh(name, numberVertices, vertices, normals, bitangents, tangents, texCoords, numberIndices, indices, subMeshes, surfaceMaterials));

		if (boneIndices0 && boneIndices1 && boneWeights0 && boneWeights1 && boneCounters)
		{
			mesh->addSkinningData(boneIndices0, boneIndices1, boneWeights0, boneWeights1, boneCounters);

			skinned = true;
		}

		// Only one mesh supported.
		break;
	}


	// Add animations.

	if (allAnimations.size() > 0)
	{
		animated = true;

		for (auto& currentAnimationPair : allAnimations)
		{
			auto& currentAnimation = currentAnimationPair.second;

			AnimationStackSP currentAnimationStack = AnimationStackSP(new AnimationStack(currentAnimationPair.first, currentAnimation->getStartTime(), currentAnimation->getStopTime()));

			allAnimStacks.push_back(currentAnimationStack);

			// Note: Currently only supporting one animation layer.
			AnimationLayerSP currentAnimationLayer = AnimationLayerSP(new AnimationLayer());

			currentAnimationStack->addAnimationLayer(currentAnimationLayer);

			for (auto& currentChannel : currentAnimation->getAllChannels())
			{
				if (currentChannel->getTargetNode()->getName() == node->getName())
				{
					for (int32_t i = 0; i < currentChannel->getTime()->getCount(); i++)
					{
						float time = ((float*)currentChannel->getTime()->getData())[i];
						float value = ((float*)currentChannel->getValue()->getData())[i];
						uint32_t interpolatorIndex = ((uint32_t*)currentChannel->getInterpolator()->getData())[i];

						const Interpolator* interpolator;
						switch (interpolatorIndex)
						{
							case 0:
								interpolator = &ConstantInterpolator::interpolator;
								break;
							case 1:
								interpolator = &LinearInterpolator::interpolator;
								break;
							case 2:
								interpolator = &CubicInterpolator::interpolator;
								break;
							default:
								return NodeSP();
						}

						enum AnimationLayer::eCHANNELS_XYZ channel;
						if (currentChannel->getTargetElement() == "x")
						{
							channel = AnimationLayer::X;
						}
						else if (currentChannel->getTargetElement() == "y")
						{
							channel = AnimationLayer::Y;
						}
						else if (currentChannel->getTargetElement() == "z")
						{
							channel = AnimationLayer::Z;
						}
						else
						{
							return NodeSP();
						}

						if (currentChannel->getTargetPath() == "translation")
						{
							currentAnimationLayer->addTranslationValue(channel, time, value, *interpolator);
						}
						else if (currentChannel->getTargetPath() == "rotation")
						{
							currentAnimationLayer->addRotationValue(channel, time, value, *interpolator);
						}
						else if (currentChannel->getTargetPath() == "scale")
						{
							currentAnimationLayer->addScalingValue(channel, time, value, *interpolator);
						}
						else
						{
							return NodeSP();
						}
					}

				}
			}
		}
	}

	//

	string parentNodeName = parentNode.get() ? parentNode->getName() : "[NULL]";

	NodeSP result = nodeTreeFactory.createNode(node->getName(), parentNodeName, node->getTranslation().getV(), node->getPostTranslation(), node->getRotation().getV(), node->getPostRotation(), node->getScale().getV(), node->getPostScaling(), node->getGeometricTransform(), mesh, camera, light, allAnimStacks);

	//

	if (node->isJoint())
	{
		nodeTreeFactory.setJoint(node->getName());
	}

	//

	if (result->getMesh().get() != nullptr)
	{
		Matrix4x4 matrix;
		Matrix4x4 localMatrix;

		result->calculateLocalMatrix(localMatrix);

		newParentMatrix = newParentMatrix * localMatrix;

		matrix = newParentMatrix * result->getGeometricTransformMatrix();

		// Update the min max for the final bounding sphere
		processMinMax(result->getMesh()->getVertices(), result->getMesh()->getNumberVertices(), matrix);
	}

	//

	for (auto& currentChild : node->getAllChildren())
	{
		NodeSP child = buildNode(result, currentChild, newParentMatrix);

		if (child.get() == nullptr)
		{
			return NodeSP();
		}
	}

	return result;
}

void GlTfEntityDecoderFactory::cleanUp()
{
	for (auto& currentBuffer : allBuffers)
	{
		glusFileDestroyBinary(&currentBuffer.second);
	}
	allBuffers.clear();

	allBufferViews.clear();

	allAccessors.clear();


	for (auto& currentTgaImage : allTgaImages)
	{
		glusImageDestroyTga(&currentTgaImage.second);
	}
	allTgaImages.clear();

	for (auto& currentHdrImage : allHdrImages)
	{
		glusImageDestroyHdr(&currentHdrImage.second);
	}
	allHdrImages.clear();

	allSamplers.clear();

	allTextures2D.clear();


	allSurfaceMaterials.clear();


	allMeshes.clear();


	allSkins.clear();


	allNodes.clear();


	allAnimations.clear();
}

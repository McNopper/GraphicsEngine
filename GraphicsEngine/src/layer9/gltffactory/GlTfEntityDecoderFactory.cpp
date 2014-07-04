/*
 * GlTfEntityDecoderFactory.cpp
 *
 *  Created on: 02.07.2014
 *      Author: nopper
 */

#include "../../layer0/json/JSONdecoder.h"

#include "GlTfEntityDecoderFactory.h"

using namespace std;

GlTfEntityDecoderFactory::GlTfEntityDecoderFactory()
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

		if (!glusLoadBinaryFile((GLUSchar*)(folderName + currentUri->getValue()).c_str(), &binaryfile))
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

			if (!glusLoadTgaImage((GLUSchar*)(folderName + currentUri->getValue()).c_str(), &tgaimage))
			{
				return false;
			}

			allTgaImages[currentUri->getValue()] = tgaimage;
		}
		else if (extension == "hdr")
		{
			glusLogPrint(GLUS_LOG_INFO, "Loading image '%s'", (folderName + currentUri->getValue()).c_str());

			if (!glusLoadHdrImage((GLUSchar*)(folderName + currentUri->getValue()).c_str(), &hdrimage))
			{
				return false;
			}

			allHdrImages[currentUri->getValue()] = hdrimage;
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

		JSONobjectSP currentAccessor = dynamic_pointer_cast<JSONobject>(currentValue);

		//

		currentValue = currentAccessor->getValue(magFilterString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentMagFilter = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum magFilter = (GLenum)currentMagFilter->getIntegerValue();

		//

		currentValue = currentAccessor->getValue(minFilterString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentMinFilter = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum minFilter = (GLenum)currentMinFilter->getIntegerValue();

		//

		currentValue = currentAccessor->getValue(wrapSString);
		if (!currentValue->isJsonNumber())
		{
			return false;
		}

		JSONnumberSP currentWrapS = dynamic_pointer_cast<JSONnumber>(currentValue);

		GLenum wrapS = (GLenum)currentWrapS->getIntegerValue();

		//

		currentValue = currentAccessor->getValue(wrapTString);
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

ModelEntitySP GlTfEntityDecoderFactory::loadGlTfModelFile(const string& identifier, const string& fileName, const string& folderName, float scale)
{
	ModelEntitySP result;

	GLUStextfile textfile;

	string completeFilename = folderName + fileName;

	if (!glusLoadTextFile((const GLUSchar*)completeFilename.c_str(), &textfile))
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not load '%s'", completeFilename.c_str());

		return result;
	}

	JSONdecoder decoder;

	string jsonText((char*)textfile.text);

	JSONvalueSP jsonResult;

	if (!decoder.decode(jsonText, jsonResult))
	{
		glusDestroyTextFile(&textfile);

		glusLogPrint(GLUS_LOG_ERROR, "Could not load '%s'", completeFilename.c_str());

		return result;
	}

	glusDestroyTextFile(&textfile);

	//

	glusLogPrint(GLUS_LOG_INFO, "Decoded '%s'", completeFilename.c_str());

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

	BoundingSphere boundingSphere;
	NodeSP rootNode;
	int32_t numberJoints = 0.0f;
	bool animationData = false;
	bool skinned = false;

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

	// TODO Decode Textures.

	//

	// TODO Decode Meshes.

	//

	// TODO Decode Materials.

	//

	// TODO Decode Animations.

	//

	// TODO Decode Skins.

	//

	// TODO Decode Nodes.

	//

	// TODO Calculate bounding box.

	// TODO Build graphics engine node tree.

	if (rootNode.get() == nullptr)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not create node tree");

		cleanUp();

		return result;
	}

	// Create the model.

	ModelSP model = ModelSP(new Model(boundingSphere, rootNode, numberJoints, animationData, skinned));

	// Create the model entity.

	result = ModelEntitySP(new ModelEntity(identifier, model, scale, scale, scale));

	//

	cleanUp();

	return result;
}

void GlTfEntityDecoderFactory::cleanUp()
{
	for (auto& currentBuffer : allBuffers)
	{
		glusDestroyBinaryFile(&currentBuffer.second);
	}
	allBuffers.clear();

	allBufferViews.clear();

	allAccessors.clear();


	for (auto& currentTgaImage : allTgaImages)
	{
		glusDestroyTgaImage(&currentTgaImage.second);
	}
	allTgaImages.clear();

	for (auto& currentHdrImage : allHdrImages)
	{
		glusDestroyHdrImage(&currentHdrImage.second);
	}
	allHdrImages.clear();

	allSamplers.clear();
}

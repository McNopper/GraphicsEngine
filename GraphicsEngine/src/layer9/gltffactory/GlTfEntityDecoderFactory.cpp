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

NodeSP GlTfEntityDecoderFactory::createNode(const JSONstringSP& nodeName, const JSONobjectSP& jsonGlTf) const
{
	// TODO Parse through nodes etc.

	return NodeSP();
}

ModelEntitySP GlTfEntityDecoderFactory::loadGlTfModelFile(const string& identifier, const string& fileName, const string& folderName, float scale) const
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

	rootNode = createNode(rootNodeString, jsonGlTf);

	if (rootNode.get() == nullptr)
	{
		glusLogPrint(GLUS_LOG_ERROR, "Could not create node tree");

		return result;
	}

	// Create the model.

	ModelSP model = ModelSP(new Model(boundingSphere, rootNode, numberJoints, animationData, skinned));

	// Create the model entity.

	result = ModelEntitySP(new ModelEntity(identifier, model, scale, scale, scale));

	return result;
}

/*
 * GlTfEntityFactory.cpp
 *
 *  Created on: 18.06.2014
 *      Author: nopper
 */

#include "../../layer0/json/JSONencoder.h"

#include "GlTfEntityFactory.h"

using namespace std;

GlTfEntityFactory::GlTfEntityFactory()
{
}

GlTfEntityFactory::~GlTfEntityFactory()
{
}

void GlTfEntityFactory::addImage(JSONobjectSP& imagesObject, const JSONstringSP& imageString, const Texture2DSP& texture) const
{
	auto walker = imagesObject->getAllKeys().begin();

	while (walker != imagesObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == imageString->getValue())
		{
			return;
		}

		walker++;
	}

	JSONobjectSP imageObject = JSONobjectSP(new JSONobject());

	imagesObject->addKeyValue(imageString, imageObject);

	//

	JSONstringSP pathString = JSONstringSP(new JSONstring("path"));

	JSONstringSP valueString;

	string path = texture->getIdentifier();

	if (texture->getType() == GL_FLOAT || texture->getType() == GL_HALF_FLOAT)
	{
		path += ".hdr";
	}
	else
	{
		path += ".tga";
	}

	valueString = JSONstringSP(new JSONstring(path));
	imageObject->addKeyValue(pathString, valueString);

	// TODO Save image.
}

void GlTfEntityFactory::addSampler(JSONobjectSP& samplersObject, const JSONstringSP& samplerString, const Texture2DSP& texture) const
{
	auto walker = samplersObject->getAllKeys().begin();

	while (walker != samplersObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == samplerString->getValue())
		{
			return;
		}

		walker++;
	}

	JSONobjectSP samplerObject = JSONobjectSP(new JSONobject());

	samplersObject->addKeyValue(samplerString, samplerObject);

	//

	JSONstringSP magFilterString = JSONstringSP(new JSONstring("magFilter"));
	JSONstringSP minFilterString = JSONstringSP(new JSONstring("minFilter"));
	JSONstringSP wrapSString = JSONstringSP(new JSONstring("wrapS"));
	JSONstringSP wrapTString = JSONstringSP(new JSONstring("wrapT"));

	JSONnumberSP valueNumber;

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getMagFilter()));
	samplerObject->addKeyValue(magFilterString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getMinFilter()));
	samplerObject->addKeyValue(minFilterString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getWrapS()));
	samplerObject->addKeyValue(wrapSString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getWrapT()));
	samplerObject->addKeyValue(wrapTString, valueNumber);
}

void GlTfEntityFactory::addTexture(JSONobjectSP& texturesObject, const JSONstringSP& textureString, const Texture2DSP& texture) const
{
	auto walker = texturesObject->getAllKeys().begin();

	while (walker != texturesObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == textureString->getValue())
		{
			return;
		}

		walker++;
	}

	JSONobjectSP textureObject = JSONobjectSP(new JSONobject());

	texturesObject->addKeyValue(textureString, textureObject);

	//

	JSONstringSP formatString = JSONstringSP(new JSONstring("format"));
	JSONstringSP internalFormatString = JSONstringSP(new JSONstring("internalFormat"));
	JSONstringSP samplerString = JSONstringSP(new JSONstring("sampler"));
	JSONstringSP sourceString = JSONstringSP(new JSONstring("source"));
	JSONstringSP targetString = JSONstringSP(new JSONstring("target"));
	JSONstringSP typeString = JSONstringSP(new JSONstring("type"));

	JSONnumberSP valueNumber;
	JSONstringSP valueString;

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getFormat()));
	textureObject->addKeyValue(formatString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getInternalFormat()));
	textureObject->addKeyValue(internalFormatString, valueNumber);

	valueString =  JSONstringSP(new JSONstring("sampler_" + texture->getIdentifier()));;
	textureObject->addKeyValue(samplerString, valueString);

	valueString =  JSONstringSP(new JSONstring("image_" + texture->getIdentifier()));;
	textureObject->addKeyValue(sourceString, valueString);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getTarget()));
	textureObject->addKeyValue(targetString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)texture->getType()));
	textureObject->addKeyValue(typeString, valueNumber);
}

void GlTfEntityFactory::addTextureSamplerImage(JSONobjectSP& texturesObject, const JSONstringSP& textureString, JSONobjectSP& samplersObject, const JSONstringSP& samplerString, JSONobjectSP& imagesObject, const JSONstringSP& imageString, const Texture2DSP& texture) const
{
	addTexture(texturesObject, textureString, texture);

	addSampler(samplersObject, samplerString, texture);

	addImage(imagesObject, imageString, texture);
}

bool GlTfEntityFactory::saveGlTfModelFile(const ModelEntitySP& modelEntity, const string& identifier)
{
	if (modelEntity.get() == nullptr)
	{
		return false;
	}

	JSONobjectSP glTF = JSONobjectSP(new JSONobject());

	//
	// Go through model entity and create glTF.
	//

	JSONstringSP imagesString = JSONstringSP(new JSONstring("images"));
	JSONobjectSP imagesObject = JSONobjectSP(new JSONobject());

	JSONstringSP samplersString = JSONstringSP(new JSONstring("samplers"));
	JSONobjectSP samplersObject = JSONobjectSP(new JSONobject());

	JSONstringSP texturesString = JSONstringSP(new JSONstring("textures"));
	JSONobjectSP texturesObject = JSONobjectSP(new JSONobject());

	//
	// TODO Accessors.
	//

	//
	// TODO Animations.
	//

	//
	// TODO Buffer views.
	//

	//
	// TODO Buffers.
	//

	//
	// Images
	//

	glTF->addKeyValue(imagesString, imagesObject);

	//
	// Materials
	//

	JSONstringSP materialsString = JSONstringSP(new JSONstring("materials"));
	JSONobjectSP materialsObject = JSONobjectSP(new JSONobject());

	glTF->addKeyValue(materialsString, materialsObject);

	JSONstringSP materialString;
	JSONobjectSP materialObject;

	JSONstringSP instanceTechniqueString = JSONstringSP(new JSONstring("instanceTechniqueString"));
	JSONobjectSP instanceTechniqueObject;

	JSONstringSP valuesString = JSONstringSP(new JSONstring("values"));
	JSONobjectSP valuesObject;

	//

	JSONstringSP emissionString = JSONstringSP(new JSONstring("emission"));

	JSONstringSP diffuseString = JSONstringSP(new JSONstring("diffuse"));

	JSONstringSP reflectionCoefficientString = JSONstringSP(new JSONstring("reflectionCoefficient"));
	JSONstringSP roughnessString = JSONstringSP(new JSONstring("roughness"));

	JSONstringSP alphaString = JSONstringSP(new JSONstring("alpha"));

	JSONstringSP normalMapString = JSONstringSP(new JSONstring("normalMap"));

	JSONstringSP displacementMapString = JSONstringSP(new JSONstring("displacementMap"));

	JSONstringSP imageString;
	JSONstringSP samplerString;
	JSONstringSP textureString;
	JSONarraySP array;
	JSONnumberSP number;

	//

	JSONstringSP materialName = JSONstringSP(new JSONstring("name"));

	for (int32_t i = 0; i < modelEntity->getModel()->getSurfaceMaterialCount(); i++)
	{
		SurfaceMaterialSP surfaceMaterial = modelEntity->getModel()->getSurfaceMaterialAt(i);

		//

		materialString = JSONstringSP(new JSONstring(surfaceMaterial->getName()));
		materialObject = JSONobjectSP(new JSONobject());

		materialsObject->addKeyValue(materialString, materialObject);

		//
		// Instance Technique
		//

		instanceTechniqueObject = JSONobjectSP(new JSONobject());

		materialObject->addKeyValue(instanceTechniqueString, instanceTechniqueObject);

		//

		valuesObject = JSONobjectSP(new JSONobject());

		instanceTechniqueObject->addKeyValue(valuesString, valuesObject);

		// Emission
		if (surfaceMaterial->getEmissiveTextureName())
		{
			textureString = JSONstringSP(new JSONstring("texture_" + surfaceMaterial->getEmissiveTexture()->getIdentifier()));
			samplerString = JSONstringSP(new JSONstring("sampler_" + surfaceMaterial->getEmissiveTexture()->getIdentifier()));
			imageString = JSONstringSP(new JSONstring("image_" + surfaceMaterial->getEmissiveTexture()->getIdentifier()));

			valuesObject->addKeyValue(emissionString, textureString);

			//

			addTextureSamplerImage(texturesObject, textureString, samplersObject, samplerString, imagesObject, imageString, surfaceMaterial->getEmissiveTexture());
		}
		else
		{
			array = JSONarraySP(new JSONarray());

			for (int32_t k = 0; k < 4; k++)
			{
				array->addValue(JSONnumberSP(new JSONnumber(surfaceMaterial->getEmissive().getRGBA()[k])));
			}

			valuesObject->addKeyValue(emissionString, array);
		}

		// Diffuse
		if (surfaceMaterial->getDiffuseTextureName())
		{
			textureString = JSONstringSP(new JSONstring("texture_" + surfaceMaterial->getDiffuseTexture()->getIdentifier()));
			samplerString = JSONstringSP(new JSONstring("sampler_" + surfaceMaterial->getDiffuseTexture()->getIdentifier()));
			imageString = JSONstringSP(new JSONstring("image_" + surfaceMaterial->getDiffuseTexture()->getIdentifier()));

			valuesObject->addKeyValue(diffuseString, textureString);

			//

			addTextureSamplerImage(texturesObject, textureString, samplersObject, samplerString, imagesObject, imageString, surfaceMaterial->getDiffuseTexture());		}
		else
		{
			array = JSONarraySP(new JSONarray());

			for (int32_t k = 0; k < 4; k++)
			{
				array->addValue(JSONnumberSP(new JSONnumber(surfaceMaterial->getDiffuse().getRGBA()[k])));
			}

			valuesObject->addKeyValue(diffuseString, array);
		}

		// Reflection coefficient
		if (surfaceMaterial->getReflectionCoefficientTextureName())
		{
			textureString = JSONstringSP(new JSONstring("texture_" + surfaceMaterial->getReflectionCoefficientTexture()->getIdentifier()));
			samplerString = JSONstringSP(new JSONstring("sampler_" + surfaceMaterial->getReflectionCoefficientTexture()->getIdentifier()));
			imageString = JSONstringSP(new JSONstring("image_" + surfaceMaterial->getReflectionCoefficientTexture()->getIdentifier()));

			valuesObject->addKeyValue(reflectionCoefficientString, textureString);

			//

			addTextureSamplerImage(texturesObject, textureString, samplersObject, samplerString, imagesObject, imageString, surfaceMaterial->getReflectionCoefficientTexture());
		}
		else
		{
			number = JSONnumberSP(new JSONnumber(surfaceMaterial->getReflectionCoefficient()));

			valuesObject->addKeyValue(reflectionCoefficientString, number);
		}

		// Roughness
		if (surfaceMaterial->getRoughnessTextureName())
		{
			textureString = JSONstringSP(new JSONstring("texture_" + surfaceMaterial->getRoughnessTexture()->getIdentifier()));
			samplerString = JSONstringSP(new JSONstring("sampler_" + surfaceMaterial->getRoughnessTexture()->getIdentifier()));
			imageString = JSONstringSP(new JSONstring("image_" + surfaceMaterial->getRoughnessTexture()->getIdentifier()));

			valuesObject->addKeyValue(roughnessString, textureString);

			//

			addTextureSamplerImage(texturesObject, textureString, samplersObject, samplerString, imagesObject, imageString, surfaceMaterial->getRoughnessTexture());
		}
		else
		{
			number = JSONnumberSP(new JSONnumber(surfaceMaterial->getRoughness()));

			valuesObject->addKeyValue(roughnessString, number);
		}

		// Alpha
		if (surfaceMaterial->getTransparencyTextureName())
		{
			textureString = JSONstringSP(new JSONstring("texture_" + surfaceMaterial->getTransparencyTexture()->getIdentifier()));
			samplerString = JSONstringSP(new JSONstring("sampler_" + surfaceMaterial->getTransparencyTexture()->getIdentifier()));
			imageString = JSONstringSP(new JSONstring("image_" + surfaceMaterial->getTransparencyTexture()->getIdentifier()));

			valuesObject->addKeyValue(alphaString, textureString);

			//

			addTextureSamplerImage(texturesObject, textureString, samplersObject, samplerString, imagesObject, imageString, surfaceMaterial->getTransparencyTexture());
		}
		else
		{
			number = JSONnumberSP(new JSONnumber(surfaceMaterial->getTransparency()));

			valuesObject->addKeyValue(alphaString, number);
		}

		// Normal map
		if (surfaceMaterial->getNormalMapTextureName())
		{
			textureString = JSONstringSP(new JSONstring("texture_" + surfaceMaterial->getNormalMapTexture()->getIdentifier()));
			samplerString = JSONstringSP(new JSONstring("sampler_" + surfaceMaterial->getNormalMapTexture()->getIdentifier()));
			imageString = JSONstringSP(new JSONstring("image_" + surfaceMaterial->getNormalMapTexture()->getIdentifier()));

			valuesObject->addKeyValue(normalMapString, textureString);

			//

			addTextureSamplerImage(texturesObject, textureString, samplersObject, samplerString, imagesObject, imageString, surfaceMaterial->getNormalMapTexture());
		}

		// Displacement map
		if (surfaceMaterial->getDisplacementMapTextureName())
		{
			textureString = JSONstringSP(new JSONstring("texture_" + surfaceMaterial->getDisplacementMapTexture()->getIdentifier()));
			samplerString = JSONstringSP(new JSONstring("sampler_" + surfaceMaterial->getDisplacementMapTexture()->getIdentifier()));
			imageString = JSONstringSP(new JSONstring("image_" + surfaceMaterial->getDisplacementMapTexture()->getIdentifier()));

			valuesObject->addKeyValue(displacementMapString, textureString);

			//

			addTextureSamplerImage(texturesObject, textureString, samplersObject, samplerString, imagesObject, imageString, surfaceMaterial->getDisplacementMapTexture());
		}

		//
		// Name
		//

		materialObject->addKeyValue(materialName, materialString);
	}

	//
	// TODO Meshes.
	//

	//
	// Nodes
	//

	char buffer[1024];

	//

	JSONstringSP nodesString = JSONstringSP(new JSONstring("nodes"));
	JSONobjectSP nodesObject = JSONobjectSP(new JSONobject());

	glTF->addKeyValue(nodesString, nodesObject);

	JSONstringSP nodeString;
	JSONobjectSP nodeObject;

	JSONstringSP childrenString = JSONstringSP(new JSONstring("children"));
	JSONarraySP childrenArray;
	JSONstringSP childNodeString;

	JSONstringSP matrixString = JSONstringSP(new JSONstring("matrix"));
	JSONarraySP matrixArray;
	JSONnumberSP matrixNumber;

	JSONstringSP meshesString = JSONstringSP(new JSONstring("meshes"));
	JSONarraySP meshesArray;
	JSONstringSP meshString;

	JSONstringSP nodeName = JSONstringSP(new JSONstring("name"));

	for (int32_t i = 0; i < modelEntity->getModel()->getNodeCount(); i++)
	{
		NodeSP node = modelEntity->getModel()->getNodeAt(i);

		//

		nodeString = JSONstringSP(new JSONstring(node->getName()));
		nodeObject = JSONobjectSP(new JSONobject());

		nodesObject->addKeyValue(nodeString, nodeObject);

		//
		// Children
		//

		childrenArray = JSONarraySP(new JSONarray());

		nodeObject->addKeyValue(childrenString, childrenArray);

		for (uint32_t k = 0; k < node->getChildCount(); k++)
		{
			NodeSP childNode = node->getChild(k);

			childNodeString = JSONstringSP(new JSONstring(childNode->getName()));

			childrenArray->addValue(childNodeString);
		}

		//
		// Matrix
		//

		matrixArray = JSONarraySP(new JSONarray());

		nodeObject->addKeyValue(matrixString, matrixArray);

		for (int32_t k = 0; k < 16; k++)
		{
			matrixNumber = JSONnumberSP(new JSONnumber(node->getLocalFinalMatrix().getM()[k]));

			matrixArray->addValue(matrixNumber);
		}

		// TODO Add FBX matrices parameters.

		//
		// Meshes
		//

		meshesArray = JSONarraySP(new JSONarray());

		nodeObject->addKeyValue(meshesString, meshesArray);

		for (uint32_t k = 0; k < node->getMesh()->getSubMeshesCount(); k++)
		{
			string currentMeshName = "mesh_" + node->getName() + "_";

			sprintf(buffer, "%03d", k);

			currentMeshName.append(buffer);

			meshString = JSONstringSP(new JSONstring(currentMeshName));

			meshesArray->addValue(meshString);
		}

		//
		// Name
		//

		nodeObject->addKeyValue(nodeName, nodeString);
	}

	//
	// Samplers
	//

	glTF->addKeyValue(samplersString, samplersObject);

	//
	// TODO Scene.
	//

	//
	// TODO Scenes.
	//

	//
	// TODO Skins.
	//

	//
	// Textures
	//

	glTF->addKeyValue(texturesString, texturesObject);

	//
	// Save as JSON text.
	//

	JSONencoder encoder;
	string jsonText;

	encoder.encode(glTF, jsonText);

	printf("\nEncoded Crate Cube:\n%s\n\n", jsonText.c_str());

	return true;
}

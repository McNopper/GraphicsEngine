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

void GlTfEntityFactory::addAccessorsValues(JSONobjectSP& accessorObject, const JSONstringSP& bufferViewValueString, size_t byteOffset, size_t byteStride, GLenum componentType, int32_t count, const string& type) const
{
	JSONstringSP bufferViewString = JSONstringSP(new JSONstring("bufferView"));
	JSONstringSP byteOffsetString = JSONstringSP(new JSONstring("byteOffset"));
	JSONstringSP byteStrideString = JSONstringSP(new JSONstring("byteStride"));
	JSONstringSP componentTypeString = JSONstringSP(new JSONstring("componentType"));
	JSONstringSP countString = JSONstringSP(new JSONstring("count"));
	JSONstringSP typeString = JSONstringSP(new JSONstring("type"));

	JSONnumberSP valueNumber;
	JSONstringSP valueString;

	accessorObject->addKeyValue(bufferViewString, bufferViewValueString);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)byteOffset));
	accessorObject->addKeyValue(byteOffsetString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)byteStride));
	accessorObject->addKeyValue(byteStrideString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)componentType));
	accessorObject->addKeyValue(componentTypeString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber(count));
	accessorObject->addKeyValue(countString, valueNumber);

	valueString = JSONstringSP(new JSONstring(type));
	accessorObject->addKeyValue(typeString, valueString);
}

void GlTfEntityFactory::addBufferViewsValues(JSONobjectSP& bufferViewObject, const JSONstringSP& bufferValueString, size_t byteOffset, size_t byteLength, GLenum target) const
{
	JSONstringSP bufferString = JSONstringSP(new JSONstring("buffer"));
	JSONstringSP byteLengthString = JSONstringSP(new JSONstring("byteLength"));
	JSONstringSP byteOffsetString = JSONstringSP(new JSONstring("byteOffset"));
	JSONstringSP targetString = JSONstringSP(new JSONstring("target"));

	JSONnumberSP valueNumber;

	bufferViewObject->addKeyValue(bufferString, bufferValueString);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)byteOffset));
	bufferViewObject->addKeyValue(byteOffsetString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)byteLength));
	bufferViewObject->addKeyValue(byteLengthString, valueNumber);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)target));
	bufferViewObject->addKeyValue(targetString, valueNumber);
}

void GlTfEntityFactory::addBufferBufferViewsAccessors(JSONobjectSP& buffersObject, const JSONstringSP& bufferString, JSONobjectSP& bufferViewsObject, JSONobjectSP& accessorsObject, const MeshSP& mesh) const
{
	auto walker = buffersObject->getAllKeys().begin();

	while (walker != buffersObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == bufferString->getValue())
		{
			return;
		}

		walker++;
	}

	//

	char buffer[128];

	size_t beforeTotalLength;

	size_t currentLength;

	JSONstringSP bufferViewString;
	JSONobjectSP bufferViewObject;

	JSONstringSP accessorString;
	JSONobjectSP accessorObject;

	GlTfBin bin;

	//

	beforeTotalLength = bin.getLength();
	currentLength = mesh->getNumberVertices() * 4 * sizeof(GLfloat);
	bin.addData((const uint8_t*)mesh->getVertices(), currentLength);

	bufferViewString = JSONstringSP(new JSONstring("bufferView_" + mesh->getName() + "_vertices"));
	bufferViewObject = JSONobjectSP(new JSONobject());
	bufferViewsObject->addKeyValue(bufferViewString, bufferViewObject);

	addBufferViewsValues(bufferViewObject, bufferString, beforeTotalLength, currentLength, GL_ARRAY_BUFFER);

	accessorString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_vertices"));
	accessorObject = JSONobjectSP(new JSONobject());
	accessorsObject->addKeyValue(accessorString, accessorObject);

	addAccessorsValues(accessorObject, bufferViewString, beforeTotalLength, 0, GL_FLOAT, mesh->getNumberVertices(), "VEC4");

	if (mesh->getNormals())
	{
		beforeTotalLength = bin.getLength();
		currentLength = mesh->getNumberVertices() * 3 * sizeof(GLfloat);
		bin.addData((const uint8_t*)mesh->getNormals(), currentLength);

		bufferViewString = JSONstringSP(new JSONstring("bufferView_" + mesh->getName() + "_normals"));
		bufferViewObject = JSONobjectSP(new JSONobject());
		bufferViewsObject->addKeyValue(bufferViewString, bufferViewObject);

		addBufferViewsValues(bufferViewObject, bufferString, beforeTotalLength, currentLength, GL_ARRAY_BUFFER);

		accessorString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_normals"));
		accessorObject = JSONobjectSP(new JSONobject());
		accessorsObject->addKeyValue(accessorString, accessorObject);

		addAccessorsValues(accessorObject, bufferViewString, beforeTotalLength, 0, GL_FLOAT, mesh->getNumberVertices(), "VEC3");
	}

	if (mesh->getBitangents())
	{
		beforeTotalLength = bin.getLength();
		currentLength = mesh->getNumberVertices() * 3 * sizeof(GLfloat);
		bin.addData((const uint8_t*)mesh->getBitangents(), currentLength);

		bufferViewString = JSONstringSP(new JSONstring("bufferView_" + mesh->getName() + "_bitangents"));
		bufferViewObject = JSONobjectSP(new JSONobject());
		bufferViewsObject->addKeyValue(bufferViewString, bufferViewObject);

		addBufferViewsValues(bufferViewObject, bufferString, beforeTotalLength, currentLength, GL_ARRAY_BUFFER);

		accessorString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_bitangents"));
		accessorObject = JSONobjectSP(new JSONobject());
		accessorsObject->addKeyValue(accessorString, accessorObject);

		addAccessorsValues(accessorObject, bufferViewString, beforeTotalLength, 0, GL_FLOAT, mesh->getNumberVertices(), "VEC3");
	}

	if (mesh->getTangents())
	{
		beforeTotalLength = bin.getLength();
		currentLength = mesh->getNumberVertices() * 3 * sizeof(GLfloat);
		bin.addData((const uint8_t*)mesh->getTangents(), currentLength);

		bufferViewString = JSONstringSP(new JSONstring("bufferView_" + mesh->getName() + "_tangents"));
		bufferViewObject = JSONobjectSP(new JSONobject());
		bufferViewsObject->addKeyValue(bufferViewString, bufferViewObject);

		addBufferViewsValues(bufferViewObject, bufferString, beforeTotalLength, currentLength, GL_ARRAY_BUFFER);

		accessorString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_tangents"));
		accessorObject = JSONobjectSP(new JSONobject());
		accessorsObject->addKeyValue(accessorString, accessorObject);

		addAccessorsValues(accessorObject, bufferViewString, beforeTotalLength, 0, GL_FLOAT, mesh->getNumberVertices(), "VEC3");
	}

	if (mesh->getTexCoords())
	{
		beforeTotalLength = bin.getLength();
		currentLength = mesh->getNumberVertices() * 2 * sizeof(GLfloat);
		bin.addData((const uint8_t*)mesh->getTexCoords(), currentLength);

		bufferViewString = JSONstringSP(new JSONstring("bufferView_" + mesh->getName() + "_texcoords"));
		bufferViewObject = JSONobjectSP(new JSONobject());
		bufferViewsObject->addKeyValue(bufferViewString, bufferViewObject);

		addBufferViewsValues(bufferViewObject, bufferString, beforeTotalLength, currentLength, GL_ARRAY_BUFFER);

		accessorString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_texcoords"));
		accessorObject = JSONobjectSP(new JSONobject());
		accessorsObject->addKeyValue(accessorString, accessorObject);

		addAccessorsValues(accessorObject, bufferViewString, beforeTotalLength, 0, GL_FLOAT, mesh->getNumberVertices(), "VEC2");
	}

	beforeTotalLength = bin.getLength();
	currentLength = mesh->getNumberIndices() * sizeof(GLuint);
	bin.addData((const uint8_t*)mesh->getIndices(), currentLength);

	bufferViewString = JSONstringSP(new JSONstring("bufferView_" + mesh->getName() + "_indices"));
	bufferViewObject = JSONobjectSP(new JSONobject());
	bufferViewsObject->addKeyValue(bufferViewString, bufferViewObject);

	addBufferViewsValues(bufferViewObject, bufferString, beforeTotalLength, currentLength, GL_ELEMENT_ARRAY_BUFFER);

	for (uint32_t i = 0; i < mesh->getSubMeshesCount(); i++)
	{
		const SubMeshSP& currentSubMesh = mesh->getSubMeshAt((int32_t)i);

		sprintf(buffer, "%03d", i);

		accessorString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_indices_" + buffer));
		accessorObject = JSONobjectSP(new JSONobject());
		accessorsObject->addKeyValue(accessorString, accessorObject);

		addAccessorsValues(accessorObject, bufferViewString, beforeTotalLength + currentSubMesh->getIndicesOffset(), 0, GL_UNSIGNED_INT, currentSubMesh->getTriangleCount() * 3, "SCALAR");
	}

	//
	// Buffer
	//

	JSONobjectSP bufferObject = JSONobjectSP(new JSONobject());
	buffersObject->addKeyValue(bufferString, bufferObject);

	JSONstringSP uriString = JSONstringSP(new JSONstring("uri"));
	JSONstringSP byteLengthString = JSONstringSP(new JSONstring("byteLength"));
	JSONstringSP typeString = JSONstringSP(new JSONstring("type"));

	JSONstringSP valueString;
	JSONnumberSP valueNumber;

	valueString =  JSONstringSP(new JSONstring(mesh->getName() + ".bin"));
	bufferObject->addKeyValue(uriString, valueString);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)bin.getLength()));
	bufferObject->addKeyValue(byteLengthString, valueNumber);

	valueString =  JSONstringSP(new JSONstring("arraybuffer"));
	bufferObject->addKeyValue(typeString, valueString);

	// TODO Save binary buffer.
}

void GlTfEntityFactory::addMesh(JSONobjectSP& meshesObject, const JSONstringSP& meshString, const MeshSP& mesh, int32_t index) const
{
	auto walker = meshesObject->getAllKeys().begin();

	while (walker != meshesObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == meshString->getValue())
		{
			return;
		}

		walker++;
	}

	const SurfaceMaterialSP& surfaceMaterial = mesh->getSurfaceMaterialAt(index);

	//

	char buffer[128];

	JSONobjectSP meshObject = JSONobjectSP(new JSONobject());

	meshesObject->addKeyValue(meshString, meshObject);

	//

	JSONstringSP nameString = JSONstringSP(new JSONstring("name"));
	JSONstringSP primitivesString = JSONstringSP(new JSONstring("primitives"));

	JSONarraySP valueArray;

	valueArray = JSONarraySP(new JSONarray());
	meshObject->addKeyValue(primitivesString, valueArray);

	meshObject->addKeyValue(nameString, meshString);

	//

	JSONobjectSP primitivesObject = JSONobjectSP(new JSONobject());

	valueArray->addValue(primitivesObject);

	//

	JSONstringSP attributesString = JSONstringSP(new JSONstring("attributes"));
	JSONstringSP indicesString = JSONstringSP(new JSONstring("indices"));
	JSONstringSP materialString = JSONstringSP(new JSONstring("material"));
	JSONstringSP primitiveString = JSONstringSP(new JSONstring("primitive"));

	JSONstringSP valueString;
	JSONnumberSP valueNumber;
	JSONobjectSP valueObject;

	valueObject =  JSONobjectSP(new JSONobject());

	//

	JSONstringSP attributeString;
	JSONstringSP attributeValueString;

	attributeString = JSONstringSP(new JSONstring("POSITION"));
	attributeValueString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_vertices"));
	valueObject->addKeyValue(attributeString, attributeValueString);

	if (mesh->getNormals())
	{
		attributeString = JSONstringSP(new JSONstring("NORMAL"));
		attributeValueString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_normals"));
		valueObject->addKeyValue(attributeString, attributeValueString);
	}

	if (mesh->getBitangents())
	{
		attributeString = JSONstringSP(new JSONstring("BITANGENT"));
		attributeValueString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_bitangents"));
		valueObject->addKeyValue(attributeString, attributeValueString);
	}

	if (mesh->getTangents())
	{
		attributeString = JSONstringSP(new JSONstring("TANGENT"));
		attributeValueString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_tangents"));
		valueObject->addKeyValue(attributeString, attributeValueString);
	}

	if (mesh->getTexCoords())
	{
		attributeString = JSONstringSP(new JSONstring("TEXCOORD"));
		attributeValueString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_texcoords"));
		valueObject->addKeyValue(attributeString, attributeValueString);
	}

	//

	primitivesObject->addKeyValue(attributesString, valueObject);

	sprintf(buffer, "%03d", index);
	valueString = JSONstringSP(new JSONstring("accessor_" + mesh->getName() + "_indices_" + buffer));
	primitivesObject->addKeyValue(indicesString, valueString);

	valueString = JSONstringSP(new JSONstring(surfaceMaterial->getName()));
	primitivesObject->addKeyValue(materialString, valueString);

	valueNumber = JSONnumberSP(new JSONnumber((int32_t)GL_TRIANGLES));
	primitivesObject->addKeyValue(primitiveString, valueNumber);
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

	JSONstringSP uriString = JSONstringSP(new JSONstring("uri"));

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
	imageObject->addKeyValue(uriString, valueString);

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

	JSONstringSP accessorsString = JSONstringSP(new JSONstring("accessors"));
	JSONobjectSP accessorsObject = JSONobjectSP(new JSONobject());

	JSONstringSP bufferViewsString = JSONstringSP(new JSONstring("bufferViews"));
	JSONobjectSP bufferViewsObject = JSONobjectSP(new JSONobject());

	JSONstringSP buffersString = JSONstringSP(new JSONstring("buffers"));
	JSONobjectSP buffersObject = JSONobjectSP(new JSONobject());

	JSONstringSP imagesString = JSONstringSP(new JSONstring("images"));
	JSONobjectSP imagesObject = JSONobjectSP(new JSONobject());

	JSONstringSP meshesString = JSONstringSP(new JSONstring("meshes"));
	JSONobjectSP meshesObject = JSONobjectSP(new JSONobject());

	JSONstringSP samplersString = JSONstringSP(new JSONstring("samplers"));
	JSONobjectSP samplersObject = JSONobjectSP(new JSONobject());

	JSONstringSP texturesString = JSONstringSP(new JSONstring("textures"));
	JSONobjectSP texturesObject = JSONobjectSP(new JSONobject());

	//
	// Accessors
	//

	glTF->addKeyValue(accessorsString, accessorsObject);

	//
	// TODO Animations.
	//

	//
	// FIXME Asset,
	//

	//
	// Buffer views
	//

	glTF->addKeyValue(bufferViewsString, bufferViewsObject);

	//
	// Buffers
	//

	glTF->addKeyValue(buffersString, buffersObject);

	//
	// FIXME Cameras.
	//

	//
	// Images
	//

	glTF->addKeyValue(imagesString, imagesObject);

	//
	// FIXME Lights.
	//

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

		// FIXME Technique.

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
	// Meshes
	//

	glTF->addKeyValue(meshesString, meshesObject);

	//
	// Nodes
	//

	char buffer[128];

	//

	JSONstringSP nodesString = JSONstringSP(new JSONstring("nodes"));
	JSONobjectSP nodesObject = JSONobjectSP(new JSONobject());

	glTF->addKeyValue(nodesString, nodesObject);

	JSONstringSP nodeString;
	JSONobjectSP nodeObject;

	JSONstringSP childrenString = JSONstringSP(new JSONstring("children"));
	JSONarraySP childrenArray;
	JSONstringSP childNodeString;

	// FBX

	JSONstringSP LclTranslationString = JSONstringSP(new JSONstring("LclTranslation"));
	JSONstringSP RotationOffsetString = JSONstringSP(new JSONstring("RotationOffset"));
	JSONstringSP RotationPivotString = JSONstringSP(new JSONstring("RotationPivot"));
	JSONstringSP PreRotationString = JSONstringSP(new JSONstring("PreRotation"));
	JSONstringSP LclRotationString = JSONstringSP(new JSONstring("LclRotation"));
	JSONstringSP PostRotationString = JSONstringSP(new JSONstring("PostRotation"));
	JSONstringSP ScalingOffsetString = JSONstringSP(new JSONstring("ScalingOffset"));
	JSONstringSP ScalingPivotString = JSONstringSP(new JSONstring("ScalingPivot"));
	JSONstringSP LclScalingString = JSONstringSP(new JSONstring("LclScaling"));
	JSONstringSP GeometricTranslationString = JSONstringSP(new JSONstring("GeometricTranslation"));
	JSONstringSP GeometricRotationString = JSONstringSP(new JSONstring("GeometricRotation"));
	JSONstringSP GeometricScalingString = JSONstringSP(new JSONstring("GeometricScaling"));

	JSONstringSP nodeMeshesString = JSONstringSP(new JSONstring("meshes"));
	JSONarraySP nodeMeshesArray;
	JSONstringSP nodeBufferString;
	JSONstringSP nodeMeshString;

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
		// FBX parameters
		//

		// TODO Add parameters.

		//
		// Meshes
		//

		nodeMeshesArray = JSONarraySP(new JSONarray());

		nodeObject->addKeyValue(nodeMeshesString, nodeMeshesArray);

		if (node->getMesh())
		{
			nodeBufferString = JSONstringSP(new JSONstring("buffer_" + node->getMesh()->getName()));

			addBufferBufferViewsAccessors(buffersObject, nodeBufferString, bufferViewsObject, accessorsObject, node->getMesh());

			for (uint32_t k = 0; k < node->getMesh()->getSubMeshesCount(); k++)
			{
				string currentMeshName = "mesh_" + node->getMesh()->getName() + "_";

				sprintf(buffer, "%03d", k);

				currentMeshName.append(buffer);

				nodeMeshString = JSONstringSP(new JSONstring(currentMeshName));

				nodeMeshesArray->addValue(nodeMeshString);

				//

				addMesh(meshesObject, nodeMeshString, node->getMesh(), (int32_t)k);
			}
		}

		//
		// Name
		//

		nodeObject->addKeyValue(nodeName, nodeString);
	}

	//
	// FIXME Programs.
	//

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
	// FIXME Shaders.
	//

	//
	// TODO Skins.
	//

	//
	// FIXME Techniques.
	//

	//
	// Textures
	//

	glTF->addKeyValue(texturesString, texturesObject);

	//
	// TODO Save as JSON text.
	//

	JSONencoder encoder;
	string jsonText;

	encoder.encode(glTF, jsonText);

	printf("\nEncoded Crate Cube:\n%s\n\n", jsonText.c_str());

	return true;
}

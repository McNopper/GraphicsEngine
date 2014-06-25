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

void GlTfEntityFactory::addFBXValues(JSONobjectSP& nodeObject, const NodeSP& node) const
{
	JSONstringSP PostTranslationString = JSONstringSP(new JSONstring("postTranslation"));
	JSONstringSP PostRotationString = JSONstringSP(new JSONstring("postRotation"));
	JSONstringSP PostScalingString = JSONstringSP(new JSONstring("postScaling"));

	JSONstringSP GeometricTranslationString = JSONstringSP(new JSONstring("geometricTransform"));

	JSONarraySP valueArray;
	JSONobjectSP valueObject;

	//

	valueArray = JSONarraySP(new JSONarray());
	for (int32_t i = 0; i < 16; i++)
	{
		valueArray->addValue(JSONnumberSP(new JSONnumber(node->getPostTranslationMatrix().getM()[i])));
	}
	nodeObject->addKeyValue(PostTranslationString, valueArray);

	valueArray = JSONarraySP(new JSONarray());
	for (int32_t i = 0; i < 16; i++)
	{
		valueArray->addValue(JSONnumberSP(new JSONnumber(node->getPostRotationMatrix().getM()[i])));
	}
	nodeObject->addKeyValue(PostRotationString, valueArray);

	valueArray = JSONarraySP(new JSONarray());
	for (int32_t i = 0; i < 16; i++)
	{
		valueArray->addValue(JSONnumberSP(new JSONnumber(node->getPostScalingMatrix().getM()[i])));
	}
	nodeObject->addKeyValue(PostScalingString, valueArray);

	valueArray = JSONarraySP(new JSONarray());
	for (int32_t i = 0; i < 16; i++)
	{
		valueArray->addValue(JSONnumberSP(new JSONnumber(node->getGeometricTransformMatrix().getM()[i])));
	}
	nodeObject->addKeyValue(GeometricTranslationString, valueArray);

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

	// TODO Save binary buffer to file.
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

	// TODO Save image to file.
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

void GlTfEntityFactory::addShader(JSONobjectSP& shadersObject, const JSONstringSP& shaderString, const ProgramSeparableSP programSeparable) const
{
	if (programSeparable.get() == nullptr)
	{
		return;
	}

	auto walker = shadersObject->getAllKeys().begin();

	while (walker != shadersObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == shaderString->getValue())
		{
			return;
		}

		walker++;
	}

	JSONobjectSP shaderObject = JSONobjectSP(new JSONobject());

	shadersObject->addKeyValue(shaderString, shaderObject);

	//

	JSONstringSP uriString = JSONstringSP(new JSONstring("uri"));
	JSONstringSP typeString = JSONstringSP(new JSONstring("type"));

	shaderObject->addKeyValue(uriString, JSONstringSP(new JSONstring(programSeparable->getFilename())));

	shaderObject->addKeyValue(typeString, JSONnumberSP(new JSONnumber((int32_t)programSeparable->getShaderType())));
}

void GlTfEntityFactory::addProgramShader(JSONobjectSP& programsObject, JSONobjectSP& shadersObject, const JSONstringSP& programString, const ProgramPipelineSP programPipeline) const
{
	if (programPipeline.get() == nullptr)
	{
		return;
	}

	auto walker = programsObject->getAllKeys().begin();

	while (walker != programsObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == programString->getValue())
		{
			return;
		}

		walker++;
	}

	JSONobjectSP programObject = JSONobjectSP(new JSONobject());

	programsObject->addKeyValue(programString, programObject);

	JSONstringSP valueString;

	//

	JSONstringSP vertexShaderString = JSONstringSP(new JSONstring("vertexShader"));

	JSONstringSP tessControlShaderString = JSONstringSP(new JSONstring("tessControlShader"));
	JSONstringSP tessEvaluationShaderString = JSONstringSP(new JSONstring("tessEvaluationShader"));

	JSONstringSP geometryShaderString = JSONstringSP(new JSONstring("geometryShader"));

	JSONstringSP fragmentShaderString = JSONstringSP(new JSONstring("fragmentShader"));

	if (programPipeline->hasVertexProgramSeparable())
	{
		valueString = JSONstringSP(new JSONstring(vertexShaderString->getValue() + "_" + programPipeline->getName()));

		programObject->addKeyValue(vertexShaderString, valueString);

		addShader(shadersObject, valueString, programPipeline->getVertexProgramSeparable());
	}

	if (programPipeline->hasControlProgramSeparable())
	{
		valueString = JSONstringSP(new JSONstring(tessControlShaderString->getValue() + "_" + programPipeline->getName()));

		programObject->addKeyValue(tessControlShaderString, valueString);

		addShader(shadersObject, valueString, programPipeline->getControlProgramSeparable());
	}
	if (programPipeline->hasEvaluationProgramSeparable())
	{
		valueString = JSONstringSP(new JSONstring(tessEvaluationShaderString->getValue() + "_" + programPipeline->getName()));

		programObject->addKeyValue(tessEvaluationShaderString, valueString);

		addShader(shadersObject, valueString, programPipeline->getEvaluationProgramSeparable());
	}

	if (programPipeline->hasGeometryProgramSeparable())
	{
		valueString = JSONstringSP(new JSONstring(geometryShaderString->getValue() + "_" + programPipeline->getName()));

		programObject->addKeyValue(geometryShaderString, valueString);

		addShader(shadersObject, valueString, programPipeline->getGeometryProgramSeparable());
	}

	if (programPipeline->hasFragmentProgramSeparable())
	{
		valueString = JSONstringSP(new JSONstring(fragmentShaderString->getValue() + "_" + programPipeline->getName()));

		programObject->addKeyValue(fragmentShaderString, valueString);

		addShader(shadersObject, valueString, programPipeline->getFragmentProgramSeparable());
	}
}

void GlTfEntityFactory::addTechniqueProgramShader(JSONobjectSP& techniquesObject, JSONobjectSP& programsObject, JSONobjectSP& shadersObject, const JSONstringSP& techniqueString, const ProgramPipelineSP programPipeline) const
{
	if (programPipeline.get() == nullptr)
	{
		return;
	}

	auto walker = techniquesObject->getAllKeys().begin();

	while (walker != techniquesObject->getAllKeys().end())
	{
		if ((*walker)->getValue() == techniqueString->getValue())
		{
			return;
		}

		walker++;
	}

	JSONobjectSP techniqueObject = JSONobjectSP(new JSONobject());

	techniquesObject->addKeyValue(techniqueString, techniqueObject);

	//

	JSONstringSP passString = JSONstringSP(new JSONstring("pass"));

	JSONstringSP valueString = JSONstringSP(new JSONstring("defaultPass"));
	techniqueObject->addKeyValue(passString, valueString);

	//

	JSONstringSP passesString = JSONstringSP(new JSONstring("passes"));

	JSONobjectSP valueObject = JSONobjectSP(new JSONobject());
	techniqueObject->addKeyValue(passesString, valueObject);

	JSONobjectSP passObject = JSONobjectSP(new JSONobject());
	valueObject->addKeyValue(valueString, passObject);

	//

	JSONstringSP instanceProgramString = JSONstringSP(new JSONstring("instanceProgram"));
	JSONobjectSP instanceProgramObject = JSONobjectSP(new JSONobject());

	passObject->addKeyValue(instanceProgramString, instanceProgramObject);

	//

	JSONstringSP programString = JSONstringSP(new JSONstring("program"));

	valueString = JSONstringSP(new JSONstring("program_" + programPipeline->getName()));

	instanceProgramObject->addKeyValue(programString, valueString);

	addProgramShader(programsObject, shadersObject, valueString, programPipeline);
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

	JSONarraySP transformArray;
	JSONnumberSP valueNumber;
	JSONstringSP valueString;

	//

	JSONstringSP allExtensionsString = JSONstringSP(new JSONstring("allExtensions"));
	JSONarraySP allExtensionsArray = JSONarraySP(new JSONarray());

	JSONstringSP accessorsString = JSONstringSP(new JSONstring("accessors"));
	JSONobjectSP accessorsObject = JSONobjectSP(new JSONobject());

	JSONstringSP animationsString = JSONstringSP(new JSONstring("animations"));
	JSONobjectSP animationsObject = JSONobjectSP(new JSONobject());

	JSONstringSP assetString = JSONstringSP(new JSONstring("asset"));
	JSONobjectSP assetObject = JSONobjectSP(new JSONobject());

	JSONstringSP bufferViewsString = JSONstringSP(new JSONstring("bufferViews"));
	JSONobjectSP bufferViewsObject = JSONobjectSP(new JSONobject());

	JSONstringSP buffersString = JSONstringSP(new JSONstring("buffers"));
	JSONobjectSP buffersObject = JSONobjectSP(new JSONobject());

	JSONstringSP camerasString = JSONstringSP(new JSONstring("cameras"));
	JSONobjectSP camerasObject = JSONobjectSP(new JSONobject());

	JSONstringSP imagesString = JSONstringSP(new JSONstring("images"));
	JSONobjectSP imagesObject = JSONobjectSP(new JSONobject());

	JSONstringSP lightsString = JSONstringSP(new JSONstring("lights"));
	JSONobjectSP lightsObject = JSONobjectSP(new JSONobject());

	JSONstringSP materialsString = JSONstringSP(new JSONstring("materials"));
	JSONobjectSP materialsObject = JSONobjectSP(new JSONobject());

	JSONstringSP meshesString = JSONstringSP(new JSONstring("meshes"));
	JSONobjectSP meshesObject = JSONobjectSP(new JSONobject());

	JSONstringSP programsString = JSONstringSP(new JSONstring("programs"));
	JSONobjectSP programsObject = JSONobjectSP(new JSONobject());

	JSONstringSP samplersString = JSONstringSP(new JSONstring("samplers"));
	JSONobjectSP samplersObject = JSONobjectSP(new JSONobject());

	JSONstringSP sceneString = JSONstringSP(new JSONstring("scene"));

	JSONstringSP scenesString = JSONstringSP(new JSONstring("scenes"));
	JSONobjectSP scenesObject = JSONobjectSP(new JSONobject());
	JSONarraySP nodesArray = JSONarraySP(new JSONarray());

	JSONstringSP shadersString = JSONstringSP(new JSONstring("shaders"));
	JSONobjectSP shadersObject = JSONobjectSP(new JSONobject());

	JSONstringSP skinsString = JSONstringSP(new JSONstring("skins"));
	JSONobjectSP skinsObject = JSONobjectSP(new JSONobject());

	JSONstringSP texturesString = JSONstringSP(new JSONstring("textures"));
	JSONobjectSP texturesObject = JSONobjectSP(new JSONobject());

	JSONstringSP techniquesString = JSONstringSP(new JSONstring("techniques"));
	JSONobjectSP techniquesObject = JSONobjectSP(new JSONobject());

	//
	// All extensions
	//

	glTF->addKeyValue(allExtensionsString, allExtensionsArray);

	//
	// Accessors
	//

	glTF->addKeyValue(accessorsString, accessorsObject);

	//
	// Animations
	//

	glTF->addKeyValue(animationsString, animationsObject);

	// TODO Add animation elements.

	//
	// Asset
	//

	glTF->addKeyValue(assetString, assetObject);

	JSONstringSP generatorString = JSONstringSP(new JSONstring("generator"));
	valueString = JSONstringSP(new JSONstring("Norbert Nopper's Graphics Engine"));
	assetObject->addKeyValue(generatorString, valueString);

	JSONstringSP profileString = JSONstringSP(new JSONstring("profile"));
	valueString = JSONstringSP(new JSONstring("OpenGL 4.4 Core Profile"));
	assetObject->addKeyValue(profileString, valueString);

	JSONstringSP versionString = JSONstringSP(new JSONstring("version"));
	valueString = JSONstringSP(new JSONstring("0.6"));
	assetObject->addKeyValue(versionString, valueString);

	//
	// Buffer views
	//

	glTF->addKeyValue(bufferViewsString, bufferViewsObject);

	//
	// Buffers
	//

	glTF->addKeyValue(buffersString, buffersObject);

	//
	// Cameras
	//

	glTF->addKeyValue(camerasString, camerasObject);

	//
	// Images
	//

	glTF->addKeyValue(imagesString, imagesObject);

	//
	// Lights
	//

	glTF->addKeyValue(lightsString, lightsObject);

	//
	// Materials
	//

	glTF->addKeyValue(materialsString, materialsObject);

	JSONstringSP materialString;
	JSONobjectSP materialObject;

	JSONstringSP instanceTechniqueString = JSONstringSP(new JSONstring("instanceTechniqueString"));
	JSONobjectSP instanceTechniqueObject;

	JSONstringSP techniqueString = JSONstringSP(new JSONstring("technique"));

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
		// Technique
		//

		if (surfaceMaterial->getProgramPipeline().get() != nullptr)
		{
			valueString = JSONstringSP(new JSONstring("technique_" + surfaceMaterial->getProgramPipeline()->getName()));

			instanceTechniqueObject->addKeyValue(techniqueString, valueString);

			addTechniqueProgramShader(techniquesObject, programsObject, shadersObject, valueString, surfaceMaterial->getProgramPipeline());
		}

		//
		// Values
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
			transformArray = JSONarraySP(new JSONarray());

			for (int32_t k = 0; k < 4; k++)
			{
				transformArray->addValue(JSONnumberSP(new JSONnumber(surfaceMaterial->getEmissive().getRGBA()[k])));
			}

			valuesObject->addKeyValue(emissionString, transformArray);
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
			transformArray = JSONarraySP(new JSONarray());

			for (int32_t k = 0; k < 4; k++)
			{
				transformArray->addValue(JSONnumberSP(new JSONnumber(surfaceMaterial->getDiffuse().getRGBA()[k])));
			}

			valuesObject->addKeyValue(diffuseString, transformArray);
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
			valueNumber = JSONnumberSP(new JSONnumber(surfaceMaterial->getReflectionCoefficient()));

			valuesObject->addKeyValue(reflectionCoefficientString, valueNumber);
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
			valueNumber = JSONnumberSP(new JSONnumber(surfaceMaterial->getRoughness()));

			valuesObject->addKeyValue(roughnessString, valueNumber);
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
			valueNumber = JSONnumberSP(new JSONnumber(surfaceMaterial->getTransparency()));

			valuesObject->addKeyValue(alphaString, valueNumber);
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

	JSONstringSP jointString = JSONstringSP(new JSONstring("joint"));
	JSONstringSP jointValueString;

	JSONstringSP LclTranslationString = JSONstringSP(new JSONstring("translation"));
	JSONstringSP LclRotationString = JSONstringSP(new JSONstring("rotation"));
	JSONstringSP LclScalingString = JSONstringSP(new JSONstring("scale"));

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
		// Instance skin
		//

		// TODO Add instance skin.

		//
		// Joint
		//

		if (node->getJointIndex() >= 0)
		{
			string currentJointName = "joint_";

			sprintf(buffer, "%03d", node->getJointIndex());

			currentJointName.append(buffer);

			jointValueString  = JSONstringSP(new JSONstring(currentJointName));

			nodeObject->addKeyValue(jointString, jointValueString);
		}

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
		// Transform
		//

		transformArray = JSONarraySP(new JSONarray());
		for (int32_t i = 0; i < 3; i++)
		{
			transformArray->addValue(JSONnumberSP(new JSONnumber(node->getLclTranslation()[i])));
		}
		nodeObject->addKeyValue(LclTranslationString, transformArray);

		transformArray = JSONarraySP(new JSONarray());
		for (int32_t i = 0; i < 3; i++)
		{
			transformArray->addValue(JSONnumberSP(new JSONnumber(node->getLclRotation()[i])));
		}
		nodeObject->addKeyValue(LclRotationString, transformArray);

		transformArray = JSONarraySP(new JSONarray());
		for (int32_t i = 0; i < 3; i++)
		{
			transformArray->addValue(JSONnumberSP(new JSONnumber(node->getLclScaling()[i])));
		}
		nodeObject->addKeyValue(LclScalingString, transformArray);

		//
		// FBX parameters
		//

		addFBXValues(nodeObject, node);

		//
		// Name
		//

		nodeObject->addKeyValue(nodeName, nodeString);
	}

	//
	// Programs
	//

	glTF->addKeyValue(programsString, programsObject);

	//
	// Samplers
	//

	glTF->addKeyValue(samplersString, samplersObject);

	//
	// Scene
	//

	valueString = JSONstringSP(new JSONstring("defaultScene"));

	glTF->addKeyValue(sceneString, valueString);

	//
	// Scenes
	//

	glTF->addKeyValue(scenesString, scenesObject);

	JSONobjectSP sceneObject = JSONobjectSP(new JSONobject());

	scenesObject->addKeyValue(valueString, sceneObject);

	// Root Nodes

	JSONstringSP rootNodeString = JSONstringSP(new JSONstring(modelEntity->getModel()->getRootNode()->getName()));
	nodesArray->addValue(rootNodeString);

	sceneObject->addKeyValue(nodesString, nodesArray);

	//
	// Shaders
	//

	glTF->addKeyValue(shadersString, shadersObject);

	//
	// Skins
	//

	glTF->addKeyValue(skinsString, skinsObject);

	// TODO Add skin elements.

	//
	// Techniques
	//

	glTF->addKeyValue(techniquesString, techniquesObject);

	//
	// Textures
	//

	glTF->addKeyValue(texturesString, texturesObject);

	//
	// TODO Save JSON text to file.
	//

	JSONencoder encoder;
	string jsonText;

	encoder.encode(glTF, jsonText);

	printf("\nEncoded Crate Cube:\n%s\n\n", jsonText.c_str());

	return true;
}

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

	// TODO Add other elements.

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

		// TODO Add values.

		//
		// Name
		//

		materialObject->addKeyValue(materialName, materialString);
	}

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

	JSONstringSP extraName = JSONstringSP(new JSONstring("extra"));
	JSONobjectSP extraObject;

	for (int32_t i = 0; i < modelEntity->getModel()->getNodeCount(); i++)
	{
		NodeSP node = modelEntity->getModel()->getNodeAt(i);

		extraObject = JSONobjectSP(new JSONobject());

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

		//
		// Meshes
		//

		meshesArray = JSONarraySP(new JSONarray());

		nodeObject->addKeyValue(meshesString, meshesArray);

		for (uint32_t k = 0; k < node->getMesh()->getSubMeshesCount(); k++)
		{
			string currentMeshName = node->getMesh()->getName();

			sprintf(buffer, "%03d", k);

			currentMeshName.append("_");
			currentMeshName.append(buffer);

			meshString = JSONstringSP(new JSONstring(currentMeshName));

			meshesArray->addValue(meshString);
		}

		//
		// Name
		//

		nodeObject->addKeyValue(nodeName, nodeString);

		//
		// Extra
		//

		nodeObject->addKeyValue(extraName, extraObject);
	}

	// TODO Add other elements.

	//
	// Save as JSON text.
	//

	JSONencoder encoder;
	string jsonText;

	encoder.encode(glTF, jsonText);

	printf("Encoded:\n%s\n", jsonText.c_str());

	return true;
}

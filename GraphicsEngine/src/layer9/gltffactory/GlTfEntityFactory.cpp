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
	// Nodes
	//

	JSONstringSP nodesString = JSONstringSP(new JSONstring("nodes"));
	JSONobjectSP nodesObject = JSONobjectSP(new JSONobject());

	glTF->addKeyValue(nodesString, nodesObject);

	JSONstringSP nodeString;
	JSONobjectSP nodeObject;

	JSONstringSP nodeName = JSONstringSP(new JSONstring("name"));

	JSONstringSP childrenString = JSONstringSP(new JSONstring("children"));
	JSONarraySP childrenArray;
	JSONstringSP childNodeString;

	for (int32_t i = 0; i < modelEntity->getModel()->getNodeCount(); i++)
	{
		NodeSP node = modelEntity->getModel()->getNodeAt(i);

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

		// TODO Add matrix.

		//
		// Meshes
		//

		// TODO Add meshes.

		//
		// Name
		//

		nodeObject->addKeyValue(nodeName, nodeString);
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

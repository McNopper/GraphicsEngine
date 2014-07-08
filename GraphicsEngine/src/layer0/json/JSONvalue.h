/*
 * JSONvalue.h
 *
 *  Created on: Jun 16, 2014
 *      Author: nopper
 */

#ifndef JSONVALUE_H_
#define JSONVALUE_H_

#include "../../UsedLibs.h"

class JSONvalue
{

protected:

	bool jsonObject;
	bool jsonArray;
	bool jsonNumber;
	bool jsonString;
	bool jsonTrue;
	bool jsonFalse;
	bool jsonNull;

protected:

	JSONvalue();
	virtual ~JSONvalue();

public:

	bool isJsonArray() const;
	bool isJsonObject() const;
	bool isJsonNumber() const;
	bool isJsonString() const;
	bool isJsonTrue() const;
	bool isJsonFalse() const;
	bool isJsonNull() const;

};

typedef std::shared_ptr<JSONvalue> JSONvalueSP;

#endif /* JSONVALUE_H_ */

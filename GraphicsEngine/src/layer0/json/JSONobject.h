/*
 * JSONobject.h
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#ifndef JSONOBJECT_H_
#define JSONOBJECT_H_

#include "JSONstring.h"
#include "JSONvalue.h"

class JSONobject : public JSONvalue
{

private:

	std::map<JSONstringSP, JSONvalueSP> allKeyValues;

public:

	JSONobject();

	virtual ~JSONobject();

	void addKeyValue(const JSONstringSP& key, const JSONvalueSP& value);

	bool hasKey(const JSONstringSP& key) const;

	JSONvalueSP getValue(const JSONstringSP& key) const;

	const std::map<JSONstringSP, JSONvalueSP>& getAllKeyValues() const;

	size_t size() const;

};

typedef std::shared_ptr<JSONobject> JSONobjectSP;

#endif /* JSONOBJECT_H_ */

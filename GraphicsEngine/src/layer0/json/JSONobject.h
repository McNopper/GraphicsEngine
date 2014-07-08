/*
 * JSONobject.h
 *
 *  Created on: Jun 16, 2014
 *      Author: nopper
 */

#ifndef JSONOBJECT_H_
#define JSONOBJECT_H_

#include "JSONstring.h"
#include "JSONvalue.h"

class CompareJSONstringSP
{
	public:
		bool operator()(const JSONstringSP& first, const JSONstringSP& second) const { return first->getValue() < second->getValue(); }
};

class JSONobject : public JSONvalue
{

private:

	std::map<JSONstringSP, JSONvalueSP, CompareJSONstringSP> allKeyValues;

	std::vector<JSONstringSP> allKeys;

public:

	JSONobject();

	virtual ~JSONobject();

	void addKeyValue(const JSONstringSP& key, const JSONvalueSP& value);

	bool hasKey(const JSONstringSP& key) const;

	JSONvalueSP getValue(const JSONstringSP& key) const;

	const std::map<JSONstringSP, JSONvalueSP, CompareJSONstringSP>& getAllKeyValues() const;

	const std::vector<JSONstringSP>& getAllKeys() const;

	size_t size() const;

};

typedef std::shared_ptr<JSONobject> JSONobjectSP;

#endif /* JSONOBJECT_H_ */

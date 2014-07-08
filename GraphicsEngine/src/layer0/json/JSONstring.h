/*
 * JSONstring.h
 *
 *  Created on: Jun 16, 2014
 *      Author: nopper
 */

#ifndef JSONSTRING_H_
#define JSONSTRING_H_

#include "JSONvalue.h"

class JSONstring : public JSONvalue
{

private:

	std::string value;

public:

	JSONstring();
	JSONstring(const std::string& value);
	virtual ~JSONstring();

	const std::string& getValue() const;

	void setValue(const std::string& value);

};

typedef std::shared_ptr<JSONstring> JSONstringSP;

#endif /* JSONSTRING_H_ */

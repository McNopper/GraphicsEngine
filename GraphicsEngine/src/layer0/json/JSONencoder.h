/*
 * JSONencoder.h
 *
 *  Created on: Jun 16, 2014
 *      Author: nopper
 */

#ifndef JSONENCODER_H_
#define JSONENCODER_H_

// see http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf

#include "JSONvalue.h"
#include "JSONobject.h"
#include "JSONarray.h"
#include "JSONnumber.h"
#include "JSONstring.h"
#include "JSONtrue.h"
#include "JSONfalse.h"
#include "JSONnull.h"

class JSONencoder
{

private:

	std::string jsonText;

	std::int32_t spaces;

	bool doLineFeed(std::int32_t tabs);

	bool encodeObject(const JSONobjectSP jsonObject);
	bool encodeArray(const JSONarraySP jsonArray);
	bool encodeNumber(const JSONnumberSP jsonNumber);
	bool encodeString(const JSONstringSP jsonString);
	bool encodeTrue(const JSONtrueSP jsonTrue);
	bool encodeFalse(const JSONfalseSP jsonFalse);
	bool encodeNull(const JSONnullSP jsonNull);

	//

	bool encodeValue(const JSONvalueSP jsonValue);

public:

	JSONencoder();
	~JSONencoder();

	bool encode(const JSONvalueSP jsonValue, std::string& jsonText);

};

#endif /* JSONENCODER_H_ */

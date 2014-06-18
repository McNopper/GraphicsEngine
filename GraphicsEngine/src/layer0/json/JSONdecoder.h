/*
 * JSONdecoder.h
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#ifndef JSONDECODER_H_
#define JSONDECODER_H_

// see http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf

#include "JSONvalue.h"
#include "JSONobject.h"
#include "JSONarray.h"
#include "JSONnumber.h"
#include "JSONstring.h"
#include "JSONtrue.h"
#include "JSONfalse.h"
#include "JSONnull.h"

class JSONdecoder
{

private:

	std::string jsonText;

	//

	bool match(const std::string token, size_t& index);

	//

	bool decodeWhitespace(size_t& index);

	//

	bool decodeLeftSquareBracket(size_t& index);
	bool decodeLeftCurlyBracket(size_t& index);
	bool decodeRightSquareBracket(size_t& index);
	bool decodeRightCurlyBracket(size_t& index);
	bool decodeColon(size_t& index);
	bool decodeComma(size_t& index);

	//

	bool decodePlus(size_t& index, std::string& characters);
	bool decodeMinus(size_t& index, std::string& characters);
	bool decodePoint(size_t& index, std::string& characters);

	bool decodeHexadecimalDigit(size_t& index, std::string& characters, std::int32_t& value);

	bool decodeDigit_0(size_t& index, std::string& characters, std::int32_t& value);
	bool decodeDigit_1_9(size_t& index, std::string& characters, std::int32_t& value);
	bool decodeDigit(size_t& index, std::string& characters, std::int32_t& value);

	bool decodeExponent(size_t& index, std::string& characters);

	bool decodeQuotationMark(size_t& index, std::string& characters);
	bool decodeReverseSolidus(size_t& index, std::string& characters);
	bool decodeSolidus(size_t& index, std::string& characters);
	bool decodeBackspace(size_t& index, std::string& characters);
	bool decodeFormFeed(size_t& index, std::string& characters);
	bool decodeLineFeed(size_t& index, std::string& characters);
	bool decodeCarriageReturn(size_t& index, std::string& characters);
	bool decodeCharacterTabulation(size_t& index, std::string& characters);
	bool decodeHexadecimalNumber(size_t& index, std::string& characters);

	//

	bool decodeObject(size_t& index, JSONobjectSP& jsonObject);
	bool decodeArray(size_t& index, JSONarraySP& jsonArray);
	bool decodeNumber(size_t& index, JSONnumberSP& jsonNumber);
	bool decodeString(size_t& index, JSONstringSP& jsonString);
	bool decodeTrue(size_t& index, JSONtrueSP& jsonTrue);
	bool decodeFalse(size_t& index, JSONfalseSP& jsonFalse);
	bool decodeNull(size_t& index, JSONnullSP& jsonNull);

	//

	bool decodeValue(size_t& index, JSONvalueSP& jsonValue);

public:

	JSONdecoder();
	~JSONdecoder();

	bool decode(const std::string& jsonText, JSONvalueSP& jsonValue);

};

#endif /* JSONDECODER_H_ */

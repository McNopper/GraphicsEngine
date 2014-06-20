/*
 * JSONdecoder.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#include "JSONtokens.h"

#include "JSONdecoder.h"

using namespace std;

JSONdecoder::JSONdecoder() : jsonText("")
{
}

JSONdecoder::~JSONdecoder()
{
}

//

bool JSONdecoder::match(const string token, size_t& index)
{
	size_t length = token.length();

	if (jsonText.length() < index + length)
	{
		return false;
	}

	if (jsonText.substr(index, length).compare(token) == 0)
	{
		index += length;

		return true;
	}

	return false;
}

//

bool JSONdecoder::decodeWhitespace(size_t& index)
{
	return match(JSON_Encode_character_tabulation, index) || match(JSON_Encode_line_feed, index) ||match(JSON_Encode_carriage_return, index) || match(JSON_space, index);
}

//

bool JSONdecoder::decodeLeftSquareBracket(size_t& index)
{
	return match(JSON_left_square_bracket, index);
}

bool JSONdecoder::decodeLeftCurlyBracket(size_t& index)
{
	return match(JSON_left_curly_bracket, index);
}

bool JSONdecoder::decodeRightSquareBracket(size_t& index)
{
	return match(JSON_right_square_bracket, index);
}

bool JSONdecoder::decodeRightCurlyBracket(size_t& index)
{
	return match(JSON_right_curly_bracket, index);
}

bool JSONdecoder::decodeColon(size_t& index)
{
	return match(JSON_colon, index);
}

bool JSONdecoder::decodeComma(size_t& index)
{
	return match(JSON_comma, index);
}

//

bool JSONdecoder::decodePlus(size_t& index, string& characters)
{
	if (match(JSON_plus, index))
	{
		characters += JSON_plus;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeMinus(size_t& index, string& characters)
{
	if (match(JSON_minus, index))
	{
		characters += JSON_minus;

		return true;
	}

	return false;
}

bool JSONdecoder::decodePoint(size_t& index, string& characters)
{
	if (match(JSON_point, index))
	{
		characters += JSON_point;

		return true;
	}

	return false;
}

//

bool JSONdecoder::decodeHexadecimalDigit(size_t& index, string& characters, int32_t& value)
{
	if (match(JSON_A, index) || match(JSON_B, index) || match(JSON_C, index) || match(JSON_D, index) || match(JSON_E, index) || match(JSON_F, index))
	{
		characters += jsonText.substr(index - 1, 1);

		value = static_cast<int32_t>(jsonText.substr(index - 1, 1)[0] - JSON_A[0]);

		return true;
	}
	if (match(JSON_a, index) || match(JSON_b, index) || match(JSON_c, index) || match(JSON_d, index) || match(JSON_e, index) || match(JSON_f, index))
	{
		characters += jsonText.substr(index - 1, 1);

		value = static_cast<int32_t>(jsonText.substr(index - 1, 1)[0] - JSON_a[0]);

		return true;
	}

	return false;
}

//

bool JSONdecoder::decodeDigit_0(size_t& index, string& characters, int32_t& value)
{
	if (match(JSON_0, index))
	{
		characters += JSON_0;

		value = 0;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeDigit_1_9(size_t& index, string& characters, int32_t& value)
{
	if (match(JSON_1, index) || match(JSON_2, index) || match(JSON_3, index) || match(JSON_4, index) || match(JSON_5, index) || match(JSON_6, index) || match(JSON_7, index) || match(JSON_8, index) || match(JSON_9, index))
	{
		characters += jsonText.substr(index - 1, 1);

		value = atoi(jsonText.substr(index - 1, 1).c_str());

		return true;
	}

	return false;
}

bool JSONdecoder::decodeDigit(size_t& index, string& characters, int32_t& value)
{
	return decodeDigit_0(index, characters, value) || decodeDigit_1_9(index, characters, value);
}

bool JSONdecoder::decodeExponent(size_t& index, string& characters)
{
	if (match(JSON_e, index) || match(JSON_E, index))
	{
		characters += JSON_e;

		return true;
	}

	return false;
}

//

bool JSONdecoder::decodeQuotationMark(size_t& index, string& characters)
{
	if (match(JSON_quotation_mark, index))
	{
		characters += JSON_quotation_mark;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeReverseSolidus(size_t& index, string& characters)
{
	if (match(JSON_reverse_solidus, index))
	{
		// Do nothing.

		return true;
	}

	return false;
}

bool JSONdecoder::decodeSolidus(size_t& index, string& characters)
{
	if (match(JSON_solidus, index))
	{
		characters += JSON_solidus;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeBackspace(size_t& index, string& characters)
{
	if (match(JSON_Decode_backspace, index))
	{
		characters += JSON_Encode_backspace;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeFormFeed(size_t& index, string& characters)
{
	if (match(JSON_Decode_form_feed, index))
	{
		characters += JSON_Encode_form_feed;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeLineFeed(size_t& index, string& characters)
{
	if (match(JSON_Decode_line_feed, index))
	{
		characters += JSON_Encode_line_feed;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeCarriageReturn(size_t& index, string& characters)
{
	if (match(JSON_Decode_carriage_return, index))
	{
		characters += JSON_Encode_carriage_return;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeCharacterTabulation(size_t& index, string& characters)
{
	if (match(JSON_Decode_character_tabulation, index))
	{
		characters += JSON_Encode_character_tabulation;

		return true;
	}

	return false;
}

bool JSONdecoder::decodeHexadecimalNumber(size_t& index, string& characters)
{
	int32_t value = 0;
	int32_t tempValue = 0;

	size_t tempIndex = index;

	if (!match(JSON_u, tempIndex))
	{
		return false;
	}

	if (tempIndex + 4 > jsonText.length())
	{
		return false;
	}

	while (tempIndex < jsonText.length())
	{
		if (!decodeDigit(tempIndex, characters, tempValue) && !decodeHexadecimalDigit(tempIndex, characters, tempValue))
		{
			return false;
		}

		value = value * 16 + tempValue;
	}

	characters += static_cast<char>(value & 0xFF);

	index = tempIndex;

	return true;
}

//

bool JSONdecoder::decodeObject(size_t& index, JSONobjectSP& jsonObject)
{
	JSONobjectSP tempJsonObject = JSONobjectSP(new JSONobject());

	size_t tempIndex = index;

	bool loop = true;

	while (decodeWhitespace(tempIndex));

	if (!decodeLeftCurlyBracket(tempIndex))
	{
		return false;
	}

	while (decodeWhitespace(tempIndex));

	if (decodeRightCurlyBracket(tempIndex))
	{
		//
	}
	else
	{
		while (decodeWhitespace(tempIndex));

		while (loop)
		{
			JSONstringSP jsonString;
			JSONvalueSP jsonValue;

			loop = false;

			if (!decodeString(tempIndex, jsonString))
			{
				return false;
			}

			while (decodeWhitespace(tempIndex));

			if (!decodeColon(tempIndex))
			{
				return false;
			}

			while (decodeWhitespace(tempIndex));

			if (!decodeValue(tempIndex, jsonValue))
			{
				return false;
			}

			tempJsonObject->addKeyValue(jsonString, jsonValue);

			while (decodeWhitespace(tempIndex));

			if (decodeComma(tempIndex))
			{
				loop = true;
			}

			while (decodeWhitespace(tempIndex));
		}

		if (!decodeRightCurlyBracket(tempIndex))
		{
			return false;
		}
	}

	while (decodeWhitespace(tempIndex));

	jsonObject = tempJsonObject;

	index = tempIndex;

	return true;
}

bool JSONdecoder::decodeArray(size_t& index, JSONarraySP& jsonArray)
{
	JSONarraySP tempJsonArray = JSONarraySP(new JSONarray());

	size_t tempIndex = index;

	bool loop = true;

	while (decodeWhitespace(tempIndex));

	if (!decodeLeftSquareBracket(tempIndex))
	{
		return false;
	}

	while (decodeWhitespace(tempIndex));

	if (decodeRightSquareBracket(tempIndex))
	{
		//
	}
	else
	{
		while (decodeWhitespace(tempIndex));

		while (loop)
		{
			JSONvalueSP jsonValue;

			loop = false;

			if (!decodeValue(tempIndex, jsonValue))
			{
				return false;
			}

			tempJsonArray->addValue(jsonValue);

			while (decodeWhitespace(tempIndex));

			if (decodeComma(tempIndex))
			{
				loop = true;
			}

			while (decodeWhitespace(tempIndex));
		}

		if (!decodeRightSquareBracket(tempIndex))
		{
			return false;
		}
	}

	while (decodeWhitespace(tempIndex));

	jsonArray = tempJsonArray;

	index = tempIndex;

	return true;
}

bool JSONdecoder::decodeNumber(size_t& index, JSONnumberSP& jsonNumber)
{
	string tempString = "";
	int32_t dummy;

	size_t tempIndex = index;

	bool isFloat = false;

	while (decodeWhitespace(tempIndex));

	if (decodeMinus(tempIndex, tempString))
	{
		//
	}

	if (decodeDigit_0(tempIndex, tempString, dummy))
	{
		//
	}
	else if (decodeDigit_1_9(tempIndex, tempString, dummy))
	{
		bool loop = true;

		while (loop)
		{
			loop = false;

			loop = decodeDigit(tempIndex, tempString, dummy);
		}
	}
	else
	{
		return false;
	}

	if (decodePoint(tempIndex, tempString))
	{
		isFloat = true;

		bool loop = true;

		if (!decodeDigit(tempIndex, tempString, dummy))
		{
			return false;
		}

		while (loop)
		{
			loop = false;

			loop = decodeDigit(tempIndex, tempString, dummy);
		}
	}

	if (decodeExponent(tempIndex, tempString))
	{
		bool loop = true;

		if (decodePlus(tempIndex, tempString) || decodeMinus(tempIndex, tempString))
		{
			//
		}

		if (!decodeDigit(tempIndex, tempString, dummy))
		{
			return false;
		}

		while (loop)
		{
			loop = false;

			loop = decodeDigit(tempIndex, tempString, dummy);
		}
	}

	while (decodeWhitespace(tempIndex));

	jsonNumber = JSONnumberSP(new JSONnumber(tempString, isFloat));

	index = tempIndex;

	return true;
}

bool JSONdecoder::decodeString(size_t& index, JSONstringSP& jsonString)
{
	string dummyString = "";
	string tempString = "";

	size_t tempIndex = index;

	bool loop = true;

	while (decodeWhitespace(tempIndex));

	if (!decodeQuotationMark(tempIndex, dummyString))
	{
		return false;
	}

	while (loop)
	{
		loop = false;

		if (decodeQuotationMark(tempIndex, dummyString))
		{
			break;
		}

		if (decodeReverseSolidus(tempIndex, tempString))
		{
			if (decodeQuotationMark(tempIndex, tempString) || decodeReverseSolidus(tempIndex, tempString) || decodeSolidus(tempIndex, tempString) || decodeBackspace(tempIndex, tempString) || decodeSolidus(tempIndex, tempString) || decodeFormFeed(tempIndex, tempString) || decodeLineFeed(tempIndex, tempString) || decodeCarriageReturn(tempIndex, tempString) || decodeCharacterTabulation(tempIndex, tempString) || decodeHexadecimalNumber(tempIndex, tempString))
			{
				loop = true;
			}
			else
			{
				return false;
			}
		}
		else if ((jsonText[tempIndex] >= JSON_C0_start && jsonText[tempIndex] <= JSON_C0_end) || (jsonText[tempIndex] >= JSON_C1_start && jsonText[tempIndex] <= JSON_C1_end))
		{
			return false;
		}
		else
		{
			tempString += jsonText.substr(tempIndex, 1);

			if (tempIndex + 1 < jsonText.length())
			{
				tempIndex++;

				loop = true;
			}
			else
			{
				return false;
			}
		}
	}

	while (decodeWhitespace(tempIndex));

	jsonString = JSONstringSP(new JSONstring(tempString));

	index = tempIndex;

	return true;
}


bool JSONdecoder::decodeTrue(size_t& index, JSONtrueSP& jsonTrue)
{
	bool result;

	while (decodeWhitespace(index));

	result = match(JSON_true, index);

	while (decodeWhitespace(index));

	if (result)
	{
		jsonTrue = JSONtrueSP(new JSONtrue());
	}

	return result;
}

bool JSONdecoder::decodeFalse(size_t& index, JSONfalseSP& jsonFalse)
{
	bool result;

	while (decodeWhitespace(index));

	result = match(JSON_false, index);

	while (decodeWhitespace(index));

	if (result)
	{
		jsonFalse = JSONfalseSP(new JSONfalse());
	}

	return result;
}

bool JSONdecoder::decodeNull(size_t& index, JSONnullSP& jsonNull)
{
	bool result;

	while (decodeWhitespace(index));

	result =  match(JSON_null, index);

	while (decodeWhitespace(index));

	if (result)
	{
		jsonNull = JSONnullSP(new JSONnull());
	}

	return result;
}

//

bool JSONdecoder::decodeValue(size_t& index, JSONvalueSP& jsonValue)
{
	JSONobjectSP jsonObject;
	JSONarraySP jsonArray;
	JSONnumberSP jsonNumber;
	JSONstringSP jsonString;
	JSONtrueSP jsonTrue;
	JSONfalseSP jsonFalse;
	JSONnullSP jsonNull;

	jsonValue = JSONvalueSP();

	while (decodeWhitespace(index));

	if (decodeObject(index, jsonObject))
	{
		jsonValue = jsonObject;
	}
	else if (decodeArray(index, jsonArray))
	{
		jsonValue = jsonArray;
	}
	else if (decodeNumber(index, jsonNumber))
	{
		jsonValue = jsonNumber;
	}
	else if (decodeString(index, jsonString))
	{
		jsonValue = jsonString;
	}
	else if (decodeTrue(index, jsonTrue))
	{
		jsonValue = jsonTrue;
	}
	else if (decodeFalse(index, jsonFalse))
	{
		jsonValue = jsonFalse;
	}
	else if (decodeNull(index, jsonNull))
	{
		jsonValue = jsonNull;
	}

	while (decodeWhitespace(index));

	return jsonValue.get() != nullptr;
}

//

bool JSONdecoder::decode(const string& jsonText, JSONvalueSP& jsonValue)
{
	size_t index = 0;

	this->jsonText = jsonText;

	return decodeValue(index, jsonValue);
}

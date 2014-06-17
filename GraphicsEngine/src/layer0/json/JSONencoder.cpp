/*
 * JSONencoder.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#define JSON_TAB_STEP 3

#include "JSONtokens.h"

#include "JSONencoder.h"

using namespace std;

JSONencoder::JSONencoder() : jsonText(""), spaces(0)
{
}

JSONencoder::~JSONencoder()
{
}

bool JSONencoder::doLineFeed(int32_t tabs)
{
	if (spaces + JSON_TAB_STEP * tabs < 0)
	{
		return false;
	}

	jsonText += JSON_Encode_line_feed;

	spaces += JSON_TAB_STEP * tabs;

	for (int32_t i = 0; i < spaces; i++)
	{
		jsonText += JSON_space;
	}

	return true;
}

//

bool JSONencoder::encodeObject(const JSONobjectSP jsonObject)
{
	if (jsonObject.get() == nullptr)
	{
		return false;
	}

	jsonText += JSON_left_curly_bracket;

	doLineFeed(1);

	auto allKeyValues = jsonObject->getAllKeyValues();

	auto walker = allKeyValues.begin();

	while (walker != allKeyValues.end())
	{
		if (!encodeString(walker->first))
		{
			return false;
		}

		jsonText += JSON_space;
		jsonText += JSON_colon;
		jsonText += JSON_space;

		if (!encodeValue(walker->second))
		{
			return false;
		}

		walker++;

		if (walker != allKeyValues.end())
		{
			jsonText += JSON_comma;

			doLineFeed(0);
		}
	}

	doLineFeed(-1);

	jsonText += JSON_right_curly_bracket;

	return true;
}

bool JSONencoder::encodeArray(const JSONarraySP jsonArray)
{
	if (jsonArray.get() == nullptr)
	{
		return false;
	}

	jsonText += JSON_left_square_bracket;

	doLineFeed(1);

	auto allValues = jsonArray->getAllValues();

	auto walker = allValues.begin();

	while (walker != allValues.end())
	{
		if (!encodeValue(*walker))
		{
			return false;
		}

		walker++;

		if (walker != allValues.end())
		{
			jsonText += JSON_comma;

			doLineFeed(0);
		}
	}

	doLineFeed(-1);

	jsonText += JSON_right_square_bracket;

	return true;
}

bool JSONencoder::encodeNumber(const JSONnumberSP jsonNumber)
{
	if (jsonNumber.get() == nullptr)
	{
		return false;
	}

	char buffer[2048];

	if (jsonNumber->isFloatValue())
	{
		float dummy;

		if (fabsf(jsonNumber->getFloatValue()) >= 1000000.0 || fabsf(modff(jsonNumber->getFloatValue(), &dummy)) <= 0.0000001)
		{
			sprintf(buffer, "%e", jsonNumber->getFloatValue());
		}
		else
		{
			sprintf(buffer, "%.6f", jsonNumber->getFloatValue());
		}
	}
	else
	{
		sprintf(buffer, "%d", jsonNumber->getIntegerValue());
	}

	jsonText += string(buffer);

	return true;
}

bool JSONencoder::encodeString(const JSONstringSP jsonString)
{
	char c;

	if (jsonString.get() == nullptr)
	{
		return false;
	}

	jsonText += JSON_quotation_mark;

	for (size_t i = 0; i < jsonString->getValue().length(); i++)
	{
		c = jsonString->getValue()[i];

		if ((c >= JSON_C0_start && c <= JSON_C0_end) || (c >= JSON_C1_start && c <= JSON_C1_end))
		{
			return false;
		}

		if (c == JSON_quotation_mark[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_quotation_mark;
		}
		else if (c == JSON_reverse_solidus[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_reverse_solidus;
		}
		else if (c == JSON_solidus[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_solidus;
		}
		else if (c == JSON_Encode_backspace[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_Decode_backspace;
		}
		else if (c == JSON_Encode_form_feed[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_Decode_form_feed;
		}
		else if (c == JSON_Encode_line_feed[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_Decode_line_feed;
		}
		else if (c == JSON_Encode_carriage_return[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_Decode_carriage_return;
		}
		else if (c == JSON_Encode_character_tabulation[0])
		{
			jsonText += JSON_reverse_solidus;
			jsonText += JSON_Decode_character_tabulation;
		}
		else
		{
			jsonText += jsonString->getValue().substr(i, 1);
		}
	}

	jsonText += JSON_quotation_mark;

	return true;
}

bool JSONencoder::encodeTrue(const JSONtrueSP jsonTrue)
{
	if (jsonTrue.get() == nullptr)
	{
		return false;
	}

	jsonText += JSON_true;

	return true;
}

bool JSONencoder::encodeFalse(const JSONfalseSP jsonFalse)
{
	if (jsonFalse.get() == nullptr)
	{
		return false;
	}

	jsonText += JSON_false;

	return true;
}

bool JSONencoder::encodeNull(const JSONnullSP jsonNull)
{
	if (jsonNull.get() == nullptr)
	{
		return false;
	}

	jsonText += JSON_null;

	return true;
}

//

bool JSONencoder::encodeValue(const JSONvalueSP jsonValue)
{
	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	if (jsonValue->isJsonObject())
	{
		const JSONobjectSP jsonObject = dynamic_pointer_cast<JSONobject>(jsonValue);

		return encodeObject(jsonObject);
	}
	else if (jsonValue->isJsonArray())
	{
		const JSONarraySP jsonArray = dynamic_pointer_cast<JSONarray>(jsonValue);

		return encodeArray(jsonArray);
	}
	else if (jsonValue->isJsonNumber())
	{
		const JSONnumberSP jsonNumber = dynamic_pointer_cast<JSONnumber>(jsonValue);

		return encodeNumber(jsonNumber);
	}
	else if (jsonValue->isJsonString())
	{
		const JSONstringSP jsonString = dynamic_pointer_cast<JSONstring>(jsonValue);

		return encodeString(jsonString);
	}
	else if (jsonValue->isJsonTrue())
	{
		const JSONtrueSP jsonTrue = dynamic_pointer_cast<JSONtrue>(jsonValue);

		return encodeTrue(jsonTrue);
	}
	else if (jsonValue->isJsonFalse())
	{
		const JSONfalseSP jsonFalse = dynamic_pointer_cast<JSONfalse>(jsonValue);

		return encodeFalse(jsonFalse);
	}
	else if (jsonValue->isJsonNull())
	{
		const JSONnullSP jsonNull = dynamic_pointer_cast<JSONnull>(jsonValue);

		return encodeNull(jsonNull);
	}

	return false;
}

//

bool JSONencoder::encode(const JSONvalueSP jsonValue, string& jsonText)
{
	bool result;

	if (jsonValue.get() == nullptr)
	{
		return false;
	}

	this->jsonText = "";
	this->spaces = 0;

	result = encodeValue(jsonValue);

	if (result)
	{
		jsonText = this->jsonText;
	}

	return result;
}

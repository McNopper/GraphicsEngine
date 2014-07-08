/*
 * JSONtokens.h
 *
 *  Created on: Jun 16, 2014
 *      Author: nopper
 */

#ifndef JSONTOKENS_H_
#define JSONTOKENS_H_

#include "../../UsedLibs.h"

// Structural tokens

static const std::string JSON_left_square_bracket = "[";
static const std::string JSON_left_curly_bracket = "{";
static const std::string JSON_right_square_bracket = "]";
static const std::string JSON_right_curly_bracket = "}";
static const std::string JSON_colon = ":";
static const std::string JSON_comma = ",";

// Literal name tokens

static const std::string JSON_true = "true";
static const std::string JSON_false = "false";
static const std::string JSON_null = "null";

//

static const std::string JSON_quotation_mark = "\"";
static const std::string JSON_reverse_solidus = "\\";
static const std::string JSON_solidus = "/";

static const std::string JSON_Decode_backspace = "b";
static const std::string JSON_Decode_form_feed = "f";
static const std::string JSON_Decode_line_feed = "n";
static const std::string JSON_Decode_carriage_return = "r";
static const std::string JSON_Decode_character_tabulation = "t";

static const std::string JSON_Encode_backspace = "\b";
static const std::string JSON_Encode_form_feed = "\f";
static const std::string JSON_Encode_line_feed = "\n";
static const std::string JSON_Encode_carriage_return = "\r";
static const std::string JSON_Encode_character_tabulation = "\t";

//

static const std::string JSON_space = " ";

//

static const std::string JSON_plus = "+";
static const std::string JSON_minus = "-";
static const std::string JSON_point = ".";

static const std::string JSON_A = "A";
static const std::string JSON_B = "B";
static const std::string JSON_C = "C";
static const std::string JSON_D = "D";
static const std::string JSON_E = "E";
static const std::string JSON_F = "F";

static const std::string JSON_a = "a";
static const std::string JSON_b = "b";
static const std::string JSON_c = "c";
static const std::string JSON_d = "d";
static const std::string JSON_e = "e";
static const std::string JSON_f = "f";

static const std::string JSON_0 = "0";
static const std::string JSON_1 = "1";
static const std::string JSON_2 = "2";
static const std::string JSON_3 = "3";
static const std::string JSON_4 = "4";
static const std::string JSON_5 = "5";
static const std::string JSON_6 = "6";
static const std::string JSON_7 = "7";
static const std::string JSON_8 = "8";
static const std::string JSON_9 = "9";

static const std::string JSON_u = "u";

static const std::int32_t JSON_C0_start = 0x00;
static const std::int32_t JSON_C0_end = 0x1F;
static const std::int32_t JSON_C1_start = 0x7F;
static const std::int32_t JSON_C1_end = 0x9F;

#endif /* JSONTOKENS_H_ */

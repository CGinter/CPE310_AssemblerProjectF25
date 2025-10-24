/**
 * @file consts.c
 * @brief
 * @author Chase Sprigle
 * @date 10/23/2025
 */
#include "include.h"

const uint32_t UNDEFINED;

const uint32_t MAX_5_BIT = 31;
const uint32_t MAX_6_BIT = 63;
const uint32_t MAX_16_BIT = 65535;
const uint32_t MAX_26_BIT = 67108863;

const struct instruction_definition instruction_definitions[] = {
	{
		"ADD",
		R_TYPE,
		"000000",
		"100000",
		{ RD, RS, RT, EMPTY }
	},
	{
		"DIV",
		R_TYPE,
		"000000",
		"011010",
		{ RS, RT, EMPTY, EMPTY }
	}
};
